/*
 * digit.h
 *
 *  Created on: 17.01.2023
 *      Author: graumkli
 */
#ifndef DIGIT_H_
#define DIGIT_H_

void digit_draw_20x32(uint8_t x, uint8_t y_page, uint8_t digit);
void digit_draw_12x16(uint8_t x, uint8_t y_page, uint8_t digit);
void digit_draw_6x8(uint8_t x, uint8_t y_page, uint8_t digit);
void digit_draw_6x8_invert(uint8_t x, uint8_t y_page, uint8_t digit);
void digit_clear_20x32(uint8_t x, uint8_t y_page);
void digit_clear_12x16(uint8_t x, uint8_t y_page);
void digit_clear_6x8(uint8_t x, uint8_t y_page);
void draw_number_6x8(uint8_t x, uint8_t y_page, uint32_t number,
        uint8_t digit_count, uint8_t leading_zeros, uint8_t stelle_invert);

#endif /* DIGIT_H_ */
