/*
 * power.h
 *
 *  Created on: 01.02.2023
 *      Author: graumkli
 */

#ifndef DISPLAYSTEUERUNG_POWER_H_
#define DISPLAYSTEUERUNG_POWER_H_
#include <stdint.h>

extern uint8_t powerstatus;

void power_fall_asleep();
void power_main_loop();

#endif /* DISPLAYSTEUERUNG_POWER_H_ */
