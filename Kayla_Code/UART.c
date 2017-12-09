/*
 * UART.c
 *
 *  Created on: Nov 21, 2017
 *      Author: Kayla
 */

#include "msp.h"
#include "UART.h"
#include "FPS.h"

extern volatile int i;


void WaitResponse(){
        i = 0;
         while(state == FP_WAIT_RSP);
               i = 0;
         if(state == FP_PROCESS_RSP){
             ProcessRSP();
         }
             i = 0;
     }


 EUSCIA2_IRQHandler(){
     if(EUSCI_A2->IFG & EUSCI_A_IFG_RXIFG){
         if (state == FP_WAIT_RSP)
             {
                 rsp_databuf[i++]= EUSCI_A2->RXBUF;
                 if(i == FP_RSP_PACKET_LENGTH)
                     {
                         state = FP_PROCESS_RSP;
                         EUSCI_A2->IFG &= ~EUSCI_A_IFG_RXIFG;
                     }
             }
         else if (state == FP_WAIT_DATA)
             {
                 data_databuf[i++] = EUSCI_A2->RXBUF;
                 if(i == FP_DATA_PACKET_LENGTH )
                     {
                         state = FP_PROCESS_RSP;
                         EUSCI_A2->IFG &= ~EUSCI_A_IFG_RXIFG;
                     }
             }
         }
     }


void UART_send_byteA2(uint8_t data){
   while((EUSCI_A2->STATW & EUSCI_A_STATW_BUSY)); //May have to change to using the TXIFG flag
        EUSCI_A2->TXBUF = data;
}

void UART_send_A2(uint8_t * data, uint32_t length){
    int i = 0;
    for(i=0 ; i<length ; i++){
        UART_send_byteA2(data[i]);
    }
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


void UART_ConfigureA0(){

    CS->KEY = CS_KEY_VAL;                   // Unlock CS module for register access
    CS->CTL0 = 0;                           // Reset tuning parameters
    CS->CTL0 = CS_CTL0_DCORSEL_3;           // Set DCO to 12MHz (nominal, center of 8-16MHz range)
    CS->CTL1 = CS_CTL1_SELA_2 |             // Select ACLK = REFO
    CS_CTL1_SELS_3 |                // SMCLK = DCO
    CS_CTL1_SELM_3;                 // MCLK = DCO
    CS->KEY = 0;                            // Lock CS module from unintended accesses

    P1->SEL0 |= BIT2 | BIT3;
    P1->SEL1 &= ~(BIT2 | BIT3);
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_MODE_0; // UART Mode
    EUSCI_A0->CTLW0 &= ~(EUSCI_A_CTLW0_PEN | EUSCI_B_CTLW0_MSB | EUSCI_B_CTLW0_SEVENBIT | EUSCI_A_CTLW0_SPB); //Set No Parity, LSB First, 8-bit data, 1 start bit, 1 stop bit

    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK;

    // Baud Rate calculation
         // 12000000/(16*9600) = 78.125
         // Fractional portion = 0.125
         // User's Guide Table 21-4: UCBRSx = 0x10
         // UCBRFx = int ( (78.125-78)*16) = 2
         EUSCI_A0->BRW = 78;                     // 12000000/16/9600
         EUSCI_A0->MCTLW = (2 << EUSCI_A_MCTLW_BRF_OFS) |
                 EUSCI_A_MCTLW_OS16;

         EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; // Initialize eUSCI
         EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG;    // Clear eUSCI RX interrupt flag
         EUSCI_A0->IE |= EUSCI_A_IE_RXIE;        // Enable USCI_A0 RX interrupt

    NVIC_EnableIRQ(EUSCIA0_IRQn);
}

void UART_ConfigureA2(){

    CS->KEY = CS_KEY_VAL;                   // Unlock CS module for register access
    CS->CTL0 = 0;                           // Reset tuning parameters
    CS->CTL0 = CS_CTL0_DCORSEL_3;           // Set DCO to 12MHz (nominal, center of 8-16MHz range)
    CS->CTL1 = CS_CTL1_SELA_2 |             // Select ACLK = REFO
          CS_CTL1_SELS_3 |                // SMCLK = DCO
          CS_CTL1_SELM_3;                 // MCLK = DCO
    CS->KEY = 0;                            // Lock CS module from unintended accesses

    P3->SEL0 |= (BIT2 | BIT3);
    P3->SEL1 &= ~(BIT2 | BIT3);
    EUSCI_A2->CTLW0 |= EUSCI_A_CTLW0_MODE_0; // UART Mode
    EUSCI_A2->CTLW0 &= ~(EUSCI_A_CTLW0_PEN | EUSCI_B_CTLW0_MSB | EUSCI_B_CTLW0_SEVENBIT | EUSCI_A_CTLW0_SPB); //Set No Parity, LSB First, 8-bit data, 1 start bit, 1 stop bit

    EUSCI_A2->CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK;

    // Baud Rate calculation
       // 12000000/(16*9600) = 78.125
       // Fractional portion = 0.125
       // User's Guide Table 21-4: UCBRSx = 0x10
       // UCBRFx = int ( (78.125-78)*16) = 2
       EUSCI_A2->BRW = 78;                     // 12000000/16/9600
       EUSCI_A2->MCTLW = (2 << EUSCI_A_MCTLW_BRF_OFS) |
               EUSCI_A_MCTLW_OS16;

       EUSCI_A2->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; // Initialize eUSCI
       EUSCI_A2->IFG &= ~EUSCI_A_IFG_RXIFG;    // Clear eUSCI RX interrupt flag
       EUSCI_A2->IE |= EUSCI_A_IE_RXIE;        // Enable USCI_A0 RX interrupt

       SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);
       SysTick->LOAD |= SysTick_LOAD_RELOAD_Msk; //SysTick_LOAD_RELOAD_Msk;

   NVIC_EnableIRQ(EUSCIA2_IRQn);
}




void reverse(char s[])
     {
         int i, j;
         char c;
         for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
             c = s[i];
             s[i] = s[j];
             s[j] = c;
         }
     }

void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void FloatReverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

// Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    FloatReverse(str, i);
    str[i] = '\0';
    return i;
}
// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}
