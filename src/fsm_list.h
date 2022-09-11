#ifndef FSMLIST_H
#define FSMLIST_H

// libs
#include "tinyfsm.h"

// ours
#include "pusher_motor_fsm.h"
#include "trigger_servo_fsm.h"
#include "priming_motor_fsm.h"
#include "indicator_led_fsm.h"
#include "dirtaeb_fsm.h"

using fsm_list = tinyfsm::FsmList<DirtAEB, PusherMotor, TriggerServo, 
      PrimingMotor, IndicatorLed>;

/** dispatch event to the DirtAEB fsm */
template<typename E>
void send_event(E const & event)
{
  fsm_list::template dispatch<E>(event);
}

#endif
