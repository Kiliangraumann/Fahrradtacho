/*
 * power.c
 *
 *  Created on: 01.02.2023
 *      Author: graumkli
 */
#include <msp430.h>
#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\controlfunctions.h"
#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\LCD\lcd.h"
#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\LCD\digit.h"
#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\Displayanzeige\settings.h"
#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\Displayanzeige\start.h"

#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Signalauswertung\fram.h"
#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Signalauswertung\dynamoauswertung.h"

#include "power.h"

uint8_t powerstatus = 1;

/**
 * @brief Abschaltung unnoetiger Ports etc.
 */
void power_fall_asleep(){
    // Pins abschalten?

    // Deaktivieren der Module
    lcd_disable();
    //timer_disable();
}

/**
 * @brief Hauptschleife im aktive Zustand
 */
void power_main_loop(){
    if (Shutdown == 1) {
        // Standy aktivieren
        set_fram();
        power_fall_asleep();
        powerstatus = 0;
        __low_power_mode_4();   // Warten im LPM

        // Aufwachen
        init();
        reset_dynamo_timer();
        Shutdown = 0;
        powerstatus = 1;
    }
    else {
        button1(Click1);
        button2(Click2);
    }
}

