/*
 * fram.c
 *
 *  Created on: 02.02.2023
 *      Author: graumkli
 */

#include <msp430.h>
#include <stdint.h>

#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Signalauswertung\dynamoauswertung.h"


#include "fram.h"

__attribute__ ((noinit)) uint32_t radumfang_fram;

__attribute__ ((noinit)) uint32_t dist1_fram;

__attribute__ ((noinit)) uint32_t dist2_fram;

__attribute__ ((noinit)) uint32_t dist3_fram;

__attribute__ ((noinit)) uint8_t first_init_fram;

__attribute__ ((noinit)) uint32_t Dist_Dezimeter_fram;

/**
 * @brief Speicherung der Parameter im FRAM
 */
void set_fram(){
    Dist_Dezimeter_fram = Dist_Dezimeter;
    dist1_fram = Settings.Distanz.Gesamt;
    dist2_fram = Settings.Distanz.Tour;
    dist3_fram = Settings.Distanz.Tag;
    radumfang_fram = Settings.Radumfang;
}

/**
 * @brief Einlesen der Werte aus dem FRAM
 * @return Einstellungen aus dem FRAM
 */
settings_t get_fram(){
    settings_t Fram;
    if(first_init_fram != 0x10){
        Fram.Distanz.Gesamt = 0;
        Fram.Distanz.Tour = 0;
        Fram.Distanz.Tag = 0;
        Fram.Radumfang = 2220;
        Dist_Dezimeter = 0;

        Dist_Dezimeter_fram = Dist_Dezimeter;
        dist1_fram = Fram.Distanz.Gesamt;
        dist2_fram = Fram.Distanz.Tour;
        dist3_fram = Fram.Distanz.Tag;
        radumfang_fram = Fram.Radumfang;
        first_init_fram = 0x10;
    }
    else{
        Dist_Dezimeter = Dist_Dezimeter_fram;
        Fram.Distanz.Gesamt = dist1_fram;
        Fram.Distanz.Tour = dist2_fram;
        Fram.Distanz.Tag = dist3_fram;
        Fram.Radumfang = radumfang_fram;
    }
    return Fram;
}
