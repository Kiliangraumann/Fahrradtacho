/*
 * dynamoauswertung.h
 *
 *  Created on: 04.02.2023
 *      Author: graumkli
 */

#ifndef SIGNALAUSWERTUNG_DYNAMOAUSWERTUNG_H_
#define SIGNALAUSWERTUNG_DYNAMOAUSWERTUNG_H_

#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\Displayanzeige\settings.h"

extern uint8_t Shutdown;
extern uint32_t Dist_Dezimeter;

void auswertung_init();
void calc_speed();
void calc_dist();
void reset_dynamo_timer();

#endif /* SIGNALAUSWERTUNG_DYNAMOAUSWERTUNG_H_ */
