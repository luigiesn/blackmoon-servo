/*
 * User led driver - part of Blackmoon servo controller
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

#ifndef _LED_H_
#define	_LED_H_

#include <xc.h>
#include "../defs.h"
#include "../driver/timer.h"

#define LED_MASK 0x10 // RA4
#define LED_PORT PORTA
#define LED_PORT_DIR TRISA


#define LED_CONST_OFF 0
#define LED_SLOW 500 // ms (ton and toff)
#define LED_FAST 50 // ms
#define LED_CONST_ON 65535

/**
 * @brief LED driver bootstrap
 *
 * Initializes the hardware configuration from LED
 */
void LED_Bootstrap(void);

/**
 * @brief Intializes all relative configuration to the LED driver
 */
void LED_Init(void);

/**
 * @brief Change status LED speed
 *
 * @param LED blinking period
 */
void LED_Mode(UINT16 period);

/**
 * @brief Instant turn-off
 *
 * Instantly turns off the LED
 */
#define LED_ForceOff() (LED_PORT &= ~LED_MASK)

/**
 * @brief Instant turn-on
 *
 * Instantly turns on the LED
 */
#define LED_ForceOn() (LED_PORT |= LED_MASK)


#endif	/* _LED_H_ */

