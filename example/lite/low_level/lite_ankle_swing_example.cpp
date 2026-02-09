#include <cmath>
#include <memory>
#include <mutex>
#include <shared_mutex>

#include "gamepad.hpp"

// DDS
#include <unitree/robot/channel/channel_publisher.hpp>
#include <unitree/robot/channel/channel_subscriber.hpp>

// IDL
#include <unitree/idl/pnd_adam/IMUState_.hpp>
#include <unitree/idl/pnd_adam/LowCmd_.hpp>
#include <unitree/idl/pnd_adam/LowState_.hpp>
#include <unitree/robot/b2/motion_switcher/motion_switcher_client.hpp>

static const std::string ADAMCMD_TOPIC = "rt/lowcmd";
static const std::string ADAMSTATE_TOPIC = "rt/lowstate";

using namespace unitree::common;
using namespace unitree::robot;
using namespace pnd_adam::msg::dds_;

template <typename T>
class DataBuffer {
 public:
  void SetData(const T &newData) {
    std::unique_lock<std::shared_mutex> lock(mutex);
    data = std::make_shared<T>(newData);
  }

  std::shared_ptr<const T> GetData() {
    std::shared_lock<std::shared_mutex> lock(mutex);
    return data ? data : nullptr;
  }

  void Clear() {
    std::unique_lock<std::shared_mutex> lock(mutex);
    data = nullptr;
  }

 private:
  std::shared_ptr<T> data;
  std::shared_mutex mutex;
};

const int LITE_NUM_MOTOR = 23;
struct ImuState {
  std::array<float, 3> ypr = {};
  std::array<float, 3> omega = {};
};
struct MotorCommand {
  std::array<float, LITE_NUM_MOTOR> q_target = {};
  std::array<float, LITE_NUM_MOTOR> dq_target = {};
  std::array<float, LITE_NUM_MOTOR> kp = {};
  std::array<float, LITE_NUM_MOTOR> kd = {};
  std::array<float, LITE_NUM_MOTOR> tau_ff = {};
};
struct MotorState {
  std::array<float, LITE_NUM_MOTOR> q = {};
  std::array<float, LITE_NUM_MOTOR> dq = {};
};

// Stiffness for all LITE Joints
std::array<float, LITE_NUM_MOTOR> Kp{
    305.0, 700.0, 405.0, //  hip left
    305.0, 20, 0, // knee and ankle
    
    305.0, 700.0, 405.0, //  hip right
    305.0, 20, 0, // knee and ankle
    
    405.0, 405.0, 205.0, //  waist
    
    18.0, 9.0, 9.0, //  shoulder left
    9.0,  //  arms

    18.0, 9.0, 9.0, //  shoulder right
    9.0 //  arms
};

// Damping for all LITE Joints
std::array<float, LITE_NUM_MOTOR> Kd{
    6.1, 30.0, 6.1,
    6.1, 2.5, 0.35,
    
    6.1, 30.0, 6.1,
    6.1, 2.5, 0.35,    //  legs
    
    4.1, 6.1, 6.1,             //  waist
    
    0.9, 0.9, 0.9,
    0.9,  //  arms
    
    0.9, 0.9, 0.9, 
    0.9 //  arms 
};

enum class Mode {
  PR = 0,  // Series Control for Ptich/Roll Joints
  AB = 1   // Parallel Control for A/B Joints
};

enum LITEJointIndex {
  LeftHipPitch = 0,
  LeftHipRoll = 1,
  LeftHipYaw = 2,
  LeftKnee = 3,
  LeftAnklePitch = 4,
  LeftAnkleB = 4,
  LeftAnkleRoll = 5,
  LeftAnkleA = 5,
  RightHipPitch = 6,
  RightHipRoll = 7,
  RightHipYaw = 8,
  RightKnee = 9,
  RightAnklePitch = 10,
  RightAnkleB = 10,
  RightAnkleRoll = 11,
  RightAnkleA = 11,
  WaistYaw = 12,
  WaistRoll = 13,        
  WaistA = 13,           
  WaistPitch = 14,       
  WaistB = 14,           
  LeftShoulderPitch = 15,
  LeftShoulderRoll = 16,
  LeftShoulderYaw = 17,
  LeftElbow = 18,
  RightShoulderPitch = 19,
  RightShoulderRoll = 20,
  RightShoulderYaw = 21,
  RightElbow = 22,
};

class LITEExample {
 private:
  double time_;
  double control_dt_;  // [2ms]
  double duration_;    // [3 s]
  int counter_;
  Mode mode_pr_;
  uint8_t mode_machine_;

  Gamepad gamepad_;
  REMOTE_DATA_RX rx_;

  DataBuffer<MotorState> motor_state_buffer_;
  DataBuffer<MotorCommand> motor_command_buffer_;
  DataBuffer<ImuState> imu_state_buffer_;

  ChannelPublisherPtr<LowCmd_> lowcmd_publisher_;
  ChannelSubscriberPtr<LowState_> lowstate_subscriber_;
  ChannelSubscriberPtr<IMUState_> imutorso_subscriber_;
  ThreadPtr command_writer_ptr_, control_thread_ptr_;

  std::shared_ptr<unitree::robot::b2::MotionSwitcherClient> msc_;

 public:
  LITEExample(std::string networkInterface)
      : time_(0.0),
        control_dt_(0.002),
        duration_(3.0),
        counter_(0),
        mode_pr_(Mode::PR),
        mode_machine_(0) {
    ChannelFactory::Instance()->Init(1, networkInterface);

    // try to shutdown motion control-related service
    msc_ = std::make_shared<unitree::robot::b2::MotionSwitcherClient>();
    msc_->SetTimeout(5.0f);
    msc_->Init();
    std::string form, name;
    while (msc_->CheckMode(form, name), !name.empty()) {
      if (msc_->ReleaseMode())
        std::cout << "Failed to switch to Release Mode\n";
      sleep(5);
    }

    // create publisher
    // LowCmd_ low_cmd = LowCmd_(0, std::vector<MotorCmd_>(LITE_NUM_MOTOR), 0); 
    lowcmd_publisher_.reset(new ChannelPublisher<LowCmd_>(ADAMCMD_TOPIC));
    lowcmd_publisher_->InitChannel();
    // create subscriber
    LowState_(0, 0, IMUState_(), std::vector<MotorState_>(LITE_NUM_MOTOR), std::array<float,19>{}, 0);
    lowstate_subscriber_.reset(new ChannelSubscriber<LowState_>(ADAMSTATE_TOPIC));
    lowstate_subscriber_->InitChannel(std::bind(&LITEExample::LowStateHandler, this, std::placeholders::_1), 1);

    // create threads
    command_writer_ptr_ = CreateRecurrentThreadEx("command_writer", UT_CPU_ID_NONE, 2000, &LITEExample::LowCommandWriter, this);
    control_thread_ptr_ = CreateRecurrentThreadEx("control", UT_CPU_ID_NONE, 2000, &LITEExample::Control, this);
  }

  void LowStateHandler(const void *message) {
    LowState_ low_state = *(const LowState_ *)message;

    // get motor state
    MotorState ms_tmp;
    for (int i = 0; i < LITE_NUM_MOTOR; ++i) {
      ms_tmp.q.at(i) = low_state.motor_state()[i].q();
      ms_tmp.dq.at(i) = low_state.motor_state()[i].dq();
      if (low_state.motor_state()[i].state() && i <= RightAnkleRoll)
        std::cout << "[ERROR] motor " << i << " with code " << low_state.motor_state()[i].state() << "\n";
    }
    motor_state_buffer_.SetData(ms_tmp);

    // get imu state
    ImuState imu_tmp;
    imu_tmp.omega = low_state.imu_state().gyroscope();
    imu_tmp.ypr = low_state.imu_state().ypr();
    imu_state_buffer_.SetData(imu_tmp);

    // update gamepad
    memcpy(rx_.buff, &low_state.wireless_remote()[0], 40);
    gamepad_.update(rx_.RF_RX);

    // report robot status every second
    if (++counter_ % 500 == 0) {
      counter_ = 0;
      // IMU
      auto &ypr = low_state.imu_state().gyroscope();
      printf("IMU.pelvis.ypr: %.2f %.2f %.2f\n", ypr[0], ypr[1], ypr[2]);

      // RC
      printf("gamepad_.A.pressed: %d\n", static_cast<int>(gamepad_.A.pressed));
      printf("gamepad_.B.pressed: %d\n", static_cast<int>(gamepad_.B.pressed));
      printf("gamepad_.X.pressed: %d\n", static_cast<int>(gamepad_.X.pressed));
      printf("gamepad_.Y.pressed: %d\n", static_cast<int>(gamepad_.Y.pressed));

      // Motor
      auto &ms = low_state.motor_state();
      printf("All %d Motors:", LITE_NUM_MOTOR);
      printf("\nmode: ");
      for (int i = 0; i < LITE_NUM_MOTOR; ++i) printf("%u,", ms[i].mode());
      printf("\npos: ");
      for (int i = 0; i < LITE_NUM_MOTOR; ++i) printf("%.2f,", ms[i].q());
      printf("\nvel: ");
      for (int i = 0; i < LITE_NUM_MOTOR; ++i) printf("%.2f,", ms[i].dq());
      printf("\ntau_est: ");
      for (int i = 0; i < LITE_NUM_MOTOR; ++i) printf("%.2f,", ms[i].tau_est());
      printf("\nstate: ");
      for (int i = 0; i < LITE_NUM_MOTOR; ++i) printf("%u,", ms[i].state());
      printf("\n");
    }
  }

  void LowCommandWriter() {
    LowCmd_ dds_low_command = LowCmd_(0, std::vector<MotorCmd_>(LITE_NUM_MOTOR), 0);
    dds_low_command.mode_pr() = static_cast<uint8_t>(mode_pr_);
    // dds_low_command.mode_machine() = mode_machine_;

    const std::shared_ptr<const MotorCommand> mc = motor_command_buffer_.GetData();
    if (mc) {
      for (size_t i = 0; i < LITE_NUM_MOTOR; i++) {
        dds_low_command.motor_cmd().at(i).mode() = 1;  // 1:Enable, 0:Disable
        dds_low_command.motor_cmd().at(i).tau() = mc->tau_ff.at(i);
        dds_low_command.motor_cmd().at(i).q() = mc->q_target.at(i);
        dds_low_command.motor_cmd().at(i).dq() = mc->dq_target.at(i);
        dds_low_command.motor_cmd().at(i).kp() = mc->kp.at(i);
        dds_low_command.motor_cmd().at(i).kd() = mc->kd.at(i);
      }

      lowcmd_publisher_->Write(dds_low_command);
    }
  }

  void Control() {
    MotorCommand motor_command_tmp;
    const std::shared_ptr<const MotorState> ms = motor_state_buffer_.GetData();

    for (int i = 0; i < LITE_NUM_MOTOR; ++i) {
      motor_command_tmp.tau_ff.at(i) = 0.0;
      motor_command_tmp.q_target.at(i) = 0.0;
      motor_command_tmp.dq_target.at(i) = 0.0;
      motor_command_tmp.kp.at(i) = Kp[i];
      motor_command_tmp.kd.at(i) = Kd[i];
    }

    if (ms) {
      time_ += control_dt_;
      if (time_ < duration_) {
        // [Stage 1]: set robot to zero posture
        for (int i = 0; i < LITE_NUM_MOTOR; ++i) {
          double ratio = std::clamp(time_ / duration_, 0.0, 1.0);
          motor_command_tmp.q_target.at(i) = (1.0 - ratio) * ms->q.at(i);
        }
      } else if (time_ < duration_ * 2) {
        // [Stage 2]: swing ankle using PR mode
        mode_pr_ = Mode::PR;
        double max_P = M_PI * 30.0 / 180.0;
        double max_R = M_PI * 10.0 / 180.0;
        double t = time_ - duration_;
        double L_P_des = max_P * std::sin(2.0 * M_PI * t);
        double L_R_des = max_R * std::sin(2.0 * M_PI * t);
        double R_P_des = max_P * std::sin(2.0 * M_PI * t);
        double R_R_des = -max_R * std::sin(2.0 * M_PI * t);

        motor_command_tmp.q_target.at(LeftAnklePitch) = L_P_des;
        motor_command_tmp.q_target.at(LeftAnkleRoll) = L_R_des;
        motor_command_tmp.q_target.at(RightAnklePitch) = R_P_des;
        motor_command_tmp.q_target.at(RightAnkleRoll) = R_R_des;
      } else {
        // [Stage 3]: swing ankle using AB mode
        mode_pr_ = Mode::AB;
        double max_A = M_PI * 30.0 / 180.0;
        double max_B = M_PI * 10.0 / 180.0;
        double t = time_ - duration_ * 2;
        double L_A_des = +max_A * std::sin(M_PI * t);
        double L_B_des = +max_B * std::sin(M_PI * t + M_PI);
        double R_A_des = -max_A * std::sin(M_PI * t);
        double R_B_des = -max_B * std::sin(M_PI * t + M_PI);

        motor_command_tmp.q_target.at(LeftAnkleA) = L_A_des;
        motor_command_tmp.q_target.at(LeftAnkleB) = L_B_des;
        motor_command_tmp.q_target.at(RightAnkleA) = R_A_des;
        motor_command_tmp.q_target.at(RightAnkleB) = R_B_des;
      }

      motor_command_buffer_.SetData(motor_command_tmp);
    }
  }
};

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: lite_ankle_swing_example network_interface" << std::endl;
    exit(0);
  }
  std::string networkInterface = argv[1];
  LITEExample custom(networkInterface);
  while (true) sleep(10);
  return 0;
}
