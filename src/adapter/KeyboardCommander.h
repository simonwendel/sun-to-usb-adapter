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

#include "../hardware/ISerialPort.h"
#include "IKeyboardCommander.h"

namespace adapter
{
    class KeyboardCommander : public IKeyboardCommander
    {
        hardware::ISerialPort *serialPort;

    public:
        KeyboardCommander(hardware::ISerialPort *serialPort);
        void turnOnClicks() override;
        void turnOffClicks() override;
    };
} // namespace adapter
