/*
 * port.h
 *
 *  Created on: Nov 28, 2017
 *      Author: admin
 */

#ifndef PORT_H_
#define PORT_H_

void config_finger();
void config_buttons();
void acccel_port_config();

void PORT2_IRQHandler(void);
void PORT4_IRQHandler(void);
void PORT5_IRQHandler(void);
void PORT6_IRQHandler(void);

//accel_pins_handlers();

//finger_prin_stuff??();


#endif /* PORT_H_ */
