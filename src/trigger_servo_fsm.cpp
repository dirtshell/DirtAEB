// STL
#include <iostream>
#include <cstdint>

// libs
#include "tinyfsm.h"

// ours
#include "trigger_servo_fsm.h"
#include "fsm_list.h"

// ============================================================================
// STATE DEFINITIONS
// These are the states in the FSM
// ============================================================================

// Forward declaration of all the states
class TriggerServoMoving;
class TriggerServoStopped;

/**
 * TriggerServoMoving: The servo is moving towards its target position
 */
class TriggerServoMoving
: public TriggerServo
{
    void entry() override
    {
        std::cout << "The trigger servo is moving to " << target_pos_deg_ 
                  << std::endl;
        // TODO move the servo towards the target position, and call a callback
        // when it reaches its target position
    }

    void react(MoveServoEvent const &e)
    {
        target_pos_deg_ = e.position_deg;
        transit<TriggerServoMoving>();
    }
};

/**
 * TriggerServoStopped: The servo is no longer moving
 */
class TriggerServoStopped
: public TriggerServo
{
    void entry() override
    {
        std::cout << "The trigger servo is stopped" << std::endl;
    }

    void react(MoveServoEvent const &e)
    {
        target_pos_deg_ = e.position_deg;
        transit<TriggerServoMoving>();
    }
};

void TriggerServo::ServoUpdateCallback(const double position_deg)
{
    current_pos_deg_ = position_deg;

    // if we have reached the target position, stop
    if (abs(current_pos_deg_ - target_pos_deg_) <= 1)
    {
        transit<TriggerServoStopped>();
    }
}

// set initialization values for the state machine
double TriggerServo::target_pos_deg_ = TriggerServo::init_target_pos_deg_;
double TriggerServo::current_pos_deg_ = TriggerServo::init_current_pos_deg_;

// set the starting state of the FSM
FSM_INITIAL_STATE(TriggerServo, TriggerServoMoving)
