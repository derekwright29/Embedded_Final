/*
 * FPS_Timer.h
 *
 *  Created on: Dec 4, 2017
 *      Author: Kayla
 */

#ifndef FPS_TIMER_H_
#define FPS_TIMER_H_

#include "msp.h"

/*STATES FOR STATE2 */
#define TIMER_START (0x00)
#define TIMER_DONE (0x01)

extern volatile int countTime;
extern volatile int freqDiv;

void timer_config();

volatile extern uint8_t state2;


#endif /* FPS_TIMER_H_ */
