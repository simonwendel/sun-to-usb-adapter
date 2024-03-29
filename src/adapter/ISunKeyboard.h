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

#include "LedConfiguration.h"

namespace adapter
{
    class ISunKeyboard
    {
    public:
        virtual void turnOnClicks() = 0;
        virtual void turnOffClicks() = 0;

        virtual void turnOnBell() = 0;
        virtual void turnOffBell() = 0;

        virtual void setLeds(LedConfiguration leds) = 0;

        virtual int read() = 0;
    };
} // namespace adapter
