set(LITE_ANKLE_SWING_TARGET lite_ankle_swing_example)

set(LITE_ANKLE_SWING_SOURCES
    low_level/lite_ankle_swing_example.cpp
    src_idl/HandCmd_.cpp
    src_idl/HandState_.cpp
    src_idl/IMUState_.cpp
    src_idl/LowCmd_.cpp
    src_idl/LowState_.cpp
    src_idl/MotorCmd_.cpp
    src_idl/MotorState_.cpp
)

add_executable(${LITE_ANKLE_SWING_TARGET} ${LITE_ANKLE_SWING_SOURCES})

# 让 src_idl/*.cpp 中的 #include "XXX_.hpp" 能找到 pnd_adam 下的头文件
target_include_directories(${LITE_ANKLE_SWING_TARGET}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/pndbotics/idl/pnd_adam
)

target_link_libraries(${LITE_ANKLE_SWING_TARGET}
    PRIVATE
        pndbotics_sdk2
)