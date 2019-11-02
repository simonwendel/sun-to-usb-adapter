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

#include "../../../src/hardware/ISerialPort.h"

#include <arduino-platform.h>
#include <gmock/gmock.h>
#include <stdint.h>
#include <stdlib.h>

namespace hardware_mocks
{
    class MockISerialPort : public hardware::ISerialPort
    {
    public:
        MOCK_METHOD1(begin, void(long));
        MOCK_METHOD0(read, int());
        MOCK_METHOD1(write, size_t(uint8_t));
        MOCK_METHOD2(write, size_t(const uint8_t *, size_t));
        MOCK_METHOD1(print, size_t(const String &));
        MOCK_METHOD1(println, size_t(const String &));
    };
} // namespace hardware_mocks
