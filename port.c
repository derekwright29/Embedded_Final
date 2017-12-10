/*
 * port.c
 *
 *  Created on: Nov 28, 2017
 *      Author: admin
 */
#include "msp.h"
#include "port.h"
 uint8_t G_phrase[] = "Feed Pets! ";
  uint8_t B_phrase[] = "Lock Doors! ";
  uint8_t W_phrase[] = "Turn Off Stove! ";

extern volatile state_t state;

extern volatile uint8_t pet;
extern volatile uint8_t apps;
extern volatile uint8_t lock;
extern volatile uint8_t emergency;

extern volatile uint8_t finger;

extern volatile uint8_t fall;

void update_state_t(void) {
	if (pet || apps || lock)
		{
			state = TASK_ACTIVE;
		}
	else state = ACTIVE;
}

void config_buttons(void) {
	//SOS BUTTON -- Red
	P2->DIR &= ~(BIT7); //input
	P2->REN |= (BIT7); //Enabled pullup/pulldown resistors
	P2->OUT |= (BIT7); //Pullup selected
	P2->IFG = 0; //Clears interrupt flags
	P2->IES |= (BIT7); //Set high to low transition

	NVIC_EnableIRQ(PORT2_IRQn);

	//APPS BUTTON -- Green
	P4->DIR &= ~(BIT0); //input
	P4->REN |= (BIT0); //Enabled pullup/pulldown resistors
	P4->OUT |= (BIT0); //Pullup selected
	P4->IFG = 0; //Clears interrupt flags
	P4->IES |= (BIT0); //Set high to low transition

	NVIC_EnableIRQ(PORT4_IRQn);

	//LOCKS BUTTON -- blue
	P5->DIR &= ~(BIT6); //input
	P5->REN |= (BIT6); //Enabled pullup/pulldown resistors
	P5->OUT |= (BIT6); //Pullup selected
	P5->IFG = 0; //Clears interrupt flags
	P5->IES |= (BIT6); //Set high to low transition

	NVIC_EnableIRQ(PORT5_IRQn);

	//PETS BUTTON -- white
	P6->DIR &= ~(BIT6); //input
	P6->REN |= (BIT6); //Enabled pullup/pulldown resistors
	P6->OUT |= (BIT6); //Pullup selected
	P6->IFG = 0; //Clears interrupt flags
	P6->IES |= (BIT6); //Set high to low transition

	NVIC_EnableIRQ(PORT6_IRQn);
}

void config_buzzer() {
	//config buzzer
	P3->SEL0 &= ~BIT0;
	P3->SEL1 &= ~BIT0;
	P3->DIR |= BIT0; //output
	P3->OUT &= ~BIT0; //low
}

REMINDER_STATUS GetButtonState(uint8_t G_ID, uint8_t B_ID, uint8_t W_ID){
           REMINDER_STATUS state;
           switch(G_ID)
             {
                 case 1:
                     if(B_ID){
                         if(W_ID){
                             state = GWB;
                         }
                         else{
                             state = GB;
                         }
                     }
                     else{
                         if(W_ID){
                             state = GW;
                         }
                         else{
                             state = G;
                         }
                     }
                     break;
                 case 0:
                     if(B_ID){
                         if(W_ID){
                             state = BW;
                         }
                         else{
                             state = B;
                         }
                     }
                     else{
                         if(W_ID){
                             state = W;
                         }
                         else{
                             state = NONE;
                         }
                     }
                     break;
             }
             return state;
         }

    void PrintReminders(REMINDER_STATUS status){
        switch(status)
        {
            case GWB:
                UART_send_A0(G_phrase, G_len);
                UART_send_A0(B_phrase, B_len);
                UART_send_A0(W_phrase, W_len);
                UART_send_byteA0(0x0A);
                break;

            case G:
                UART_send_A0(G_phrase, G_len);
                UART_send_byteA0(0x0A);
                break;

            case B:
                UART_send_A0(B_phrase, B_len);
                UART_send_byteA0(0x0A);
                break;

            case W:
                UART_send_A0(W_phrase, W_len);
                UART_send_byteA0(0x0A);
                break;

            case GB:
                UART_send_A0(G_phrase, G_len);
                UART_send_A0(B_phrase, B_len);
                UART_send_byteA0(0x0A);
                break;

            case GW:
                UART_send_A0(G_phrase, G_len);
                UART_send_A0(W_phrase, W_len);
                UART_send_byteA0(0x0A);
                break;

            case BW:
                UART_send_A0(B_phrase, B_len);
                UART_send_A0(W_phrase, W_len);
                UART_send_byteA0(0x0A);
                break;

            default:
            		break;
        }
        return;
    }

void UART_send_A0(uint8_t * data, uint32_t length){
    int i = 0;
    for(i=0 ; i<length ; i++){
        UART_send_byteA0(data[i]);
    }
}

void UART_send_byteA0(uint8_t data){
   while((EUSCI_A0->STATW & EUSCI_A_STATW_BUSY)); //May have to change to using the TXIFG flag
        EUSCI_A0->TXBUF = data;
}


void PORT2_IRQHandler(void) {
	state = SOS;
	TIMER_A3->CCTL[0] |= TIMER_A_CCTLN_CCIE; //enable emergency timer
	emergency = 1; //set back to zero once timer goes off.
}
void PORT4_IRQHandler(void) {
	if(apps) {
		apps = 0;
		state = TASK_ACTIVE;

		TIMER_A0->CCTL[0] |= TIMER_A_CCTLN_CCIE; //enable task timer
	}
}
void PORT5_IRQHandler(void) {
	state = TASK_ACTIVE;
	lock = 1;
	TIMER_A0->CCTL[0] |= TIMER_A_CCTLN_CCIE; //enable task timer
}
void PORT6_IRQHandler(void) {
	state = TASK_ACTIVE;
	pet = 1;
	TIMER_A0->CCTL[0] |= TIMER_A_CCTLN_CCIE; //enable task timer
}




