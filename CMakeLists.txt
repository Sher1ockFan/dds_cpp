cmake_minimum_required(VERSION 3.5)
project(unitree_sdk2 VERSION 2.0.0)

## Project Options
option(BUILD_EXAMPLES "Build examples" ON)
option(USE_PREBUILT_UNITREE_SDK "Use prebuilt libunitree_sdk2.a" ON)

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

if (USE_PREBUILT_UNITREE_SDK)
    ## Import Unitree SDK2 library
    set(UNITREE_SDK_PATH ${CMAKE_CURRENT_LIST_DIR}/lib/${CMAKE_SYSTEM_PROCESSOR})
    find_library(UNITREE_SDK_LIB unitree_sdk2 PATHS ${UNITREE_SDK_PATH} NO_DEFAULT_PATH)

    if (NOT UNITREE_SDK_LIB)
        message(FATAL_ERROR "Unitree SDK library for the architecture is not found")
    else ()
        message(STATUS "Unitree SDK library found at: ${UNITREE_SDK_LIB}")
    endif ()

    message(STATUS "Importing: ${UNITREE_SDK_LIB}")

    add_library(unitree_sdk2 STATIC IMPORTED GLOBAL)
    set_target_properties(unitree_sdk2 PROPERTIES
            IMPORTED_LOCATION ${UNITREE_SDK_LIB})
    target_link_libraries(unitree_sdk2 INTERFACE ddsc ddscxx Threads::Threads)
    target_include_directories(unitree_sdk2 INTERFACE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>)
else ()
    message(STATUS "Building unitree_sdk2 from source (without prebuilt libunitree_sdk2.a)")

    if (BUILD_EXAMPLES)
        message(WARNING "Examples depend on modules not included in source mode. BUILD_EXAMPLES will be disabled.")
        set(BUILD_EXAMPLES OFF)
    endif ()

    set(UNITREE_SDK2_SRC
        src/unitree/common/dds/dds_callback.cpp
        src/unitree/common/dds/dds_qos_policy.cpp
        src/unitree/common/dds/dds_qos.cpp
        src/unitree/common/dds/dds_qos_policy_parameter.cpp
        src/unitree/common/dds/dds_qos_parameter.cpp
        src/unitree/common/dds/dds_qos_realize.cpp
        src/unitree/common/dds/dds_parameter.cpp
        src/unitree/common/dds/dds_entity.cpp
        src/unitree/common/dds/dds_factory_model.cpp
        src/unitree/common/dds/dds_easy_model.cpp
    )

    add_library(unitree_sdk2 STATIC ${UNITREE_SDK2_SRC})
    target_link_libraries(unitree_sdk2 PUBLIC ddsc ddscxx Threads::Threads)
    target_include_directories(unitree_sdk2 PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>)
endif ()

if (BUILD_EXAMPLES)
    add_subdirectory(example)
endif ()

## Install the library
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if (USE_PREBUILT_UNITREE_SDK)
    install(FILES ${UNITREE_SDK_LIB}
        DESTINATION ${CMAKE_INSTALL_LIBDIR})
else ()
    install(TARGETS unitree_sdk2
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif ()

install(FILES cmake/unitree_sdk2Targets.cmake
    DESTINATION lib/cmake/unitree_sdk2)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    unitree_sdk2ConfigVersion.cmake
    VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}"
    COMPATIBILITY ExactVersion)

configure_file(cmake/unitree_sdk2Config.cmake.in unitree_sdk2Config.cmake @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/unitree_sdk2Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/unitree_sdk2ConfigVersion.cmake"
    DESTINATION lib/cmake/unitree_sdk2)
