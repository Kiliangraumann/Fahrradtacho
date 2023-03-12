/*
 * controlfunctions.h
 *
 *  Created on: 21.01.2023
 *      Author: graumkli
 */

#ifndef DISPLAYSTEUERUNG_CONTROLFUNCTIONS_H_
#define DISPLAYSTEUERUNG_CONTROLFUNCTIONS_H_

#include <stdint.h>

extern volatile uint8_t Screen;
extern volatile uint8_t Click1;
extern volatile uint8_t Click2;
extern volatile uint8_t x_value;
extern volatile uint8_t y_value;

void init();
void init_display();
void draw_display();
void port_init();
void clock_init();
void timer_init();
void timer_disable();
void timer_enable();
uint8_t getDecInNumber(uint32_t *num, uint8_t pos);
void changeInteger(uint8_t *Integer, uint8_t Anzahl);
void changeDecInNumber(uint32_t *num, uint8_t pos, uint8_t new_val);
void changeIntegerInSettings(uint32_t *num, uint8_t pos);
void button1(uint8_t zustand);
void button2(uint8_t zustand);
__interrupt void port3_ISR(void);
__interrupt void TIMER0_A0(void);

#endif /* DISPLAYSTEUERUNG_CONTROLFUNCTIONS_H_ */
