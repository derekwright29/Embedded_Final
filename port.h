/*
 * port.h
 *
 *  Created on: Nov 28, 2017
 *      Author: admin
 */

#ifndef PORT_H_
#define PORT_H_
#include <stdint.h>

typedef enum {
	IDLE,
	ACTIVE,
	TASK_ACTIVE,
	SOS
} state_t;

void update_state_t(void);

void UART_send_byteA2(uint8_t data);
void UART_send_byteA0(uint8_t data);
void UART_send_A2(uint8_t * data, uint32_t length);
void UART_send_A0(uint8_t * data, uint32_t length);

void config_finger();
void config_buttons();
void config_buzzer();
void acccel_port_config();

#define G_len (11)
#define B_len (12)
#define W_len (16)


typedef enum REMINDER_STATUS {
    // Circular Buffer error (general)
    G = 0,
    B = 1,
    W = 2,
    GB = 3,
    GW = 4,
    BW = 5,
    GWB = 6,
    NONE = 7,
} REMINDER_STATUS;

void PrintReminders(REMINDER_STATUS status);
REMINDER_STATUS GetButtonState(uint8_t G_ID, uint8_t B_ID, uint8_t W_ID);

void PORT2_IRQHandler(void);
void PORT4_IRQHandler(void);
void PORT5_IRQHandler(void);
void PORT6_IRQHandler(void);

//accel_pins_handlers();

//finger_prin_stuff??();


#endif /* PORT_H_ */
