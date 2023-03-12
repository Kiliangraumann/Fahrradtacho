/*
 * settings.h
 *
 *  Created on: 20.01.2023
 *      Author: graumkli
 */

#ifndef DISPLAYSTEUERUNG_DISPLAYANZEIGE_SETTINGS_H_
#define DISPLAYSTEUERUNG_DISPLAYANZEIGE_SETTINGS_H_

typedef struct {
    uint32_t Vorkomma;
    uint32_t Nachkomma;
} speed_t;

typedef struct {
    uint32_t Gesamt;
    uint32_t Tour;
    uint32_t Tag;
} dist_t;

typedef struct {
    uint32_t Stunde;
    uint32_t Minute;
    uint32_t Sekunde;
} time_t;

typedef struct {
    time_t Uhrzeit;
    dist_t Distanz;
    uint32_t Radumfang;
    speed_t Speed;
} settings_t;

extern settings_t Settings;

void settings_init();

void draw_settings_display();
void draw_settings();
void time_draw_settings(uint8_t position);
void dist_draw_settings(uint8_t line, uint8_t position);
void umfang_draw_settings(uint8_t position);

#endif /* DISPLAYSTEUERUNG_DISPLAYANZEIGE_SETTINGS_H_ */
