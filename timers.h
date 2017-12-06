/*
 * timers.h
 *
 *  Created on: Oct 26, 2017
 *      Author: derek
 */

#ifndef TIMERS_H_
#define TIMERS_H_

typdef enum {
	TIMER0,
	TIMER1,
	TIMER2,
	TIMER3
}Timer_t;

void config_TA(Timer_t module);
void config_TA0(void);
void config_TA1(void);
void TA0_0_IRQHandler();
void TA1_0_IRQHandler();
void TA2_0_IRQHandler();
void TA3_0_IRQHandler();
void config_SysTick(void);
void SysTick_Handler();

#endif /* TIMERS_H_ */
