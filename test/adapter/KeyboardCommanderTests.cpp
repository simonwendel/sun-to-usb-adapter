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
#include "../../src/adapter/LedCommand.h"
#include "../mocks/hardware/MockISerialPort.h"

#include <arduino-platform.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace adapter_tests
{
    using namespace testing;

    class adapter_KeyboardCommander : public Test
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

    TEST_F(adapter_KeyboardCommander,
           turnOnBell_GivenSerialPort_SendsEnableBellCommand)
    {
        auto expectedCommand = adapter::Command::ENABLE_BELL;
        EXPECT_CALL(serialPort, write(expectedCommand));
        sut.turnOnBell();
    }

    TEST_F(adapter_KeyboardCommander,
           turnOffBell_GivenSerialPort_SendsDisableBellCommand)
    {
        auto expectedCommand = adapter::Command::DISABLE_BELL;
        EXPECT_CALL(serialPort, write(expectedCommand));
        sut.turnOffBell();
    }

    TEST_F(adapter_KeyboardCommander,
           setLeds_GivenLedCommandPayload_WritesSequenceToSerialPort)
    {
        adapter::LedCommand leds;
        leds.setNumLock();
        leds.setScrollLock();

        uint8_t expectedSequence[] = {adapter::Command::SET_LEDS, leds};

        auto verifySequence = [expectedSequence](const uint8_t *actualSequence,
                                                 const uint8_t size) {
            EXPECT_EQ(size, 2);
            for (size_t i = 0; i < size; ++i)
            {
                EXPECT_EQ(expectedSequence[i], actualSequence[i]);
            }
        };

        EXPECT_CALL(serialPort, write(_, 2))
        .WillOnce(DoAll(Invoke(verifySequence), Return(2)));

        sut.setLeds(leds);
    }
} // namespace adapter_tests
