#pragma once

// libs
#include "tinyfsm.h"

// ============================================================================
// EVENT DECLARATIONS
// These are events that *this* FSM listens for
// ============================================================================

// emitted when the color of the indicator LED needs to change
enum Indication { OFF, JAM, RTF, STARTUP };
struct SetIndicatorEvent : tinyfsm::Event
{
    Indication state;
};

// ============================================================================
// IndicatorLed (FSM base class) declaration
// ============================================================================
class IndicatorLed
: public tinyfsm::Fsm<IndicatorLed>
{
public:
    /* default reaction for unhandled events */
    void react(tinyfsm::Event const &) {};

    /* default event handlers */
    virtual void react(SetIndicatorEvent const &) {};
    void entry(void) {};  // this FSM has no entry actions
    void exit(void) {};   // this FSM has no exit actions

protected:
    // initial values for state vars
    static constexpr Indication initLedState_ = Indication::STARTUP;

    // state vars
    static Indication ledState_;
};
