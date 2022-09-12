// STL
#include <iostream>
#include <cstdint>

// libs
#include "tinyfsm.h"

// ours
#include "primer_motor_fsm.h"
#include "fsm_list.h"

// ============================================================================
// STATE DEFINITIONS
// These are the states in the FSM
// ============================================================================

// Forward declaration of all the states
class PrimerMotorSpinningCW;
class PrimerMotorSpinningCCW;
class PrimerMotorStopped;

/**
 * PrimerMotorSpinningCW: The primer motor is spinning CW
 */
class PrimerMotorSpinningCW
: public PrimerMotor
{
    void entry() override
    {
        // TODO spin the motor cw
        std::cout << "Spinning the primer motor CW at " 
                  << std::to_string(speed_) << std::endl;
    };

    void react(StopPrimerEvent const &e)
    {
        speed_ = 0;
        transit<PrimerMotorStopped>();
    };
    
    void react(RunPrimerEvent const &e)
    {
        // save the speed
        speed_ = e.speed;

        if (e.direction == 0)
        {
            // stop the motor
            transit<PrimerMotorStopped>();
        } 
        else if (e.direction == 1)
        {
            // TODO adjust the current motor speed
            std::cout << "The primer motor speed was changed to " 
                      << std::to_string(speed_) << std::endl;
        }
        else if (e.direction == -1)
        {
            // spin the motor CCW
            transit<PrimerMotorSpinningCCW>();
        }
    };
};

/**
 * PrimerMotorSpinningCCW: The primer motor is spinning CCW
 */
class PrimerMotorSpinningCCW
: public PrimerMotor
{
    void entry() override
    {
        // TODO spin the motor CCW
        std::cout << "Spinning the primer motor CCW at " 
                  << std::to_string(speed_) << std::endl;
    };

    void react(StopPrimerEvent const &e)
    {
        // TODO stop the motor
        transit<PrimerMotorStopped>();
    };

    void react(RunPrimerEvent const &e)
    {
        // save the speed
        speed_ = e.speed;

        if (e.direction == 0)
        {
            // stop the motor
            transit<PrimerMotorStopped>();
        } 
        else if (e.direction == 1)
        {
            // spin the motor CW
            transit<PrimerMotorSpinningCW>();
        }
        else if (e.direction == -1)
        {
            // TODO adjust the speed of the motor
            std::cout << "The primer motor speed was changed to " 
                      << std::to_string(speed_) << std::endl;
        }
    };
};

/**
 * PrimerMotorStopped: The primer motor is stopped
 */
class PrimerMotorStopped
: public PrimerMotor
{
    void entry()
    {
        // TODO stop spinning the motor
        speed_ = 0;
        std::cout << "The primer motor has been stopped" << std::endl;
    };
    
    void react(RunPrimerEvent const &e)
    {
        // save the speed
        speed_ = e.speed;

        if (e.direction == 1)
        {
            // spin the motor CW
            transit<PrimerMotorSpinningCW>();
        }
        else if (e.direction == -1)
        {
            // spin the motor CCW
            transit<PrimerMotorSpinningCCW>();
        }
    };
};

// set initialization values for the state machine
uint8_t PrimerMotor::speed_ = PrimerMotor::initSpeed_;

// set the starting state of the FSM
FSM_INITIAL_STATE(PrimerMotor, PrimerMotorStopped)
