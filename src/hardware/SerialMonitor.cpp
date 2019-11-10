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

#include "SerialMonitor.h"

#include <arduino-platform.h>
#include <stdint.h>

namespace hardware
{
    void SerialMonitor::begin(long speed)
    {
        Serial.begin(speed);
    }

    int SerialMonitor::read()
    {
        return Serial.read();
    }

    size_t SerialMonitor::write(uint8_t byte)
    {
        return Serial.write(byte);
    }

    size_t SerialMonitor::write(const uint8_t *buffer, size_t size)
    {
        return Serial.write(buffer, size);
    }

    size_t SerialMonitor::print(const String &s)
    {
        return Serial.print(s);
    }

    size_t SerialMonitor::println(const String &s)
    {
        return Serial.println(s);
    }
} // namespace hardware
