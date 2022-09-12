#pragma once

// STL
#include <cstdint>

// libs
#include "tinyfsm.h"

// ============================================================================
// EVENT DECLARATIONS
// These are the events that *this* FSM listens for
// ============================================================================

// emitted to move the pusher
enum class PusherMotorDirection { CCW, OFF, CW };
struct RunPusherEvent : tinyfsm::Event
{
    PusherMotorDirection direction;
    uint8_t speed;  // speed to move [0,255]  
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
    static constexpr int8_t init_speed_ = 0;

    // state vars
    static uint8_t speed_;  // motor speed, [0, 255]
};

