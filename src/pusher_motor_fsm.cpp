// STL
#include <iostream>

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
class SpinningCW;
class SpinningCCW;
class Stopped;

/**
 * SpinningCW: The pusher motor is spinning CW
 */
class SpinningCW
: public PusherMotor
{
    void entry() override
    {
        // TODO spin the motor cw
        std::cout << "Spinning the motor CW at " << std::to_string(speed_)
                  << std::endl;
    };

    void react(StopPusherEvent const &e)
    {
        speed_ = 0;
        transit<Stopped>();
    };
    
    void react(RunPusherEvent const &e)
    {
        // save the speed
        speed_ = e.speed;

        if (e.direction == 0)
        {
            // stop the motor
            transit<Stopped>();
        } 
        else if (e.direction == 1)
        {
            // TODO adjust the current motor speed
            std::cout << "The speed was changed to " << std::to_string(speed_)
                      << std::endl;
        }
        else if (e.direction == -1)
        {
            // spin the motor CCW
            transit<SpinningCCW>();
        }
    };
};

/**
 * SpinningCCW: The pusher motor is spinning CCW
 */
class SpinningCCW
: public PusherMotor
{
    void entry() override
    {
        // TODO spin the motor CCW
        std::cout << "Spinning the motor CCW at " << std::to_string(speed_)
                  << std::endl;
    };

    void react(StopPusherEvent const &e)
    {
        // TODO stop the motor
        transit<Stopped>();
    };

    void react(RunPusherEvent const &e)
    {
        // save the speed
        speed_ = e.speed;

        if (e.direction == 0)
        {
            // stop the motor
            transit<Stopped>();
        } 
        else if (e.direction == 1)
        {
            // spin the motor CW
            transit<SpinningCW>();
        }
        else if (e.direction == -1)
        {
            // TODO adjust the speed of the motor
            std::cout << "The speed was changed to " << std::to_string(speed_)
                      << std::endl;
        }
    };
};

/**
 * Stopped: The pusher motor is stopped
 */
class Stopped
: public PusherMotor
{
    void entry()
    {
        // TODO stop spinning the motor
        speed_ = 0;
        std::cout << "The pusher motor has been stopped" << std::endl;
    };
    
    void react(RunPusherEvent const &e)
    {
        // save the speed
        speed_ = e.speed;

        if (e.direction == 1)
        {
            // spin the motor CW
            transit<SpinningCW>();
        }
        else if (e.direction == -1)
        {
            // spin the motor CCW
            transit<SpinningCCW>();
        }
    };
};

// set initialization values for the state machine
unsigned int PusherMotor::speed_ = PusherMotor::initSpeed_;

// set the starting state of the FSM
FSM_INITIAL_STATE(PusherMotor, Stopped)
