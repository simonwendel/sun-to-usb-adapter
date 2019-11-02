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

#include "SerialPort.h"

#include <arduino-platform.h>

namespace hardware
{
    SerialPort::SerialPort(uint8_t receivePin, uint8_t transmitPin) :
        SerialPort(receivePin, transmitPin, false)
    {
    }

    SerialPort::SerialPort(uint8_t receivePin,
                           uint8_t transmitPin,
                           bool inverse_logic)
    {
        serial = new SoftwareSerial{receivePin, transmitPin, inverse_logic};
    }

    void SerialPort::begin(long speed)
    {
        serial->begin(speed);
    }

    int SerialPort::read()
    {
        return serial->read();
    }

    size_t SerialPort::write(uint8_t byte)
    {
        return serial->write(byte);
    }

    size_t SerialPort::write(const uint8_t *buffer, size_t size)
    {
        return serial->write(buffer, size);
    }

    size_t SerialPort::print(const String &s)
    {
        return serial->print(s);
    }

    size_t SerialPort::println(const String &s)
    {
        return serial->println(s);
    }
} // namespace hardware
