#include <msp430.h>
#include <stdint.h>

#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\controlfunctions.h"
#include "C:\Users\GRAUMKLI\Desktop\Studienarbeit 2\CSS Projekt\Displaysteuerung\power.h"

/**
 * @brief Hauptfunktion des Programmes
 */
void main(void){
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	// Configure Settings
    init();

    __enable_interrupt();      // Enable Interrupt

    while(1){
        power_main_loop();
    }
}
