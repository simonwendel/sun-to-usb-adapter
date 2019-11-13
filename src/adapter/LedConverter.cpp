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

#include "LedConverter.h"

#include <stdint.h>

namespace adapter
{
    LedConfiguration LedConverter::fromUsbLeds(uint8_t usbLeds)
    {
        LedConfiguration output;

        if (usbLeds & USB_LED_NUM_LOCK_BIT)
        {
            output.setNumLock();
        }

        if (usbLeds & USB_LED_CAPS_LOCK_BIT)
        {
            output.setCapsLock();
        }

        if (usbLeds & USB_LED_SCROLL_LOCK_BIT)
        {
            output.setScrollLock();
        }

        if (usbLeds & USB_LED_COMPOSE_BIT)
        {
            output.setCompose();
        }

        return output;
    }
} // namespace adapter
