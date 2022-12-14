cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from GIT and fetch it (must be done before `project()`)
#set(PICO_SDK_FETCH_FROM_GIT on)
#include(cmake/pico_sdk_import.cmake)

# specify project name and version
project(DirtAEB VERSION 0.1)

# initialize the raspberry pi pico sdk
#pico_sdk_init()

# specify C++ version
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#==============================================================================
# DirtAEB firmware
#==============================================================================

# include all cpp and header files
#file(GLOB SOURCES "src/*.cpp" "src/*.h")

# create the executable
#set(FIRMWARE_NAME dirtaeb_v${CMAKE_PROJECT_VERSION})
#add_executable(${FIRMWARE_NAME} ${SOURCES})

# add the pico_stdlib which aggregates commonly used features
#target_link_libraries(${FIRMWARE_NAME} pico_stdlib)

# create map/bin/hex/uf2 file in addition to ELF
#pico_add_extra_outputs(${FIRMWARE_NAME})

#==============================================================================
# Pusher motor FSM test utility
#==============================================================================
add_executable(PusherMotorFsmTester 
    src/fsm_list.h
    src/tinyfsm.h
    src/pusher_motor_fsm.h
    src/pusher_motor_fsm.cpp
    src/primer_motor_fsm.h
    src/primer_motor_fsm.cpp
    src/pusher_tester.cpp
    src/indicator_led_fsm.h
    src/indicator_led_fsm.cpp
    src/trigger_servo_fsm.cpp
    src/trigger_servo_fsm.h
)

#==============================================================================
# Primer motor FSM test utility
#==============================================================================
add_executable(PrimerMotorFsmTester 
    src/fsm_list.h
    src/tinyfsm.h
    src/pusher_motor_fsm.h
    src/pusher_motor_fsm.cpp
    src/primer_motor_fsm.h
    src/primer_motor_fsm.cpp
    src/primer_tester.cpp
    src/indicator_led_fsm.h
    src/indicator_led_fsm.cpp
    src/trigger_servo_fsm.cpp
    src/trigger_servo_fsm.h
)
#==============================================================================
# Indicator LED FSM test utility
#==============================================================================
add_executable(IndicatorLedFsmTester 
    src/fsm_list.h
    src/tinyfsm.h
    src/pusher_motor_fsm.h
    src/pusher_motor_fsm.cpp
    src/primer_motor_fsm.h
    src/primer_motor_fsm.cpp
    src/indicator_tester.cpp
    src/indicator_led_fsm.h
    src/indicator_led_fsm.cpp
    src/trigger_servo_fsm.cpp
    src/trigger_servo_fsm.h
)
