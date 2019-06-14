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

#include "stub-SoftwareSerial.h"

#include <stdint.h>

#ifdef STUB_ARDUINO

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wunused-parameter"

SoftwareSerial::SoftwareSerial(uint8_t receivePin, uint8_t transmitPin)
{
}

SoftwareSerial::SoftwareSerial(uint8_t receivePin,
                               uint8_t transmitPin,
                               bool inverseLogic)
{
}

int SoftwareSerial::read()
{
}

size_t SoftwareSerial::write(uint8_t byte)
{
}

size_t SoftwareSerial::write(const uint8_t *buffer, size_t size)
{
}

#pragma GCC diagnostic pop

#endif
