#include <msp430.h>
#include <stdint.h>
#include <stdlib.h>

#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\power.h"
#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\controlfunctions.h"
#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\Displayanzeige\start.h"


#include "dynamoauswertung.h"

#define FREQUENZ 8096
#define NULLDURCHGÄNGE_PRO_UMDREHUNG 28

uint8_t Shutdown;
uint8_t Rechnen;
uint32_t Anzahl_Nulldurchgaenge;
uint32_t Timer_ticks;
uint32_t Timer_ticks_alt;
uint32_t Timer_ticks_alt2;
uint32_t Speed;
uint32_t temp_Anzahl_Nulldurchgaenge;
uint32_t temp_Timer_ticks;
uint32_t Dist_Dezimeter;

uint16_t last_trigger_time;
int32_t time_since_last_trigger;
uint32_t current_time;

/**
 * @brief Initialisierung der Dynamoauswertung
 */
void auswertung_init(){
    P1DIR &= ~BIT7;
    P1SEL0 |= BIT7;
    P1SEL1 |= BIT7;
    TA1CCTL0 = CAP+CM_1+CCIE+CCIS_0;
    TA1CTL = TASSEL_1 + MC_2 + ID_0 + TAIE + TACLR;
    TB0CTL = TASSEL_1 + MC_2 + TBCLR + ID_3;
}

/**
 * @brief Berechnung der Geschwindigkeit
 */
void calc_speed(){
    if(temp_Timer_ticks != 0){
    Speed = ((((uint32_t)8770*(uint32_t)100)/(uint32_t)temp_Timer_ticks * ((uint32_t)temp_Anzahl_Nulldurchgaenge*100)/(uint32_t)28 * (uint32_t)Settings.Radumfang * (uint32_t)36) / (uint32_t)1000000) * (uint32_t)2;
    uint8_t Runden = (uint32_t) (Speed  % 10);
    uint8_t Runden_2 = (uint32_t) ((Speed/10)  % 10);
        if(Runden >= 5){
            if(Runden_2 == 9){
                Settings.Speed.Vorkomma = (uint32_t) (Speed/100 + 1);
                Settings.Speed.Nachkomma = (uint32_t) 0;
            }
            else{
                Settings.Speed.Vorkomma = (uint32_t) Speed/100;
                Settings.Speed.Nachkomma = (uint32_t) (((Speed/10)  % 10) + 1);
            }
        }
        else{
            Settings.Speed.Vorkomma = (uint32_t) Speed/100;
            Settings.Speed.Nachkomma = (uint32_t) ((Speed/10)  % 10);
        }
    }
    else{
        Settings.Speed.Vorkomma = 0;
        Settings.Speed.Nachkomma = 0;
    }
}

/**
 * @brief Berechnung der Distanz
 */
void calc_dist(){
    Dist_Dezimeter += (uint32_t)((((uint32_t)Speed*(uint32_t)100)/(uint32_t)36) / (((uint32_t)8770*(uint32_t)100)/(uint32_t)temp_Timer_ticks));

    if(Dist_Dezimeter > 10000){
        Dist_Dezimeter -= 10000;
        Settings.Distanz.Gesamt = Settings.Distanz.Gesamt + 1;
        Settings.Distanz.Tour = Settings.Distanz.Tour + 1;
        Settings.Distanz.Tag = Settings.Distanz.Tag + 1;
    }
}

/**
 * @brief Zuruecksetzen der Dynamo Timer
 */
void reset_dynamo_timer(){
    TA1CTL |= MC_2 + TACLR;
    TB0CTL |=  MC_2 + TBCLR;
}

/**
 * @brief Timer A0 Interrupt zum Berechnen der Werte
 */
#pragma vector=TIMER1_A0_VECTOR
//__interrupt void TIMER_A0(void){
//    current_time = TB0R;
//    time_since_last_trigger = current_time - last_trigger_time;
//    if (time_since_last_trigger < 30) {
//        if (time_since_last_trigger < 0){
//            time_since_last_trigger = current_time + (0xFFFF - last_trigger_time);
//            last_trigger_time = current_time;
//        }
//        else if (time_since_last_trigger >= 0){
//            return;
//        }
//    }
//    if (time_since_last_trigger >= 30) {
//        Timer_ticks+=TA1CCR0;
//        Anzahl_Nulldurchgaenge++;
//        TA1CTL |= TACLR;
//        if(Timer_ticks >= 8770 && Rechnen == 0 && Screen == 0 && Click1 == 0){
//            Rechnen = 1;
//            temp_Anzahl_Nulldurchgaenge = Anzahl_Nulldurchgaenge;
//            temp_Timer_ticks = Timer_ticks;
//            Anzahl_Nulldurchgaenge = 0;
//            Timer_ticks = 0;
//            calc_speed();
//            calc_dist();
//            //temp_Anzahl_Nulldurchgaenge = 0;
//            //temp_Timer_ticks = 0;
//            speed_draw();
//            dist_draw();
//            Rechnen = 0;
//        }
//        last_trigger_time = current_time;
//    }
//    if(powerstatus==0) __low_power_mode_off_on_exit();
//
//}

__interrupt void TIMER_A0(void){
    if((8770/TA1CCR0)<=70){
        Timer_ticks+=TA1CCR0;
        ++Anzahl_Nulldurchgaenge;
        TA1CTL |= TACLR;
        if(Timer_ticks >= 8770 && Rechnen == 0 && Screen == 0 && Click1 == 0){
            Rechnen = 1;
            temp_Anzahl_Nulldurchgaenge = Anzahl_Nulldurchgaenge;
            temp_Timer_ticks = Timer_ticks;
            Anzahl_Nulldurchgaenge = 0;
            Timer_ticks = 0;
            calc_speed();
            calc_dist();
            //temp_Anzahl_Nulldurchgaenge = 0;
            //temp_Timer_ticks = 0;
            speed_draw();
            dist_draw();
            Rechnen = 0;
        }
    }
    if(powerstatus==0) __low_power_mode_off_on_exit();
}

//__interrupt void TIMER_A0(void){
//    if((abs(Timer_ticks_alt-TA1CCR0))<100){
//        Timer_ticks_alt = TA1CCR0;
//        Timer_ticks+=TA1CCR0;
//        Anzahl_Nulldurchgaenge++;
//        TA1CTL |= TACLR;
//        if(Timer_ticks >= 8770 && Rechnen == 0 && Screen == 0 && Click1 == 0){
//            Rechnen = 1;
//            temp_Anzahl_Nulldurchgaenge = Anzahl_Nulldurchgaenge;
//            temp_Timer_ticks = Timer_ticks;
//            Anzahl_Nulldurchgaenge = 0;
//            Timer_ticks = 0;
//            calc_speed();
//            calc_dist();
//            //temp_Anzahl_Nulldurchgaenge = 0;
//            //temp_Timer_ticks = 0;
//            speed_draw();
//            dist_draw();
//            Rechnen = 0;
//        }
//    }
//    else if(Timer_ticks_alt==0){
//        Timer_ticks_alt = TA1CCR0;
//        TA1CTL |= TACLR;
//    }
//    else if(TA1CCR0>=Timer_ticks_alt){
//        Timer_ticks_alt = TA1CCR0;
//        TA1CTL |= TACLR;
//    }
//    if(powerstatus==0) __low_power_mode_off_on_exit();
//}

/**
 * @brief Timer A1 Interrupt für Ruhemodus
 */
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER_A1(void){
    switch (TA1IV){
        case 14:
            TA1CTL &= ~MC_2;
            Shutdown = 1;
            break;
    }
}
