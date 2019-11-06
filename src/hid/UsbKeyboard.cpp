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

#include "UsbKeyboard.h"

#include "../adapter/HidCode.h"
#include "IHidDevice.h"

#include <HID-Project.h>

namespace hid
{
    UsbKeyboard::UsbKeyboard(IHidDevice *hidDevice) : hidDevice(hidDevice)
    {
    }

    void UsbKeyboard::emit(adapter::HidCode hidCode)
    {
        auto key = KeyboardKeycode(hidCode.getUsageId());
        if (hidCode.isBreakCode())
        {
            hidDevice->releaseKey(key);
        }
        else
        {
            hidDevice->pressKey(key);
        }
    }
} // namespace hid
