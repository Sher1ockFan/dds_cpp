// Copyright (c) 2025, pndbotics Robotics Co., Ltd.
// All rights reserved.

#pragma once

#include "pndbotics/dds_wrapper/common/Publisher.h"
#include "pndbotics/dds_wrapper/common/crc.h"
#include "pndbotics/dds_wrapper/common/pndbotics_joystick.hpp"

#include <pndbotics/idl/go2/LowCmd_.hpp>
#include <pndbotics/idl/go2/LowState_.hpp>
#include <pndbotics/idl/go2/SportModeCmd_.hpp>
#include <pndbotics/idl/go2/SportModeState_.hpp>
#include <pndbotics/idl/go2/LidarState_.hpp>
#include <pndbotics/idl/go2/UwbState_.hpp>
#include <pndbotics/idl/go2/HeightMap_.hpp>
#include <pndbotics/idl/ros2/Time_.hpp>
#include <pndbotics/idl/ros2/PointCloud2_.hpp>
#include <pndbotics/idl/go2/WirelessController_.hpp>
#include <pndbotics/idl/go2/Res_.hpp>
#include <pndbotics/idl/go2/MotorCmds_.hpp>
#include <pndbotics/idl/go2/MotorStates_.hpp>


namespace pndbotics
{
namespace robot
{
namespace go2
{ 
namespace publisher
{

class LowCmd : public RealTimePublisher<pndbotics_go::msg::dds_::LowCmd_>
{
public:
  LowCmd(std::string topic = "rt/lowcmd")
  : RealTimePublisher<MsgType>(topic) 
  {
    msg_.head() = {0xFE, 0xEF};
    msg_.level_flag() = 0xFF;

    for (auto & m : msg_.motor_cmd()) m.mode(1);
  } 

private:
  /**
   * @brief Something before sending the message.
   */
  void pre_communication() override {
    msg_.crc() = crc32_core((uint32_t*)&msg_, (sizeof(MsgType)>>2)-1);
  }
};


class LowState : public RealTimePublisher<pndbotics_go::msg::dds_::LowState_>
{
public:
  LowState(std::string topic = "rt/lowstate")
  : RealTimePublisher<MsgType>(topic) 
  {}

  std::shared_ptr<pndbotics::common::pndboticsJoystick> joystick = nullptr;

private:
  void pre_communication() override {
    if (joystick) {
      pndbotics::common::REMOTE_DATA_RX key = joystick->combine();
      memcpy(&msg_.wireless_remote()[0], &key, sizeof(pndbotics::common::REMOTE_DATA_RX));
    }
    msg_.crc() = crc32_core((uint32_t*)&msg_, (sizeof(MsgType)>>2)-1);
  }
};

class SportModeState : public RealTimePublisher<pndbotics_go::msg::dds_::SportModeState_>
{
public:
  SportModeState(std::string topic = "rt/sportmodestate")
  : RealTimePublisher<MsgType>(topic) 
  {
  }
};

class WirelessController : public RealTimePublisher<pndbotics_go::msg::dds_::WirelessController_>
{
public:
  WirelessController(std::string topic = "rt/wirelesscontroller")
  : RealTimePublisher<MsgType>(topic) 
  {
  }

  std::shared_ptr<pndbotics::common::pndboticsJoystick> joystick = nullptr;

private:
  void pre_communication() override {
    if (joystick) {
      msg_.lx() = joystick->lx();
      msg_.ly() = joystick->ly();
      msg_.rx() = joystick->rx();
      msg_.ry() = joystick->ry();
      msg_.keys() = joystick->combine().RF_RX.btn.value;
    }
  }
};

class MotorCmds : public RealTimePublisher<pndbotics_go::msg::dds_::MotorCmds_>
{
public:
  MotorCmds(std::string topic, int num = 1)
  : RealTimePublisher<MsgType>(topic) 
  {
    msg_.cmds().resize(num);
  }
};

class MotorStates : public RealTimePublisher<pndbotics_go::msg::dds_::MotorStates_>
{
public:
  MotorStates(std::string topic, int num = 1)
  : RealTimePublisher<MsgType>(topic) 
  {
    msg_.states().resize(num);
  }
};

} // namespace publisher
} // namespace go2
} // namespace robot
} // namespace pndbotics