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

#include "ILedConverter.h"
#include "LedConfiguration.h"

#include <stdint.h>

namespace adapter
{
    class LedConverter : public ILedConverter
    {
        static const int USB_LED_NUM_LOCK_BIT = (1 << 0);
        static const int USB_LED_CAPS_LOCK_BIT = (1 << 1);
        static const int USB_LED_SCROLL_LOCK_BIT = (1 << 2);
        static const int USB_LED_COMPOSE_BIT = (1 << 3);

    public:
        LedConfiguration fromUsbLeds(uint8_t usbLeds) override;
    };
} // namespace adapter
