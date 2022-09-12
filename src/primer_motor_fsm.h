#pragma once

// STL
#include <cstdint>

// libs
#include "tinyfsm.h"

// ============================================================================
// EVENT DECLARATIONS
// These are the events that *this* FSM listens for
// ============================================================================

// emitted to move the primer nut
struct RunPrimerEvent : tinyfsm::Event
{
    int8_t direction;  // direction of the motor (-1 = CCW, 0 = off, 1 = CW)
    uint8_t speed;  // speed to move [0,255]  
};

// emitted to stop the movement of the primer nut
struct StopPrimerEvent : tinyfsm::Event {};

// ============================================================================
// PrimerMotor (FSM base class) declaration
// ============================================================================
class PrimerMotor
: public tinyfsm::Fsm<PrimerMotor>
{
public:
    /* default reaction for unhandled events */
    void react(tinyfsm::Event const &) {};

    /* default event handlers */
    virtual void react(RunPrimerEvent const &) {};   // handled in derived state
    virtual void react(StopPrimerEvent const &) {};  // handled in derived state

    virtual void entry(void) {};  // some states have their own entry actions
    virtual void exit(void) {};   // some states have their own entry actions

protected:
    // initial values for state vars
    static constexpr int8_t initSpeed_ = 0;

    // state vars
    static uint8_t speed_;  // motor speed, [0, 255]
};

