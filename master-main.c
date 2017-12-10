#include "msp.h"
#include "port.h"
#include "timers.h"
#include "RTC.h"
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
volatile uint8_t print = 0;

volatile uint8_t fall = 0;

volatile uint32_t timer0 = 0;
volatile uint32_t timer1 = 0;
#define TASK_TIMER_CYCLES 4

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	config_buttons();
	config_buzzer();
	P2->IE |= BIT7;
	//init_all(); //inits all ports and timers and only enables fingerprint interrupts. i.e. only fingerprint stuff is running.
	while(finger) {
		if(state == IDLE) { //enable button interrupts except for 911 button
			P4->IE |= (BIT0);
			P5->IE |= (BIT6);
			P6->IE |= (BIT6);
		}
		state = ACTIVE;

		//enable accel interrupts
		//handle button stuff in interrupts. should be just setting timer bits and setting variable to 1 or 0.
		if(print) { //means timer triggered
			PrintReminders(GetButtonState(apps, lock, pet));
			//This: or Kayla's case functions.
			//bluetooth_send_n(uint8_t * message_buff);
			TIMER_A1->CCTL[0] |= TIMER_A_CCTLN_CCIE; //tunr on buzzer
		}
		if (fall) {
			P2->IE |= (BIT7); //turn on SOS button interrupt
		}
	}
	state = IDLE;
	while(1);


}
