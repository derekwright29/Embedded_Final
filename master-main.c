#include "msp.h"
#include "port.h"
#include "timers.h"
#include <stdint.h>
/**
 * main.c
 */

volatile state_t state = IDLE;
volatile uint8_t pet = 0;
volatile uint8_t apps = 0;
volatile uint8_t lock = 0;
volatile uint8_t emergency = 0;

volatile uint8_t finger = 0;

volatile uint8_t fall = 0;


void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	config_buttons();
	//init_all(); //inits all ports and timers and only enables fingerprint interrupts. i.e. only fingerprint stuff is running.
	while(1) {
		if(finger) {
			state = ACTIVE;
			finger = 0;
			//enable button interrupts except for 911 button
			//enable accel interrupts
		}
		//handle button stuff in interrupts. should be just setting timer bits and setting variable to 1 or 0.
		if(pet) { //means timer triggered
			while(1);
		}
	}



}
