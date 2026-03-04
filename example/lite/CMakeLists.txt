set(LITE_ANKLE_SWING_TARGET lite_ankle_swing_example)

set(LITE_ANKLE_SWING_SOURCES
    low_level/lite_ankle_swing_example.cpp
)

add_executable(${LITE_ANKLE_SWING_TARGET} ${LITE_ANKLE_SWING_SOURCES})

target_link_libraries(${LITE_ANKLE_SWING_TARGET}
    PRIVATE
        pndbotics_sdk
)