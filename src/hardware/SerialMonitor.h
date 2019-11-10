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

#include "ISerialPort.h"

#include <arduino-platform.h>
#include <stdint.h>

namespace hardware
{
    class SerialMonitor : public ISerialPort
    {
    public:
        void begin(long speed) override;
        int read() override;

        size_t write(uint8_t byte) override;
        size_t write(const uint8_t *buffer, size_t size) override;

        size_t print(const String &s) override;
        size_t println(const String &s) override;
    };
} // namespace hardware
