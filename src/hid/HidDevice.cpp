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

#include "HidDevice.h"

#include <HID-Project.h>
#include <stdint.h>

namespace hid
{
    HidDevice::HidDevice()
    {
        BootKeyboard.begin();
        BootKeyboard.releaseAll();
    }

    void HidDevice::pressKey(KeyboardKeycode key)
    {
        BootKeyboard.press(key);
    }

    void HidDevice::releaseKey(KeyboardKeycode key)
    {
        BootKeyboard.release(key);
    }

    void HidDevice::releaseAll()
    {
        BootKeyboard.releaseAll();
    }
} // namespace hid