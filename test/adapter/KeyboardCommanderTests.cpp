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

#include "../../src/adapter/Command.h"
#include "../../src/adapter/KeyboardCommander.h"
#include "../mocks/hardware/MockISerialPort.h"

#include <arduino-platform.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdint.h>

namespace adapter_tests
{
    using namespace testing;

    class adapter_KeyboardCommander : public ::testing::Test
    {
    public:
        hardware_mocks::MockISerialPort serialPort;
        adapter::KeyboardCommander sut{&serialPort};
    };

    TEST_F(adapter_KeyboardCommander,
           turnOnClicks_GivenSerialPort_SendsEnableClickCommand)
    {
        auto expectedCommand = adapter::Command::ENABLE_CLICK;
        EXPECT_CALL(serialPort, write(expectedCommand));
        sut.turnOnClicks();
    }

    TEST_F(adapter_KeyboardCommander,
           turnOffClicks_GivenSerialPort_SendsDisableClickCommand)
    {
        auto expectedCommand = adapter::Command::DISABLE_CLICK;
        EXPECT_CALL(serialPort, write(expectedCommand));
        sut.turnOffClicks();
    }
} // namespace adapter_tests
