// STL
#include <iostream>
#include <cstdint>

// libs
#include "tinyfsm.h"

// ours
#include "pusher_motor_fsm.h"
#include "fsm_list.h"

// ============================================================================
// STATE DEFINITIONS
// These are the states in the FSM
// ============================================================================

// Forward declaration of all the states
class PusherMotorSpinningCW;
class PusherMotorSpinningCCW;
class PusherMotorStopped;

/**
 * PusherMotorSpinningCW: The pusher motor is spinning CW
 */
class PusherMotorSpinningCW
: public PusherMotor
{
    void entry() override
    {
        // TODO spin the motor cw
        std::cout << "Spinning the pusher motor CW at " << speed_ << std::endl;
    }

    void react(StopPusherEvent const &e)
    {
        speed_ = 0;
        transit<PusherMotorStopped>();
    }
    
    void react(RunPusherEvent const &e)
    {
        // save the speed
        speed_ = e.speed;

        if (e.direction == PusherMotorDirection::OFF)
        {
            // stop the motor
            transit<PusherMotorStopped>();
        } 
        else if (e.direction == PusherMotorDirection::CW)
        {
            // TODO adjust the current motor speed
            std::cout << "The pusher motor speed was changed to " << speed_ 
                      << std::endl;
        }
        else if (e.direction == PusherMotorDirection::CCW)
        {
            // spin the motor CCW
            transit<PusherMotorSpinningCCW>();
        }
    }
};

/**
 * PusherMotorSpinningCCW: The pusher motor is spinning CCW
 */
class PusherMotorSpinningCCW
: public PusherMotor
{
    void entry() override
    {
        // TODO spin the motor CCW
        std::cout << "Spinning the pusher motor CCW at " << speed_ << std::endl;
    }

    void react(StopPusherEvent const &e)
    {
        // TODO stop the motor
        transit<PusherMotorStopped>();
    }

    void react(RunPusherEvent const &e)
    {
        // save the speed
        speed_ = e.speed;

        if (e.direction == PusherMotorDirection::OFF)
        {
            // stop the motor
            transit<PusherMotorStopped>();
        } 
        else if (e.direction == PusherMotorDirection::CW)
        {
            // spin the motor CW
            transit<PusherMotorSpinningCW>();
        }
        else if (e.direction == PusherMotorDirection::CCW)
        {
            // TODO adjust the speed of the motor
            std::cout << "The pusher motor speed was changed to " 
                      << speed_ << std::endl;
        }
    }
};

/**
 * PusherMotorStopped: The pusher motor is stopped
 */
class PusherMotorStopped
: public PusherMotor
{
    void entry()
    {
        // TODO stop spinning the motor
        speed_ = 0;
        std::cout << "The pusher motor has been stopped" << std::endl;
    }
    
    void react(RunPusherEvent const &e)
    {
        // save the speed
        speed_ = e.speed;

        if (e.direction == PusherMotorDirection::CW)
        {
            // spin the motor CW
            transit<PusherMotorSpinningCW>();
        }
        else if (e.direction == PusherMotorDirection::CCW)
        {
            // spin the motor CCW
            transit<PusherMotorSpinningCCW>();
        }
    }
};

// set initialization values for the state machine
uint8_t PusherMotor::speed_ = PusherMotor::init_speed_;

// set the starting state of the FSM
FSM_INITIAL_STATE(PusherMotor, PusherMotorStopped)
