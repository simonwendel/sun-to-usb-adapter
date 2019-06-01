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

#include "../../src/adapter/Setting.h"
#include "../mocks/hardware/MockIInputPin.h"

#include <arduino-platform.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace adapter_tests
{
    using namespace testing;

    class adapter_Setting : public ::testing::Test
    {
    public:
        hardware_mocks::MockIInputPin inputPin;
    };

    TEST_F(adapter_Setting, isOn_WhenInputPinIsLow_ReturnsFalse)
    {
        ON_CALL(inputPin, getState()).WillByDefault(Return(LOW));
        EXPECT_CALL(inputPin, getState()).Times(Exactly(1));

        adapter::Setting sut{&inputPin};

        EXPECT_EQ(sut.isOn(), false);
    }

    TEST_F(adapter_Setting, isOn_WhenInputPinIsHigh_ReturnsTrue)
    {
        ON_CALL(inputPin, getState()).WillByDefault(Return(HIGH));
        EXPECT_CALL(inputPin, getState()).Times(Exactly(1));

        adapter::Setting sut{&inputPin};

        EXPECT_EQ(sut.isOn(), true);
    }
} // namespace adapter_tests
