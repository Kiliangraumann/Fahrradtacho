/*
 * lcd.c
 *
 *  Created on: 16.01.2023
 *      Author: graumkli
 */
#include "lcd.h"
#include <msp430.h>
#include <stdint.h>


// Konstanten
const uint8_t LCD_X_SIZE = 102;         // Anzahl Pixel in X-Richtung
const uint8_t LCD_Y_SIZE = 64;          // Anzahl Pixel in Y-Richtung
const uint8_t LCD_Y_SIZE_PAGES = 64 / 8;// Anzahl der Pages (8 Y-Pixel pro Page)

// Prototypen
static void lcd_set_cd(uint8_t value);
static void lcd_reset_h();
static void lcd_reset_l();

/**
 * @brief Initialisierung des LCDs
 */
void lcd_init() {
    // Pins initialisieren
    P1DIR |= BIT0 + BIT1; // Reset + CD
    lcd_reset_l();

    // Konfiguriere Pins für UCB0
    P1SEL1 |= BIT6;
    P1SEL0 &= ~BIT6;

    P2SEL1 |= BIT2;
    P2SEL0 &= ~BIT2;

    // Initialisiere UCB0 als Master
    UCB0CTLW0 = 0xA981;
    // Starte SPI B0
    UCB0CTLW0 &= ~UCSWRST;

    // Reset Pin deaktivieren
    lcd_reset_h();

    //Initialize bottom view 3.3V (booster on) 8Bit SPI
    lcd_send(0x40, 0); //Display start line 0
    lcd_send(0xA1, 0); //ADC reverse
    lcd_send(0xC0, 0); //Normal COM0...COM63
    lcd_send(0xA7, 0); //Display normal A6 or inverse
    lcd_send(0xA2, 0); //Set Bias 1/9 (Duty 1/65)
    lcd_send(0x2F, 0); //Booster, Regulator and Follower On
    lcd_send(0x27, 0); //Contrast set
    lcd_send(0x81, 0);
    lcd_send(0x0F, 0);
    lcd_send(0xAF, 0); //Display on
    lcd_send(0xB0, 0); //Page 0 einstellen
    lcd_send(0x10, 0); //High-Nible der Spaltenadresse
    lcd_send(0x00, 0); //Low-Nible der Spaltenadresse

    lcd_clear_all();
}

/**
 * @brief Deaktivieren des LCD -> kein Stromverbrauch durch LCD
 */
void lcd_disable() {
    lcd_reset_l();
}

/**
 * @brief Senden eines Bytes ueber SPI
 * @param value Byte, welches uebermittelt werden soll
 */
void lcd_spi_send_byte(uint8_t value) {
    while (UCB0STATW & BUSY);
    UCB0TXBUF = value;
    while (UCB0STATW & BUSY);
}

/**
 * @brief Senden eines Bytes an LCD\n CD = 1 -> Command\n CD = 0 -> Data
 * @param data Byte, welches uebermittelt werden soll
 * @param cd Uebermittlung von Daten (0) oder Befehl (1)
 */
void lcd_send(uint8_t data, uint8_t cd) {
    lcd_set_cd(cd);         // CD-Pin Setzen
    lcd_spi_send_byte(data);    // Daten über SPI übertragen
}

/**
 * @brief Setzen einer Page des LCD
 * @param x Angabe der x-Position, an welcher die Page gesetzt werden soll
 * @param y_page Angabe der y-Page, an welcher die Page gesetzt werden soll
 * @param byte Byte, welches uebermittelt werden soll
 */
void lcd_set_pixels(uint8_t x, uint8_t y_page, uint8_t byte) {
    // Position setzen
    lcd_send((x & 0x0F), 0);        // Low Nibble der X-Position
    lcd_send(0x10 + (x >> 4), 0);   // High Nibble
    lcd_send(0xB0 + y_page, 0);     // Page

    lcd_send(byte, 1);              // Pixelwerte senden
}

/**
 * @brief Löschen aller Pixel des Displays
 */
void lcd_clear_all() {

    for (uint8_t x = 0; x < LCD_X_SIZE; x++) {
        for (uint8_t y = 0; y < LCD_Y_SIZE_PAGES; y++) {
            lcd_set_pixels(x, y, 0xFF);
        }
    }
}

/**
 * @brief Reset-Pin wird auf H-Pegel gesetzt -> LCD einschalten
 */
static void lcd_reset_h() {
    P1OUT |= BIT0;
}

/**
 * @brief Reset-Pin wird auf L-Pegel gesetzt -> LCD anschalten
 */
static void lcd_reset_l() {
    P1OUT &= ~ BIT0;
}

/**
 * @brief Setze CD-Pin auf den angegebenen Pegel
 * @param value Wert, auf welchen der Ausgang gesetzt werden soll (0 oder 1)
 */
static void lcd_set_cd(uint8_t value) {
    if (value) {
        P1OUT |= BIT1;
    } else {
        P1OUT &= ~BIT1;
    }
}

