#pragma once

// STL
#include <cstdint>

// libs
#include "tinyfsm.h"

// ============================================================================
// EVENT DECLARATIONS
// These are the events that *this* FSM listens for
// ============================================================================

// emitted to move the servo to a position
struct MoveServoEvent : tinyfsm::Event
{
    double position_deg;  // angle to move the servo to in degrees
    uint8_t speed;  // speed to move [0, 255]
};

// ============================================================================
// TriggerServo (FSM base class) declaration
// ============================================================================
class TriggerServo
: public tinyfsm::Fsm<TriggerServo>
{
public:
    /* default reaction for unhandled events */
    void react(tinyfsm::Event const &) {}

    /* default event handlers */
    virtual void react(MoveServoEvent const &) {}   // handled in derived state

    virtual void entry(void) {}  // some states have their own entry actions
    virtual void exit(void) {}   // some states have their own entry actions

    /**
     * Called by the servo driver to keep track of the servo position
     */
    void ServoUpdateCallback(double position_deg);

protected:
    // initial values for state vars
    static constexpr double init_target_pos_deg_ = 0;
    static constexpr double init_current_pos_deg_ = 100;  // force a movement

    // state vars
    static double target_pos_deg_;
    static double current_pos_deg_;
};

