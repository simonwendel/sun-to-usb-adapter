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

#include "../../src/hardware/InputPin.h"
#include "MockIPinControl.h"

#include <arduino-platform.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace hardware_tests
{
    using namespace testing;

    class hardware_InputPin : public ::testing::Test
    {
    public:
        int boardPin = 13;
        MockIPinControl pinControl;
    };

    TEST_F(hardware_InputPin,
           constructor_GivenPinControl_SetsSuppliedPinAsInput)
    {
        EXPECT_CALL(pinControl, pinMode(boardPin, INPUT)).Times(Exactly(1));

        hardware::InputPin sut{pinControl, boardPin};
    }

    TEST_F(hardware_InputPin, getState_GivenPinControl_ReadsStateFromPin)
    {
        auto expected = 10;
        ON_CALL(pinControl, digitalRead(boardPin))
        .WillByDefault(Return(expected));

        EXPECT_CALL(pinControl, pinMode(boardPin, INPUT)).Times(Exactly(1));

        hardware::InputPin sut{pinControl, boardPin};

        EXPECT_EQ(sut.getState(), expected);
    }
} // namespace hardware_tests
