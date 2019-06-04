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

#include "../../../src/hardware/timers/CTCModeSettings.h"

#include <gtest/gtest.h>

namespace hardware_timers_tests
{
    using namespace testing;
    using Prescaler = hardware::timers::Prescaler;

    class hardware_timers_CTCModeSettings : public ::testing::Test
    {
    public:
        Prescaler prescaler = Prescaler::PS_256;
        int compareMatchRegister = 23123;
        hardware::timers::CTCModeSettings sut{compareMatchRegister, prescaler};
    };

    TEST_F(hardware_timers_CTCModeSettings,
           constructor_GivenCompareMatchRegister_SetsRegister)
    {
        ASSERT_EQ(sut.getCompareMatchRegister(), compareMatchRegister);
    }

    TEST_F(hardware_timers_CTCModeSettings,
           constructor_GivenPrescaler_SetsPrescaler)
    {
        ASSERT_EQ(sut.getCompareMatchRegister(), compareMatchRegister);
    }
} // namespace hardware_timers_tests
