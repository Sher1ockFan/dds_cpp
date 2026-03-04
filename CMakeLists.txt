cmake_minimum_required(VERSION 3.5)
project(pndbotics_sdk VERSION 2.0.0)

## Project Options
option(BUILD_EXAMPLES "Build examples" ON)
option(USE_PREBUILT_pndbotics_SDK "Use prebuilt libpndbotics_sdk.a" ON)

## Set compiler to use c++ 17 features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Chosse build type
set(default_build_type "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
            STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
            "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()

## Use GNUInstallDirs to install libraries into correct locations on all platforms.
include(GNUInstallDirs)

## Put all binary files into /bin and libraries into /lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

## Check system architecture
message(STATUS "Current system architecture: ${CMAKE_SYSTEM_PROCESSOR}")

## Import thirdparty libraries
add_subdirectory(thirdparty)

find_package(Threads REQUIRED)

if (USE_PREBUILT_pndbotics_SDK)
    ## Import pndbotics SDK2 library
    set(pndbotics_SDK_PATH ${CMAKE_CURRENT_LIST_DIR}/lib/${CMAKE_SYSTEM_PROCESSOR})
    find_library(pndbotics_SDK_LIB pndbotics_sdk PATHS ${pndbotics_SDK_PATH} NO_DEFAULT_PATH)

    if (NOT pndbotics_SDK_LIB)
        message(FATAL_ERROR "pndbotics SDK library for the architecture is not found")
    else ()
        message(STATUS "pndbotics SDK library found at: ${pndbotics_SDK_LIB}")
    endif ()

    message(STATUS "Importing: ${pndbotics_SDK_LIB}")

    add_library(pndbotics_sdk STATIC IMPORTED GLOBAL)
    set_target_properties(pndbotics_sdk PROPERTIES
            IMPORTED_LOCATION ${pndbotics_SDK_LIB})
    target_link_libraries(pndbotics_sdk INTERFACE ddsc ddscxx Threads::Threads)
    target_include_directories(pndbotics_sdk INTERFACE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>)
else ()
    message(STATUS "Building pndbotics_sdk from source (without prebuilt libpndbotics_sdk.a)")

    set(pndbotics_sdk_SRC
        src/pndbotics/common/lock/lock.cpp
        src/pndbotics/common/os.cpp
        src/pndbotics/common/thread/future.cpp
        src/pndbotics/common/thread/thread.cpp
        src/pndbotics/common/thread/recurrent_thread.cpp
        src/pndbotics/common/time/sleep.cpp
        src/pndbotics/common/time/time_tool.cpp
        src/pndbotics/common/dds/dds_callback.cpp
        src/pndbotics/common/dds/dds_qos_policy.cpp
        src/pndbotics/common/dds/dds_qos.cpp
        src/pndbotics/common/dds/dds_qos_policy_parameter.cpp
        src/pndbotics/common/dds/dds_qos_parameter.cpp
        src/pndbotics/common/dds/dds_qos_realize.cpp
        src/pndbotics/common/dds/dds_parameter.cpp
        src/pndbotics/common/dds/dds_entity.cpp
        src/pndbotics/common/dds/dds_factory_model.cpp
        src/pndbotics/common/dds/dds_easy_model.cpp
        src/pndbotics/robot/channel/channel_factory.cpp
        example/lite/src_idl/HandCmd_.cpp
        example/lite/src_idl/HandState_.cpp
        example/lite/src_idl/IMUState_.cpp
        example/lite/src_idl/LowCmd_.cpp
        example/lite/src_idl/LowState_.cpp
        example/lite/src_idl/MotorCmd_.cpp
        example/lite/src_idl/MotorState_.cpp
    )

    add_library(pndbotics_sdk STATIC ${pndbotics_sdk_SRC})
    target_link_libraries(pndbotics_sdk PUBLIC ddsc ddscxx Threads::Threads)
    target_include_directories(pndbotics_sdk PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>)
    target_include_directories(pndbotics_sdk PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include/pndbotics/idl/pnd_adam)
endif ()

if (BUILD_EXAMPLES)
    add_subdirectory(example)
endif ()

## Install the library
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if (USE_PREBUILT_pndbotics_SDK)
    install(FILES ${pndbotics_SDK_LIB}
        DESTINATION ${CMAKE_INSTALL_LIBDIR})
else ()
    install(TARGETS pndbotics_sdk
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif ()

install(FILES cmake/pndbotics_sdkTargets.cmake
    DESTINATION lib/cmake/pndbotics_sdk)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    pndbotics_sdkConfigVersion.cmake
    VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}"
    COMPATIBILITY ExactVersion)

configure_file(cmake/pndbotics_sdkConfig.cmake.in pndbotics_sdkConfig.cmake @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pndbotics_sdkConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/pndbotics_sdkConfigVersion.cmake"
    DESTINATION lib/cmake/pndbotics_sdk)
