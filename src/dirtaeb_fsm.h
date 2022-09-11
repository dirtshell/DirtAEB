#pragma once

// libs
#include "tinyfsm.h"

// ours
#include "pusher_motor_fsm.h"
//#include "trigger_servo_fsm.h"
//#include "priming_motor_fsm.h"
#include "indicator_led_fsm.h"

// ============================================================================
// EVENT DECLARATIONS
// These are events that *this* FSM listens for
// ============================================================================

// basic button event
struct ButtonEvent : tinyfsm::Event
{
    bool pressed;
};

// emitted when the trigger position changes
struct TriggerEvent : ButtonEvent {};

// emitted when the bolts position changes
enum class BoltPosition { OPEN, CLOSED, UNKNOWN };
struct BoltEvent : tinyfsm::Event
{
    BoltPosition position;
};

// emitted when the "primer" button is pressed
struct PrimeEvent : tinyfsm::Event {};

// emitted when the "primer" button is held down for 3 seconds
struct DeprimeEvent : tinyfsm::Event {};

// emitted when the catch position changes
struct CatchEvent : tinyfsm::Event
{
    bool caught;
};

// emitted when the firing mode selector changes position
enum class FiringMode { SEMI, AUTO, SAFE };
struct SelectorEvent : tinyfsm::Event
{
    FiringMode mode;
};

// emitted when the carrier position changes
enum class CarrierPosition { FRONT, BACK, UNKNOWN };
struct CarrierEvent : tinyfsm::Event
{
    CarrierPosition pos;
};

// ============================================================================
// DirtAEB (FSM base class) declaration
// ============================================================================
class DirtAEB
: public tinyfsm::Fsm<DirtAEB>
{
public:
    /* default reaction for unhandled events */
    void react(tinyfsm::Event const &) {};

    /* default event handlers */
    virtual void react(TriggerEvent const &) {};   // handled in derived state
    virtual void react(BoltEvent const &) {};      // handled in derived state
    virtual void react(PrimeEvent const &) {};     // handled in derived state
    virtual void react(DeprimeEvent const &) {};   // handled in derived state
    virtual void react(CatchEvent const &) {};     // handled in derived state
    virtual void react(CarrierEvent const &) {};   // handled in derived state
    void react(SelectorEvent const &e);     // handled by FSM

    virtual void entry(void) {};  // some states have their own entry actions
    virtual void exit(void) {};   // some states have their own exit actions
                                  
protected:
    // initial values for state vars
    static constexpr CarrierPosition initCarrierPos_ = CarrierPosition::UNKNOWN;
    static constexpr BoltPosition initBoltPos_ = BoltPosition::UNKNOWN;
    static constexpr FiringMode initFiringMode_ = FiringMode::SAFE;
    static constexpr bool initTriggerPressed_ = false;
    static constexpr bool initCatchCaught_ = false;
    static constexpr bool initStartupFinished_ = false;

    // state vars
    static CarrierPosition carrierPos_;
    static BoltPosition boltPos_;
    static FiringMode firingMode_;
    static bool triggerPressed_;
    static bool catchCaught_;  // aka "primed"
    static bool startupFinished_;  // true when we have reset to the start state
};
    
