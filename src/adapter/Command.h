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

namespace adapter
{
    class Command
    {
    public:
        static const uint8_t RESET = 0x01;

        static const uint8_t DISABLE_CLICK = 0x0B;
        static const uint8_t ENABLE_CLICK = 0x0A;

        static const uint8_t ENABLE_BELL = 0x02;
        static const uint8_t DISABLE_BELL = 0x03;

        static const uint8_t SET_LEDS = 0x0E;
    };
} // namespace adapter
