// STL
#include <iostream>

// libs
#include "tinyfsm.h"

// ours
#include "indicator_led_fsm.h"
#include "fsmlist.h"

// ============================================================================
// STATE DECLARATIONS
// Since this is a simple FSM it only has one state
// ============================================================================

/**
 * Simple idle state where when we recieve an event to change the led color,
 * we change it. No need to have any specialized states.
 */
class Idle
: public IndicatorLed
{
    // change the color of the LED
    void react(SetIndicatorEvent const &e)
    {
        // TODO change color of LED
        IndicatorLed::ledState_ = e.state;
        std::cout << "Indicator LED color was set to " << e.state << std::endl;
    };
};

// set initialization values for the state machine
Indication IndicatorLed::ledState_ = IndicatorLed::initLedState_;

// set the default state for the Indicatorled
FSM_INITIAL_STATE(IndicatorLed, Idle)
