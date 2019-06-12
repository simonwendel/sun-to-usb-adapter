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

#include "../../src/program/ErrorIndicator.h"
#include "../mocks/hardware/timers/MockICTCTimer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace program_tests
{
    using namespace testing;

    class program_ErrorIndicator : public ::testing::Test
    {
    public:
        hardware_timers_mocks::MockICTCTimer blinkTimer;
        program::ErrorIndicator sut{&blinkTimer};
    };

    TEST_F(program_ErrorIndicator, isSet_BeforeCallingSet_ReturnsFalse)
    {
        EXPECT_FALSE(sut.isSet());
    }

    TEST_F(program_ErrorIndicator, isSet_AfterCallingSet_ReturnsTrue)
    {
        sut.set();
        EXPECT_TRUE(sut.isSet());
    }

    TEST_F(program_ErrorIndicator, set_WhenCalledFirstTime_StartsBlinkTimer)
    {
        EXPECT_CALL(blinkTimer, start()).Times(1);
        sut.set();
    }

    TEST_F(program_ErrorIndicator,
           set_WhenCalledMoreThanOnce_OnlyStartsBlinkTimerOnce)
    {
        EXPECT_CALL(blinkTimer, start()).Times(1);
        sut.set();
        sut.set();
    }
} // namespace program_tests
