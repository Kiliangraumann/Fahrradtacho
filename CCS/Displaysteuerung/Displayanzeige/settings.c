/*
 * settings.c
 *
 *  Created on: 20.01.2023
 *      Author: graumkli
 */
#include <stdint.h>
#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\LCD\lcd.h"
#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\LCD\digit.h"
#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\Displayanzeige\start.h"

#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Signalauswertung\fram.h"

#include "settings.h"

static const uint8_t DIST_VALUE_Y1 = 5;
static const uint8_t DIST_VALUE_Y2 = 6;
static const uint8_t DIST_VALUE_Y3 = 7;
static const uint8_t DIST_VALUE_X_1 = 66;
static const uint8_t DIST_VALUE_X_2 = 66;
static const uint8_t DIST_VALUE_X_3 = 66;

static const uint8_t TIME_VALUE_Y1 = 4;
static const uint8_t TIME_VALUE_X_1 = 53;

static const uint8_t UMFANG_VALUE_Y1 = 2;
static const uint8_t UMFANG_VALUE_X_1 = 34;

settings_t Settings;

#if 1
// Pr�prozessor-Anweisung f�r Folding

static const uint8_t SETTINGS_DISPLAY_DATA[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0x80, 0xff, 0xff, 0xc0, 0x80, 0x80, 0x80,
                                                0xff, 0xee, 0xff, 0xff, 0xbf, 0xbe, 0xbe, 0xbe,
                                                0xff, 0xee, 0xff, 0xff, 0xbf, 0xbe, 0xbe, 0xbe,
                                                0xff, 0xce, 0xff, 0xff, 0xbf, 0xbe, 0xbe, 0xbe,
                                                0xff, 0xb1, 0xff, 0xff, 0xc0, 0xc1, 0xc1, 0xc1,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xdf, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff,
                                                0xff, 0xab, 0xff, 0xff, 0xfb, 0x82, 0x82, 0x82,
                                                0xff, 0xab, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff,
                                                0xff, 0xab, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff,
                                                0xff, 0x87, 0xff, 0xff, 0x87, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xb7, 0xb7, 0xb7,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xab, 0xab, 0xab,
                                                0xff, 0xc7, 0xff, 0xff, 0x83, 0xab, 0xab, 0xab,
                                                0xff, 0xbb, 0xff, 0xff, 0xef, 0xab, 0xab, 0xab,
                                                0xff, 0xbb, 0xff, 0xff, 0xf7, 0xdf, 0xdf, 0xdf,
                                                0xff, 0xbb, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff,
                                                0xff, 0x80, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xfb, 0xfb,
                                                0xd9, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xc1, 0xc1,
                                                0x90, 0xc3, 0xff, 0xff, 0xbb, 0xbb, 0xbb, 0xbb,
                                                0xb6, 0xbf, 0xff, 0xff, 0x9b, 0xbb, 0xbb, 0xbb,
                                                0xb6, 0xbf, 0xff, 0xff, 0xab, 0xff, 0xff, 0xff,
                                                0x84, 0xbf, 0xff, 0xff, 0xb3, 0xff, 0xff, 0xff,
                                                0xcd, 0xc3, 0xff, 0xff, 0xbb, 0xff, 0xbd, 0xdd,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x9e, 0xbe,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xae, 0xb6,
                                                0xc7, 0x83, 0xff, 0xff, 0xc7, 0x80, 0xb6, 0xb6,
                                                0x83, 0xfb, 0xff, 0xff, 0xab, 0xff, 0xb9, 0xc9,
                                                0xab, 0xfb, 0xff, 0xff, 0xab, 0xff, 0xff, 0xff,
                                                0xab, 0xe7, 0xff, 0xff, 0xab, 0xff, 0xff, 0xff,
                                                0xa3, 0xfb, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff,
                                                0xe7, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0x87, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xbe, 0xbe, 0xbe,
                                                0xfb, 0xff, 0xff, 0xff, 0x82, 0xbe, 0xbe, 0xbe,
                                                0xc1, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0x81, 0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xbb, 0xfa, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80,
                                                0xbb, 0xfa, 0xff, 0xff, 0xfb, 0xef, 0xef, 0xef,
                                                0xff, 0xff, 0xff, 0xff, 0xc1, 0xe7, 0xe7, 0xe7,
                                                0xff, 0xff, 0xff, 0xff, 0xbb, 0xdb, 0xdb, 0xdb,
                                                0xfb, 0xdf, 0xff, 0xff, 0xbb, 0xbf, 0xbf, 0xbf,
                                                0xc1, 0xab, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0x81, 0xab, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xbb, 0xab, 0xff, 0xff, 0xff, 0x83, 0x83, 0x83,
                                                0xbb, 0x87, 0xff, 0xff, 0xff, 0xfb, 0xfb, 0xfb,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xfb, 0xfb,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xe7, 0xe7,
                                                0xff, 0x83, 0xff, 0xff, 0xff, 0xfb, 0xfb, 0xfb,
                                                0x82, 0xfb, 0xff, 0xff, 0xff, 0xfb, 0xfb, 0xfb,
                                                0x82, 0xfb, 0xff, 0xff, 0xff, 0x87, 0x87, 0x87,
                                                0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xbe, 0xbe, 0xbe,
                                                0x83, 0xff, 0xff, 0xff, 0xff, 0xbe, 0xbe, 0xbe,
                                                0x83, 0xe7, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80,
                                                0xfb, 0x5b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xfb, 0x5b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0x83, 0x5b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0x87, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0x43, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0x5b, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0x5b, 0xbe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0x3, 0xbe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xb7, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xa3, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xab, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xab, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0x8b, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xdf, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xbe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xbe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

#endif

/**
 * @brief Ausgangsfunktion zum Anzeigen der Einstellungsseite
 */
void draw_settings_display() {
    const uint8_t *pt = &(SETTINGS_DISPLAY_DATA[0]);
        for (uint8_t x = 0; x < LCD_X_SIZE; x++) {
            for (uint8_t y = 0; y < LCD_Y_SIZE_PAGES; y++) {
                lcd_set_pixels(x, y, *pt);
                pt++;
            }
        }

        lcd_set_pixels(97, 1, 0x99);
        lcd_set_pixels(98, 1, 0x99);

        lcd_set_pixels(49, 4, 0x99);
        lcd_set_pixels(50, 4, 0x99);
        lcd_set_pixels(68, 4, 0x99);
        lcd_set_pixels(69, 4, 0x99);

        lcd_set_pixels(62, 5, 0x99);
        lcd_set_pixels(63, 5, 0x99);
        lcd_set_pixels(62, 6, 0x99);
        lcd_set_pixels(63, 6, 0x99);
        lcd_set_pixels(62, 7, 0x99);
        lcd_set_pixels(63, 7, 0x99);

        draw_settings();
}

/**
 * @brief Schreibt alle Werte auf die Einstellungsseite
 */
void draw_settings(){
    time_draw_settings(0);
    dist_draw_settings(0,0);
    umfang_draw_settings(0);
}

/**
 * @brief Schreibt die aktuelle Zeit auf die Einstellungsseite
 * @param position Die Position der vorzuhebenden Ziffer
 */
void time_draw_settings(uint8_t position) {
    // Anzeige der ersten Ziffer
    uint8_t first_digit = Settings.Uhrzeit.Stunde / 10;
    if(position!=1)
        digit_draw_6x8(TIME_VALUE_X_1, TIME_VALUE_Y1,first_digit);
    else if(position==1)
        digit_draw_6x8_invert(TIME_VALUE_X_1, TIME_VALUE_Y1,first_digit);

    // Zweite Ziffer
    if(position!=2)
        digit_draw_6x8(TIME_VALUE_X_1+7, TIME_VALUE_Y1, Settings.Uhrzeit.Stunde % 10);
    else if(position==2)
        digit_draw_6x8_invert(TIME_VALUE_X_1+7, TIME_VALUE_Y1, Settings.Uhrzeit.Stunde % 10);

    first_digit = Settings.Uhrzeit.Minute / 10;
    if(position!=3)
        digit_draw_6x8(TIME_VALUE_X_1+19, TIME_VALUE_Y1,first_digit);
    else if(position==3)
        digit_draw_6x8_invert(TIME_VALUE_X_1+19, TIME_VALUE_Y1,first_digit);

    // Zweite Ziffer
    if(position!=4)
        digit_draw_6x8(TIME_VALUE_X_1+26, TIME_VALUE_Y1, Settings.Uhrzeit.Minute % 10);
    else if(position==4)
        digit_draw_6x8_invert(TIME_VALUE_X_1+26, TIME_VALUE_Y1, Settings.Uhrzeit.Minute % 10);
}

/**
 * @brief Schreibt die aktuellen Distanzen auf die Einstellungsseite
 * @param line Die Spalte, welche geschrieben werden soll
 * @param position Die Position der vorzuhebenden Ziffer
 */
void dist_draw_settings(uint8_t line, uint8_t position){
    if(line==0){
        draw_number_6x8(DIST_VALUE_X_1, DIST_VALUE_Y1, Settings.Distanz.Gesamt, 5, 1, 0);
        draw_number_6x8(DIST_VALUE_X_2, DIST_VALUE_Y2, Settings.Distanz.Tour, 5, 1, 0);
        draw_number_6x8(DIST_VALUE_X_3, DIST_VALUE_Y3, Settings.Distanz.Tag, 5, 1, 0);
    }
    if(line==1){
        draw_number_6x8(DIST_VALUE_X_1, DIST_VALUE_Y1, Settings.Distanz.Gesamt, 5, 1, position);
    }
    if(line==2){
        draw_number_6x8(DIST_VALUE_X_2, DIST_VALUE_Y2, Settings.Distanz.Tour, 5, 1, position);
    }
    if(line==3){
        draw_number_6x8(DIST_VALUE_X_3, DIST_VALUE_Y3, Settings.Distanz.Tag, 5, 1, position);
    }
}

/**
 * @brief Schreibt den aktuellen Radumfang auf die Einstellungsseite
 * @param position Die Position der vorzuhebenden Ziffer
 */
void umfang_draw_settings(uint8_t position){
    draw_number_6x8(UMFANG_VALUE_X_1, UMFANG_VALUE_Y1, Settings.Radumfang, 5, 1, position);
}

/**
 * @brief Initialisiert die Einstellungen
 */
void settings_init(){
    // Lesen aus Flash
    Settings = get_fram();

    //Beispiel

    time_t Time;
    Time.Stunde = 14;
    Time.Minute = 03;
    Time.Sekunde = 45;

    Settings.Uhrzeit = Time;

    Settings.Speed.Vorkomma = 0;
    Settings.Speed.Nachkomma = 0;
}
