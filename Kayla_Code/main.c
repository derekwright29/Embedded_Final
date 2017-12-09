#include "msp.h"
#include "FPS.h"
#include <string.h>
#include "UART.h"
#include "FPS_Timer.h"
#include "Port.h"

/**
 * main.c
 */

 volatile FP_cmd_packet cp;
 volatile uint8_t state = FP_SEND_CMD;
 volatile uint8_t state2 = FP_DONT_CARE;
 volatile uint8_t state3 = FP_DONT_CARE;
 volatile  uint8_t data_databuf[30];
 volatile  uint8_t rsp_databuf[12];
 volatile  FP_resp rp;
 volatile int i = 0;
 volatile int freqDiv = 0;

 volatile int countTime = 0;

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
    UART_ConfigureA2();
    UART_ConfigureA0();
    GPIO_config();
     timer_config();
    int id = 0;
    int begin = 0;



    __enable_irq();


   Open(1);
   SetLED(0);
   SetLED(1);

   /*while(!begin){
     id = IDENTIFY_PRINT();
     if(id < 20){
         begin = 1;
     }
     else{
         begin = 0;
     }
   } */

   while(1){
       if(state3 == FP_DELETE1){
                  FPS_Delete_ID();
                  P2->OUT &= ~(BIT0 | BIT2);
                  state3 = FP_DONT_CARE;
              }
              if(state3 == FP_DELETEALL){
                  FPS_Delete_ALL();
                  P2->OUT &= ~(BIT0 | BIT2) ;
                  state3 = FP_DONT_CARE;
              }
              if(state3 == FP_ENROLL){
                  ENROLLPRINT();
                  P2->OUT &= ~(BIT2);
                  state3 = FP_DONT_CARE;
              }

         // Identify fingerprint test

                  while(IsFingerPressed() == 0){
                      freqDiv = 50;
                      TIMER_A0->CCR[0] = 50000;
                      TIMER_A0->CCTL[0] |= TIMER_A_CCTLN_CCIE;   // Capture/Compare interrupt enabled @ peripheral  (CCIE flag enabled)

                      if(state3 == FP_DELETE1){
                          TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE;
                          FPS_Delete_ID();
                          P2->OUT &= ~(BIT0 | BIT2);
                          state3 = FP_DONT_CARE;
                          TIMER_A0->CCTL[0] |= TIMER_A_CCTLN_CCIE;
                      }
                      if(state3 == FP_DELETEALL){
                          TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE;
                          FPS_Delete_ALL();
                          P2->OUT &= ~(BIT0 | BIT2) ;
                          state3 = FP_DONT_CARE;
                          TIMER_A0->CCTL[0] |= TIMER_A_CCTLN_CCIE;
                      }
                      if(state3 == FP_ENROLL){
                          TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE;
                          ENROLLPRINT();
                          P2->OUT &= ~(BIT2);
                          state3 = FP_DONT_CARE;
                          TIMER_A0->CCTL[0] |= TIMER_A_CCTLN_CCIE;
                      }
                  }

                  TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE;

                  CaptureFinger(1);
                  int id = ID_print();
                  char strID[3] = 0;
                  itoa(id, strID);
                  uint32_t lenID = strlen((char *)strID);

                  if (id <20)
                  {//if the fingerprint matches, provide the matching template ID
                      UART_send_A0("Verified ID: ", 13);
                      UART_send_A0(&strID,lenID);
                      UART_send_byteA0(0x0A);
                  }
                  else
                  {//if unable to recognize
                      UART_send_A0("Finger not found\n", 17);
                  }
            }

        }


