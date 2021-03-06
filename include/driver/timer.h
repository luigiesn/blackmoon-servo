/*
 * Timer driver - part of Blackmoon servo controller
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

#ifndef _TIMER_H_
#define	_TIMER_H_

#include <xc.h>
#include "../defs.h"

#define NUM_MAX_TIMERS 5 // max = 255

typedef void (*TimerCallbackFunction)(void);

typedef struct {
    UINT16 period;
    UINT16 elapsedTime;

    TimerCallbackFunction pCallbackFunction;

    bool autoReload;
    bool enabled;
} Timer;

void TIMER_Bootstrap(void);

void TIMER_Process(void);

bool TIMER_Create(Timer* timer, TimerCallbackFunction pCallbackFunction);

void TIMER_SetPeriod(Timer* timer, UINT16 period);

void TIMER_Start(Timer* timer, bool autoReload);

void TIMER_Stop(Timer* timer);

void TIMER_HwEventHandle(void);

#endif	/* _TIMER_H_ */

