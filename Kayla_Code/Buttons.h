/*
 * Buttons.h
 *
 *  Created on: Dec 6, 2017
 *      Author: Kayla
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "msp.h"

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
void GPIO_config();

extern volatile uint8_t G_button;
extern volatile uint8_t B_button;
extern volatile uint8_t W_button;


#endif /* BUTTONS_H_ */
