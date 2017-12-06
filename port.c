/*
 * port.c
 *
 *  Created on: Nov 28, 2017
 *      Author: admin
 */
#include "msp.h"

volatile uint8_t pet = 0;
volatile uint8_t apps = 0;
volatile uint8_t lock = 0;
volatile uint8_t emergency = 0;

volatile uint8_t finger = 0;

volatile uint8_t fall = 0;

void config_buttons(void) {
	//SOS BUTTON
	P2->DIR &= ~(BIT7); //input
	P2->REN |= (BIT7); //Enabled pullup/pulldown resistors
	P2->OUT |= (BIT7); //Pullup selected
	P2->IFG = 0; //Clears interrupt flags
	P2->IES |= (BIT7); //Set high to low transition

	NVIC_EnableIRQ(PORT2_IRQn);

	//APPS BUTTON
	P4->DIR &= ~(BIT0); //input
	P4->REN |= (BIT0); //Enabled pullup/pulldown resistors
	P4->OUT |= (BIT0); //Pullup selected
	P4->IFG = 0; //Clears interrupt flags
	P4->IES |= (BIT0); //Set high to low transition

	NVIC_EnableIRQ(PORT4_IRQn);

	//LOCKS BUTTON
	P5->DIR &= ~(BIT6); //input
	P5->REN |= (BIT6); //Enabled pullup/pulldown resistors
	P5->OUT |= (BIT6); //Pullup selected
	P5->IFG = 0; //Clears interrupt flags
	P5->IES |= (BIT6); //Set high to low transition

	NVIC_EnableIRQ(PORT5_IRQn);

	//PETS BUTTON
	P6->DIR &= ~(BIT6); //input
	P6->REN |= (BIT6); //Enabled pullup/pulldown resistors
	P6->OUT |= (BIT6); //Pullup selected
	P6->IFG = 0; //Clears interrupt flags
	P6->IES |= (BIT6); //Set high to low transition

	NVIC_EnableIRQ(PORT6_IRQn);
}


void PORT2_IRQHandler(void) {
	state = TASK_ACTIVE;
	emergency = 1;
}
void PORT4_IRQHandler(void) {
	state = TASK_ACTIVE;
	apps = 1;
}
void PORT5_IRQHandler(void) {
	state = TASK_ACTIVE;
	lock = 1;
}
void PORT6_IRQHandler(void) {
	state = TASK_ACTIVE;
	pet = 1;
}




