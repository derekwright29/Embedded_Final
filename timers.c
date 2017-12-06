/*
 * timers.c
 *
 *  Created on: Oct 26, 2017
 *      Author: derek
 */
#include "timers.h"

extern volatile state_t state;
extern volatile uint8_t pet;
extern volatile uint8_t apps;
extern volatile uint8_t feed;
extern volatile uint8_t emergency;

extern volatile uint8_t fall;

void config_TA0() {
	//timer stuff
	TIMER_A0->R = 0; // Reset count

	// SMCLK, Up mode, interrupts enabled, div set to 8,
	TIMER_A0->CCR[0] = 65535;    // Value to count to; for 1.4 second interrupts
	TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP | TIMER_A_CTL_ID__8;
	TIMER_A0->EX0 |= TIMER_A_EX0_TAIDEX_7; //divide again by 8

	/* Enable Interrupts in the NVIC */
	NVIC_EnableIRQ(TA0_0_IRQn);
}

void config_TA1() {
	TIMER_A1->R = 0; // Reset count

	// SMCLK, Up mode, interrupts enabled, div set to 8,
	TIMER_A1->CCR[0] = 3000;// optimal beeping frequency
	TIMER_A1->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP;

	/* Enable Interrupts in the NVIC */
	NVIC_EnableIRQ(TA1_0_IRQn);
}

void config_TA2() {
	//timer stuff
	TIMER_A2->R = 0; // Reset count

	// SMCLK, Up mode, interrupts enabled, div set to 8,
	TIMER_A2->CCR[0] = 65535;    // Value to count to; for 1.4 second interrupts
	TIMER_A2->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP | TIMER_A_CTL_ID__8;
	TIMER_A2->EX0 |= TIMER_A_EX0_TAIDEX_7; //divide again by 8

	/* Enable Interrupts in the NVIC */
	NVIC_EnableIRQ(TA2_0_IRQn);
}

void config_TA3() {
	//timer stuff
	TIMER_A3->R = 0; // Reset count

	// SMCLK, Up mode, interrupts enabled, div set to 8,
	TIMER_A3->CCR[0] = 65535;    // Value to count to; for 1.4 second interrupts
	TIMER_A3->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP | TIMER_A_CTL_ID__8;
	TIMER_A3->EX0 |= TIMER_A_EX0_TAIDEX_7; //divide again by 8

	/* Enable Interrupts in the NVIC */
	NVIC_EnableIRQ(TA3_0_IRQn);
}

void TA0_0_IRQHandler() {
	TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG; // clear flag
	pet = 1;
}

void TA1_0_IRQHandler() {
	TIMER_A1->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG; // clear flag
	apps = 1;
}
void TA2_0_IRQHandler() {
	TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG; // clear flag
	feed = 1;
}

void TA3_0_IRQHandler() {
	TIMER_A1->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG; // clear flag

}


