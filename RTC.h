/*
 * RTC.h
 *
 *  Created on: Nov 28, 2017
 *      Author: admin
 */
#ifndef RTC_H_
#define RTC_H_
#include <stdint.h>

#define YEAR_INIT 0x2017
#define MONTH_INIT 0x12
#define DOM_INIT 0x9
#define DOW_INIT 0x6
#define HR_INIT 0x16
#define MIN_INIT 0x19
#define SEC_INIT 0x00

void config_RTC();
void RTC_C_IRQHandler();
void manip_register_data();

#endif /* RTC_H_ */
