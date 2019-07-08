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

#include "../../src/program/Log.h"
#include "../mocks/hardware/MockISerialPort.h"

#include <arduino-platform.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdint.h>

namespace program_tests
{
    using namespace testing;

    class program_Log : public Test
    {
    public:
        hardware_mocks::MockISerialPort serialPort;
        program::Log sut{&serialPort};
    };

    TEST_F(program_Log, info_GivenMessage_WritesToSerialPort)
    {
        String prefix{"INFO: "};
        String message{"This is an info message!"};

        InSequence seq;
        EXPECT_CALL(serialPort, print(prefix));
        EXPECT_CALL(serialPort, println(message));

        sut.info(message);
    }

    TEST_F(program_Log, error_GivenMessage_WritesToSerialPort)
    {
        String prefix{"ERROR: "};
        String message{"This is an error message!"};

        InSequence seq;
        EXPECT_CALL(serialPort, print(prefix));
        EXPECT_CALL(serialPort, println(message));

        sut.error(message);
    }
} // namespace program_tests
