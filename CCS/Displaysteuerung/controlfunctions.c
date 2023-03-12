/*
 * controlfunctions.c
 *
 *  Created on: 21.01.2023
 *      Author: graumkli
 */
#include <msp430.h>
#include <math.h>

#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\power.h"
#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\LCD\lcd.h"
#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\LCD\digit.h"
#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\Displayanzeige\settings.h"
#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\Displayanzeige\start.h"

#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Signalauswertung\fram.h"
#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Signalauswertung\dynamoauswertung.h"

#include "controlfunctions.h"

volatile uint8_t Click1 = 0;
volatile uint8_t Click2 = 0;
volatile uint8_t Screen = 0;
volatile uint8_t x_value = 0;
volatile uint8_t y_value = 0;

/**
 * @brief Initialisierung aller Bestandteile
 */
void init(){
    settings_init();
    clock_init();
    timer_init();
    lcd_init();
    init_display();
    port_init();
    auswertung_init();
}

/**
 * @brief Beschreiben des Displays mit dem aktuellen Inhalt
 */
void init_display(){
    switch (Screen) {
    case 0:
        draw_start_display();
        break;
    case 1:
        draw_settings_display();
        if(y_value!=0){
            if(y_value == 1){
                if(x_value==1 || x_value==2 || x_value==3 || x_value==4 || x_value==5){
                    umfang_draw_settings(x_value);
                }
            }
            else if(y_value == 2){
                if(x_value==1 || x_value==2 || x_value==3 || x_value==4){
                    time_draw_settings(x_value);
                }
            }
            else if(y_value == 3){
                if(x_value==1 || x_value==2 || x_value==3 || x_value==4 || x_value==5){
                    dist_draw_settings(1, x_value);
                }
            }
            else if(y_value == 4){
                if(x_value==1 || x_value==2 || x_value==3 || x_value==4 || x_value==5){
                    dist_draw_settings(2, x_value);
                }
            }
            else if(y_value == 5){
                if(x_value==1 || x_value==2 || x_value==3 || x_value==4 || x_value==5){
                    dist_draw_settings(3, x_value);
                }
            }
        }
        break;
    default:
        break;
    }
}

/**
 * @brief Aktualisieren der Inhalte auf den Menueseiten
 */
void draw_display() {
    switch (Screen) {
    case 0:
        draw_start();
        break;
//    case 1:
//        draw_settings();
//        break;
    default:
        break;
    }
}

/**
 * @brief Initialisierung der benoetigten Pins
 */
void port_init(){
    P3DIR &= ~(BIT6 + BIT7);
    P3REN |= BIT6 + BIT7;
    P3OUT |= BIT6 + BIT7;
    P3IE |= BIT6 + BIT7;
    P3IES |= BIT6 + BIT7;
    P3IFG &= ~(BIT6 + BIT7);
}

/**
 * @brief Initialisierung der Clocks
 */
void clock_init(){
    CSCTL0_H = 0xA5;
    CSCTL1 |= DCOFSEL0 + DCOFSEL1;
    CSCTL2 = SELA_0 + SELS_3 + SELM_3;
    CSCTL3 = DIVA_0 + DIVS_3 + DIVM_3;
    CSCTL4 |= XT1DRIVE_0;
    CSCTL4 &= ~XT1OFF;
}

/**
 * @brief Initialisierung von Timer A0
 */
void timer_init(){
    TA0CCTL0 = CCIE;
    TA0CTL = TASSEL_2 + TACLR + ID_3;
    TA0CCR0 = 0x61A8; //200ms Dauer des IE ausschaltens
}

/**
 * @brief Abschalten von Timer A0
 */
void timer_disable(){
    TA0CTL &= ~ MC_1;
    TA0CTL |= TACLR;
}

/**
 * @brief Starten von Timer A0
 */
void timer_enable(){
    TA0CTL |= MC_1;
    TA0CTL |= TACLR;
}

/**
 * @brief Bestimmung der aktuellen Ziffer inerhalb einer Zahl
 * @param *num Speicherort der Zahl
 * @param pos Position innerhalb der Zahl
 * @return Ziffer an gewuenschter Stelle
 */
uint8_t getDecInNumber(uint32_t *num, uint8_t pos){
    uint8_t Array[5];
    uint32_t zahl = *num;
    for(uint8_t digit = 0; digit < 5; digit++) {
        uint8_t c = zahl % 10;
        Array[4 - digit] = c;
        zahl /= 10;
    }
    return Array[pos];
}

/**
 * @brief Erhoehung einer Ziffer von 0 bis 9
 * @param *Integer Speicherort der zu aendernden Ziffer
 * @param Anzahl Anzahl an Erhoehungen der Ziffer
 */
void changeInteger(uint8_t *Integer, uint8_t Anzahl){
    for(uint8_t i = 0; i < Anzahl; i++){
        if (*Integer<9){
            *Integer += 1;
        }
        else if(*Integer == 9){
            *Integer = 0;
        }
    }
}

/**
 * @brief Aenderung einer Ziffer inerhalb einer Zahl
 * @param *num Speicherort der Zahl
 * @param pos Position innerhalb der Zahl
 * @param new_val Neue Ziffer, welche an der Stelle eingesetzt werden soll
 */
void changeDecInNumber(uint32_t *num, uint8_t pos, uint8_t new_val){
    // Gib eine maximal 5 stellige Zahl an in welcher an einer Gegebenen Position ein neuer Integer gesetzt
    // werden soll
    // Eingabe der pos von 0-4
    uint8_t Array[5];
    uint32_t zahl = *num;
        for(uint8_t digit = 0; digit < 5; digit++) {
            uint8_t c = zahl % 10;
            Array[4 - digit] = c;
            zahl /= 10;
        }
    Array[pos] = new_val;
    uint32_t result = 0;
    for(uint8_t temp=0; temp < 5; temp++){
        result*=10;
        result+=Array[temp];
    }
    *num = result;
}

/**
 * @brief Zusammenfassende Funktion um eine ausgewaehlte Ziffer innerhalb einer Zahl zu erhoehen
 * @param *num Speicherort der Zahl
 * @param pos Position innerhalb der Zahl
 */
void changeIntegerInSettings(uint32_t *num, uint8_t pos){
    // Nutzt getDecInNumber, changeDecInNumber und changeInteger um eine Stelle in einem Integer
    // zu tauschen.
    // Die neue Zahl hängt dabei von der vorherigen ab und der Anzahl an Taster Betätigunge

    uint8_t Integer = getDecInNumber(num, pos);

    changeInteger(&Integer, 1);

    changeDecInNumber(num, pos, Integer);
}

/**
 * @brief Verwaltung aller noetigen Ereignisse, welche durch das Betaetigen des ersten Tasters ausgeloest werden sollen
 * @param zustand Ausfuehrung der Funktion sobald dieser Zustand aktiv ist
 */
void button1(uint8_t zustand){
    if(zustand==1){
        if(y_value == 0 && x_value == 0){
            switch(Screen){
                case 0:
                    draw_settings_display();
                    Screen = 1;
                    break;
                case 1:
                    draw_start_display();
                    Screen = 0;
                    break;
                default:
                    break;
            }
        }
        else if(y_value == 1){
            if(x_value==1 || x_value==2 || x_value==3 || x_value==4 || x_value==5){
                changeIntegerInSettings(&Settings.Radumfang, x_value - 1);
                umfang_draw_settings(x_value);
            }
        }
        else if(y_value == 2){
            if(x_value==1 ||  x_value==2){
                changeIntegerInSettings(&Settings.Uhrzeit.Stunde, x_value + 2);
                time_draw_settings(x_value);
            }
            else if(x_value==3 ||  x_value==4){
                changeIntegerInSettings(&Settings.Uhrzeit.Minute, x_value);
                time_draw_settings(x_value);
            }
        }
        else if(y_value == 3){
            if(x_value==1 || x_value==2 || x_value==3 || x_value==4 || x_value==5){
                changeIntegerInSettings(&Settings.Distanz.Gesamt, x_value - 1);
                dist_draw_settings(1, x_value);
            }
        }
        else if(y_value == 4){
            if(x_value==1 || x_value==2 || x_value==3 || x_value==4 || x_value==5){
                changeIntegerInSettings(&Settings.Distanz.Tour, x_value - 1);
                dist_draw_settings(2, x_value);
            }
        }
        else if(y_value == 5){
            if(x_value==1 || x_value==2 || x_value==3 || x_value==4 || x_value==5){
                changeIntegerInSettings(&Settings.Distanz.Tag, x_value - 1);
                dist_draw_settings(3, x_value);
            }
        }
        Click1 = 0;
        timer_enable();
    }
}

/**
 * @brief Verwaltung aller noetigen Ereignisse, welche durch das Betaetigen des zweiten Tasters ausgeloest werden sollen
 * @param zustand Ausfuehrung der Funktion sobald dieser Zustand aktiv ist
 */
void button2(uint8_t zustand){
    if(zustand==1){
        if(Screen == 1){
            if(y_value == 0){
                y_value = 1;
                x_value = 1;
                umfang_draw_settings(1);
            }
            else if(y_value == 1){
                if(x_value==1 || x_value==2 || x_value==3 || x_value==4){
                    umfang_draw_settings(x_value + 1);
                    x_value++;
                }
                else if(x_value==5){
                    umfang_draw_settings(0);
                    time_draw_settings(1);
                    y_value = 2;
                    x_value = 1;
                }
            }
            else if(y_value == 2){
                if(x_value==1 || x_value==2 || x_value==3){
                    time_draw_settings(x_value + 1);
                    x_value++;
                }
                else if(x_value==4){
                    time_draw_settings(0);
                    dist_draw_settings(1, 1);
                    y_value = 3;
                    x_value = 1;
                }
            }
            else if(y_value == 3){
                if(x_value==1 || x_value==2 || x_value==3 || x_value==4){
                    dist_draw_settings(1, x_value + 1);
                    x_value++;
                }
                else if(x_value==5){
                    dist_draw_settings(1, 0);
                    dist_draw_settings(2, 1);
                    y_value = 4;
                    x_value = 1;
                }
            }
            else if(y_value == 4){
                if(x_value==1 || x_value==2 || x_value==3 || x_value==4){
                    dist_draw_settings(2, x_value + 1);
                    x_value++;
                }
                else if(x_value==5){
                    dist_draw_settings(2, 0);
                    dist_draw_settings(3, 1);
                    y_value = 5;
                    x_value = 1;
                }
            }
            else if(y_value == 5){
                if(x_value==1 || x_value==2 || x_value==3 || x_value==4){
                    dist_draw_settings(3, x_value + 1);
                    x_value++;
                }
                else if(x_value==5){
                    dist_draw_settings(3, 0);
                    y_value = 0;
                    x_value = 0;
                }
            }
        }
    Click2 = 0;
    timer_enable();
    }
}

/**
 * @brief Verwaltung der Port-Interrupts
 */
#pragma vector=PORT3_VECTOR
__interrupt void port3_ISR(void) {
    // Erster Taster zum Navigieren und Einstellen
    if(P3IFG&BIT7){
        P3IFG &= ~BIT7;
        P3IE &= ~BIT6;
        P3IE &= ~BIT7;
        Click1 = 1;
        if(powerstatus==0){
            Click1 = 0;
            __low_power_mode_off_on_exit();
            timer_enable();
        }
    }
    // Zweiter Taster um durch die Einstellungen zu navigieren
    if(P3IFG&BIT6){
        P3IFG &= ~BIT6;
        P3IE &= ~BIT6;
        P3IE &= ~BIT7;
        Click2 = 1;
        if(powerstatus==0){
            Click2 = 0;
            __low_power_mode_off_on_exit();
            timer_enable();
        }
    }
}

/**
 * @brief Timer A0 Interrupt zum Entprellen der Taster
 */
#pragma vector=TIMER0_A0_VECTOR
interrupt void TIMER0_A0_ISR() {
    timer_disable();
    TA0CTL &= ~TAIFG;
    P3IFG &= ~BIT7;
    P3IE |= BIT7;
    P3IFG &= ~BIT6;
    P3IE |= BIT6;
}
