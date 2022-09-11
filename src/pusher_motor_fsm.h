#pragma once

// libs
#include "tinyfsm.h"

// ============================================================================
// EVENT DECLARATIONS
// These are the events that *this* FSM listens for
// ============================================================================

// emitted to move the pusher
struct RunPusherEvent : tinyfsm::Event
{
    int direction;  // direction of the motor (-1 = CCW, 0 = off, 1 = CW)
    unsigned int speed;  // speed to move [0,255]  
};

// emitted to stop the movement of the pusher
struct StopPusherEvent : tinyfsm::Event {};

// ============================================================================
// PusherMotor (FSM base class) declaration
// ============================================================================
class PusherMotor
: public tinyfsm::Fsm<PusherMotor>
{
public:
    /* default reaction for unhandled events */
    void react(tinyfsm::Event const &) {};

    /* default event handlers */
    virtual void react(RunPusherEvent const &) {};   // handled in derived state
    virtual void react(StopPusherEvent const &) {};  // handled in derived state

    virtual void entry(void) {};  // some states have their own entry actions
    virtual void exit(void) {};   // some states have their own entry actions

protected:
    // initial values for state vars
    static constexpr int initSpeed_ = 0;

    // state vars
    static unsigned int speed_;  // motor speed, [0, 255]
};

