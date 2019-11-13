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

#include "../adapter/HidCode.h"
#include "../adapter/IUsbKeyboard.h"
#include "IHidDevice.h"

namespace hid
{
    class UsbKeyboard : public adapter::IUsbKeyboard
    {
        IHidDevice *hidDevice;

    public:
        UsbKeyboard(IHidDevice *hidDevice);
        void emit(adapter::HidCode hidCode) override;
        uint8_t getLeds() override;
    };
} // namespace hid
