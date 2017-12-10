/*
 * RTC.c
 *
 *  Created on: Nov 28, 2017
 *      Author: admin
 */

#include RTC.h

void config_RTC() {

	RTC_C->CTL0 = RTC_C_KEY | RTC_C_CTL0_RDYIE; // unlock RTC
	RTC_C->CTL13 |= (RTC_C_CTL13_HOLD | RTCBCD | RTC_C_CTL13_MODE);

	RTC_C->YEAR = YEAR_INIT;                   // Year = 0x2017
	RTC_C->DATE = (MONTH_INIT << RTC_C_DATE_MON_OFS) | // Month = 0x12 = Dec
			(DOM_INIT | RTC_C_DATE_DAY_OFS);    // Day = 0x05 = 5th
	RTC_C->TIM1 = (DOW_INIT << RTC_C_TIM1_DOW_OFS) | // Day of week = 0x06 = Sat
			(HR_INIT << RTC_C_TIM1_HOUR_OFS);  // Hour = 0x10
	RTC_C->TIM0 = (MIN_INIT << RTC_C_TIM0_MIN_OFS) | // Minute = 0x32
			(SEC_INIT << RTC_C_TIM0_SEC_OFS);   // Seconds = 0x45

	// Start RTC calendar mode
	RTC_C->CTL13 &= ~(RTC_C_CTL13_HOLD);

	// Lock the RTC registers
	RTC_C->CTL0 &= ~(RTC_C_CTL0_KEY_MASK);

	NVIC_EnableIRQ(RTC_C_IRQn);
}

void RTC_C_IRQHandler() {
	if(RTC_C->CTL0 & RTCRDYIFG) {
		RTC_C->CTL0 = RTC_C_KEY; //clear flag
		RTC_C->CTL0 = (RTC_C_KEY | RTCRDYIE); //re-enable interrupt
		min_sec = RTC_C->TIM0;
		hr_dow = RTC_C->TIM1;

		read = 1;
	}
}

void manip_register_data() {
	sec_hex = min_sec % (1 << RTC_C_TIM0_MIN_OFS);
	min_hex = min_sec >> RTC_C_TIM0_MIN_OFS;
	sec = (sec_hex>>4)*10 + (sec_hex % 16);
	min = (min_hex >>4)*10 + (min_hex %16);
	//if (min == 0) {
		hr_hex = (hr_dow % 256);
		hr = (hr_hex>>4)*10 + (hr_hex % 16);
	//}
	//if(hr == 0) {
		dow = hr_dow >> DAYOFWEEK_OFS;
	//}
}
