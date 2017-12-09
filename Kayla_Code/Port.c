/*
 * Port.c
 *
 *  Created on: Dec 4, 2017
 *      Author: Kayla
 */

#include "msp.h"
#include "FPS.h"
#include "Port.h"

void PORT1_IRQHandler(){
     int i = 0;
     for(i=0; i<= 10; i++); //delay to allow for debouncing

     if(state3 == FP_DELETE){
         if(P1->IFG & BIT1) {
             state3 = FP_DELETE1;
             P1->IFG &= ~BIT1; //clear flag
             }
          if(P1->IFG & BIT4) {
              state3 = FP_DELETEALL;
              P1->IFG &= ~BIT4; //clear flag
          }
         }
     else{
         if(P1->IFG & BIT1) {
              state3 = FP_DELETE;
              P2->OUT |= (BIT0 | BIT2);
              P1->IFG &= ~BIT1; //clear flag
         }
         if(P1->IFG & BIT4) {
             state3 = FP_ENROLL;
             P2->OUT |= (BIT2);
             P1->IFG &= ~BIT4; //clear flag
         }
      }
    }




  void GPIO_config(){
    /* Left and right button configure */
       P1->SEL0 &= ~(BIT1 | BIT4);     //Use the OR function to set BIT1 and BIT4 to general IO Mode
       P1->SEL1 &= ~(BIT1 | BIT4) ;     //^^^
       P1->DIR &= ~(BIT1 | BIT4);       //Direction pin is set to zero since BIT1 and BIT4 are inputs
       P1->REN |= BIT1 | BIT4 ;        //REN is set to 1 at BIT1 and BIT4 in order to enable pullup/pulldown
       P1->OUT |= BIT1 | BIT4 ;        //Output resgister is set to 1 to enable the pullup resister
       P1->IE |= BIT1 | BIT4 ;          //interrupts are enabled
       P1->IES |= BIT1  | BIT4;        //high-to-low transition
       P1->IFG = 0;                    //interrupt flag is set to zero
       P2->SEL0 &= ~(BIT0 | BIT2| BIT1) ;     //GENERAL I/O for RED and BLUE
       P2->SEL1 &= ~(BIT0 | BIT2 | BIT1) ;     //^^^
       P2->OUT &= ~(BIT0 | BIT2 | BIT1) ;      //Direction is set to 1 so the LEDs act as outputs
       P2->DIR |= (BIT0 | BIT2 | BIT1);         //Output is set to low so the LED will only turn on when the interrupt is called

       /* PCB Button Input configuration */
       P2->SEL0 &= ~BIT7;
       P2->SEL1 &= ~BIT7;
       P2->DIR &= ~BIT7;
       P2->IES &= ~BIT7; // Low to High transition
       P2->IE |= BIT7;
       P2->IFG = 0;                    //interrupt flag is set to zero

       P4->SEL0 &= ~BIT0;
       P4->SEL1 &= ~BIT0;
       P4->DIR &= ~BIT0;
       P4->IE |= BIT0;
       P4->IES &= ~BIT0; // Low to High transition
       P4->IFG = 0;                    //interrupt flag is set to zero

       P5->SEL0 &= ~BIT6;
       P5->SEL1 &= ~BIT6;
       P5->DIR &= ~BIT6;
       P5->IE |= BIT6;
       P5->IES &= ~BIT6; // Low to High transition
       P5->IFG = 0;                    //interrupt flag is set to zero

       P6->SEL0 &= ~BIT6;
       P6->SEL1 &= ~BIT6;
       P6->DIR &= ~BIT6;
       P6->IE |= BIT6;
       P6->IES &= ~BIT6; // Low to High transition
       P6->IFG = 0;                    //interrupt flag is set to zero




        /* Enable Interrupts in the NVIC */
       NVIC_EnableIRQ(PORT1_IRQn);
       NVIC_EnableIRQ(PORT2_IRQn);
       NVIC_EnableIRQ(PORT4_IRQn);
       NVIC_EnableIRQ(PORT5_IRQn);
       NVIC_EnableIRQ(PORT6_IRQn);
  }
