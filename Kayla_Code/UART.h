/*
 * UART.h
 *
 *  Created on: Nov 21, 2017
 *      Author: Kayla
 */

#ifndef UART_H_
#define UART_H_

void UART_ConfigureA2();
void UART_ConfigureA0();

void UART_send_byteA2(uint8_t data);
void UART_send_byteA0(uint8_t data);
void UART_send_A2(uint8_t * data, uint32_t length);
void UART_send_A0(uint8_t * data, uint32_t length);

void UART_read_data(uint8_t * data, int length);
void UART_read_byte(uint8_t data);


#endif /* UART_H_ */
