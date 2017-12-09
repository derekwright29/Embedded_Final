/*
 * FPS_Timer.c
 *
 *  Created on: Nov 29, 2017
 *      Author: Kayla
 */

#include "FPS_Timer.h"
#include "msp.h"



void TA0_0_IRQHandler()
{
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    countTime ++;
     if(countTime == freqDiv) {
           countTime = 0;
           UART_send_A0("Please press finger\n", 20);
           TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE;   // Capture/Compare interrupt disabled @ peripheral  (CCIE flag enabled)
       }
}

void timer_config(){
    TIMER_A0->R = 0 ;         // Reset count
    TIMER_A0->CTL |= (TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_ID__8 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_IE ) ; //Set SMCLK Multiplexer mode clock source, divide by 1
        // and Up mode (BIT5,BIT4 = 01) and enable interrupt for timer register (enable TAIE flag)
    TIMER_A0->CCR[0] = 37500;    // Value to count to TAxCCRn holds the data for the comparison to the timer value
          //in the Timer_A Register, TAxR.
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE;   // Capture/Compare interrupt enabled @ peripheral  (CCIE flag enabled)
    TIMER_A0->CTL &= ~(TIMER_A_CCTLN_CAP); // set BIT8 to zero to set to compare mode (CAP = 0)
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG ; //Clear CCIFG interrupt (BIT0)
    TIMER_A0->CTL &= ~TIMER_A_CTL_IFG;  //Clear TAIFG interrupt (BIT0)
    /* Enable Interrupts in the NVIC */
      NVIC_EnableIRQ(TA0_0_IRQn );
  }
