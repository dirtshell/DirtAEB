// libs
#include "tinyfsm.h"

// ours
#include "dirtaeb_fsm.h"
#include "indicator_led_fsm.h"
#include "priming_motor_fsm.h"
#include "pusher_motor_fsm.h"
#include "fsmlist.h"

// ============================================================================
// STATE DEFINITIONS
// These are the states in the FSM
// ============================================================================

/**
 * Deprime1: Move carrier to far position
 *
 * The first step in the depriming sequence. This is also the startup state,
 * since once the blaster is finished starting up we want it to be in a 
 * deprimed state with the breach open.
 */
class Deprime1
: public DirtAEB
{
    void entry() override
    {
        // TODO emit event indicating to indicatorled to change color
        // TODO move carrier to the far position
    };

    /**
     * When the carrier has reached the far position, transition to the next
     * state.
     */
    void react(CarrierEvent const &e) 
    {
        // TODO transition if we are in far position
    };
};

/**
 * Deprime4: Close the catch
 * 
 * Last step in the depriming process. The catch servo is pulsed to the down
 * position to allow the catch to fall freely, and any indicator light that
 * was activated (either the startup light or the RTF light) is turned off.
 *
 * If this step was reached during the startup depriming process, we also mark
 * that the startup process has finished.
 */
class Deprime4
: public DirtAEB
{
    void entry() override
    {
        // TODO Pulse the catch servo to let it down
    };

    void react(CatchEvent const &e)
    {
        // TODO when the catch is down, go to the open breach (unprimed) state
    };

    void exit() override
    {
        // TODO change the indicator led to off
        
        // if we reached this point during startup, mark that startup is done
        if (startupFinished_ == false) { startupFinished_ = true; }
    };
};


// set initialization values for the state machine
CarrierPosition DirtAEB::carrierPos_ = DirtAEB::initCarrierPos_;
BoltPosition DirtAEB::boltPos_ = DirtAEB::initBolPos_;
FiringMode DirtAEB::firingMode_ = DirtAEB::initFiringMode_;
IndicatorState DirtAEB::indicatorState_ = DirtAEB::initIndicatorState_;
bool DirtAEB::triggerPressed_ = DirtAEB::initTriggerPressed_;
bool DirtAEB::catchCaught_ = DirtAEB::initCatchCaught_; 
bool DirtAEB::startupFinished_ = DirtAEB::initStartupFinished_;

// set the default starting state of the FSM
FSM_INITIAL_STATE(DirtAEB, Deprime1)
