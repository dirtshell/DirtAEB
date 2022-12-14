#pragma once

// libs
#include "tinyfsm.h"

// ours
#include "pusher_motor_fsm.h"
#include "trigger_servo_fsm.h"
#include "primer_motor_fsm.h"
#include "indicator_led_fsm.h"
#include "dirtaeb_fsm.h"

using fsm_list = tinyfsm::FsmList<PusherMotor, PrimerMotor, IndicatorLed, TriggerServo>;

/** dispatch event to the FSMs */
template<typename E>
void send_event(E const & event)
{
  fsm_list::template dispatch<E>(event);
}
