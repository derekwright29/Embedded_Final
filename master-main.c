#include "msp.h"
#include "state.h"
#include <stdint.h>
#include "UART.h"
#include "port.h"
#include "timers.h"
#include "RTC.h"
#include "ADC.h"

/**
 * main.c
 */

//system state
volatile state_t state = IDLE;

//FPS state
volatile FP_cmd_packet cp;
volatile uint8_t FP_state;
volatile  uint8_t data_databuf[30];
volatile  uint8_t rsp_databuf[12];
volatile  FP_resp rp;
volatile uint8_t state3 = FP_DONT_CARE;
volatile uint8_t freqDiv = 0;
volatile uint8_t countTime = 0;
volatile uint8_t count_time_fall = 0;
volatile uint8_t timer_exit = 0;

//accel globals
volatile uint16_t ACCELX=0;
volatile uint16_t ACCELY=0;
volatile uint16_t ACCELZ=0;

volatile uint16_t CALX=0;
volatile uint16_t CALY=0;
volatile uint16_t CALZ=0;

//button globals
volatile uint8_t pet = 0;
volatile uint8_t apps = 0;
volatile uint8_t lock = 0;
volatile uint8_t emergency = 0;

//flow globals
volatile uint8_t finger = 0;
volatile uint8_t print = 0;
volatile uint8_t fall = 0;

//timer globals
volatile uint32_t timer0 = 0;
volatile uint32_t timer1 = 0;

//RTC globals
volatile RealTime_t currentTime;
volatile uint8_t read = 0;
volatile uint8_t temp_sec = 61; //init out of range. This var is for debouncing.

volatile uint8_t RTC_str[4];

void init_all() {
	config_buttons();
	config_buzzer();
	config_TA0();
	config_TA1();
	config_TA2();
	config_TA3();
	UART_ConfigureA2();
	UART_ConfigureA3();
	GPIO_FPS_config();
	configure_ADC();
	Open();
	SetLED(1);
}



void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
    int id = 0;
    int begin = 0;
    int stay_FP = 1;
    int is_freefall = 0;
	config_buttons();
	config_buzzer();
	//init_all(); //inits all ports and timers and only enables fingerprint interrupts. i.e. only fingerprint stuff is running.

	while(state == IDLE){
		//FPS enroll code
		//FPS check finger code
//		if(fingerisMAtched) {
//			state = ACTIVE
//			P4->IE |= (BIT0); //activate task buttons
//			P5->IE |= (BIT6);
//			P6->IE |= (BIT6);
//		}
	}
	handle_state();
		//accel code


		if(print) { //means timer triggered
			print = 0;
			sendCurrentTime();
			PrintReminders(GetButtonState(pet,apps,lock));
			UART_send_byteA0('\n');
		}
		if (fall) {
			P2->IE |= (BIT7); //turn on SOS button interrupt

		}
	}
	state = IDLE;
	while(1);


}
