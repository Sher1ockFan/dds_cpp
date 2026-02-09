add_executable(lite_ankle_swing_example low_level/lite_ankle_swing_example.cpp
                src_idl/HandCmd_.cpp
                src_idl/HandState_.cpp
                src_idl/IMUState_.cpp
                src_idl/LowCmd_.cpp
                src_idl/LowState_.cpp
                src_idl/MotorCmd_.cpp
                src_idl/MotorState_.cpp)
# 让 src_idl/*.cpp 中的 #include "XXX_.hpp" 能找到 pnd_adam 下的头文件
target_include_directories(lite_ankle_swing_example PRIVATE
    ${CMAKE_SOURCE_DIR}/include/unitree/idl/pnd_adam)
target_link_libraries(lite_ankle_swing_example unitree_sdk2)