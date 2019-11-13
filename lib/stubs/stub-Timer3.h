/*
 * Sun to USB keyboard adapter
 * Copyright (C) 2019  Simon Wendel
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdint.h>

extern uint8_t TCCR3A;
#define WGM30 0
#define WGM31 1
#define COM3C0 2
#define COM3C1 3
#define COM3B0 4
#define COM3B1 5
#define COM3A0 6
#define COM3A1 7

extern uint8_t TCCR3B;
#define CS30 0
#define CS31 1
#define CS32 2
#define WGM32 3
#define WGM33 4
#define ICES3 6
#define ICNC3 7

extern uint16_t TCNT3;
extern uint16_t OCR3A;

extern uint8_t TIMSK3;
#define ICIE3 5
#define OCIE3B 2
#define OCIE3A 1
#define TOIE3 0

#ifndef _VECTOR
#define _VECTOR(N) __vector_##N
#endif

#define TIMER3_COMPA_vect_num 32
#define TIMER3_COMPA_vect _VECTOR(32) /* Timer/Counter3 Compare Match A */

#define ISR(vector, ...)                                                       \
    extern "C" void vector(void) __attribute__((signal, __INTR_ATTRS))         \
    __VA_ARGS__;                                                               \
    void vector(void)
