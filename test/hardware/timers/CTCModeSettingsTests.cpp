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

    class hardware_timers_CTCModeSettings : public Test
    {
    public:
        const int CS12 = 2;
        const int CS11 = 1;
        const int CS10 = 0;

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

    TEST_F(hardware_timers_CTCModeSettings,
           getPrescalerRegister_GivenPS1_Returns001)
    {
        sut = {compareMatchRegister, Prescaler::PS_1};
        EXPECT_EQ(sut.getPrescalerRegister(), 0b001);
    }

    TEST_F(hardware_timers_CTCModeSettings,
           getPrescalerRegister_GivenPS8_Returns010)
    {
        sut = {compareMatchRegister, Prescaler::PS_8};
        EXPECT_EQ(sut.getPrescalerRegister(), 0b010);
    }

    TEST_F(hardware_timers_CTCModeSettings,
           getPrescalerRegister_GivenPS64_Returns011)
    {
        sut = {compareMatchRegister, Prescaler::PS_64};
        EXPECT_EQ(sut.getPrescalerRegister(), 0b011);
    }

    TEST_F(hardware_timers_CTCModeSettings,
           getPrescalerRegister_GivenPS256_Returns100)
    {
        sut = {compareMatchRegister, Prescaler::PS_256};
        EXPECT_EQ(sut.getPrescalerRegister(), 0b100);
    }

    TEST_F(hardware_timers_CTCModeSettings,
           getPrescalerRegister_GivenPS1024_Returns101)
    {
        sut = {compareMatchRegister, Prescaler::PS_1024};
        EXPECT_EQ(sut.getPrescalerRegister(), 0b101);
    }

    TEST_F(hardware_timers_CTCModeSettings,
           getPrescalerRegister_GivenUnmappedPrescaler_Returns000)
    {
        sut = {compareMatchRegister, (Prescaler)0};
        EXPECT_EQ(sut.getPrescalerRegister(), 0b000);

        sut = {compareMatchRegister, (Prescaler)2};
        EXPECT_EQ(sut.getPrescalerRegister(), 0b000);
    }

    TEST_F(hardware_timers_CTCModeSettings,
           operatorEquals_GivenSameProperties_ReturnsTrue)
    {
        hardware::timers::CTCModeSettings first{1337, Prescaler::PS_64};
        hardware::timers::CTCModeSettings second{1337, Prescaler::PS_64};
        EXPECT_TRUE(first == second);
    }

    TEST_F(hardware_timers_CTCModeSettings,
           operatorEquals_GivenDifferingRegister_ReturnsFalse)
    {
        hardware::timers::CTCModeSettings first{1337, Prescaler::PS_64};
        hardware::timers::CTCModeSettings second{1338, Prescaler::PS_64};
        EXPECT_FALSE(first == second);
    }

    TEST_F(hardware_timers_CTCModeSettings,
           operatorEquals_GivenDifferingPrescaler_ReturnsFalse)
    {
        hardware::timers::CTCModeSettings first{1337, Prescaler::PS_64};
        hardware::timers::CTCModeSettings second{1338, Prescaler::PS_8};
        EXPECT_FALSE(first == second);
    }
} // namespace hardware_timers_tests
