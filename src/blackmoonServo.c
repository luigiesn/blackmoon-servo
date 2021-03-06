/*
 * Main Blackmoon-servo application - part of Blackmoon servo controller
 * Copyright (C) 2015 - Luigi E. Sica Nery
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../include/blackmoonServo.h"
#include "../include/defs.h"

#include "../include/driver/led.h"
#include "../include/driver/timer.h"
#include "../include/driver/serial.h"
#include "../include/driver/adc.h"
#include "../include/driver/bridge.h"
#include "../include/driver/eeprom.h"
#include "../include/app.h"

void SystemInit(void);
void InterruptsDisable(void);
void InterruptsEnable(void);

void BlackmoonServo(void) {

    // Initial setup
    SystemInit();

    InterruptsDisable();

    // bootstrap all drivers
    ADC_Bootstrap();
    TIMER_Bootstrap();
    LED_Bootstrap();
    Bridge_Bootstrap();
    Serial_Boostrap();
    EEPROM_Boostrap();
    App_Boostrap();

    InterruptsEnable();

    // initialize all drivers
    LED_Init();
    EEPROM_Init();
    App_Init();

    // run all processes in loop
    for (;;) {
        Serial_TxProcess();
        Serial_RxProcess();
        EEPROM_Process();
        TIMER_Process();

        App_Process();
    }
}

void interrupt high_priority HighPriorISR(void) {

    if (PIE1bits.RCIE && PIR1bits.RCIF) { // UART RX
        Serial_ReceiveEventHandle();
    }
}

void interrupt low_priority LowPriorISR(void) {

    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) { // TIMER0
        INTCONbits.TMR0IF = 0; // clean flag
        TIMER_HwEventHandle();
    }

    if (PIE1bits.ADIE && PIR1bits.ADIF) { // ADC
        PIR1bits.ADIF = 0; // clean flag
        ADC_ConversionDoneEventHandle();
    }

    if (PIE2bits.EEIE && PIR2bits.EEIF) { // EEPROM
        PIR2bits.EEIF = 0; // clean flag
        // here: eeprom write event hadle
    }
}

void SystemInit() {
    // Oscillator Configuration
    OSCCONbits.IRCF = 0x7;
    OSCCONbits.SCS = 0x0;
    OSCTUNEbits.PLLEN = 0x1;
}

void InterruptsDisable(void) {
    RCONbits.IPEN = 0; // enables interrupt
    INTCONbits.GIEH = 0; // enables high-priority interrupts
    INTCONbits.GIEL = 0; // enables low-priority interrupts
}

void InterruptsEnable(void) {
    RCONbits.IPEN = 1; // enables interrupt
    INTCONbits.GIEH = 1; // enables high-priority interrupts
    INTCONbits.GIEL = 1; // enables low-priority interrupts
}


