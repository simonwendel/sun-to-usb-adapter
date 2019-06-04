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

#include "../../../src/hardware/timers/CTCModeCalculator.h"

#include <gtest/gtest.h>

namespace hardware_timers_tests
{
    using namespace testing;
    using Prescaler = hardware::timers::Prescaler;

    class hardware_timers_CTCModeCalculator : public ::testing::Test
    {
    public:
        Prescaler defaultPrescalers[5] = {Prescaler::PS_1,
                                          Prescaler::PS_8,
                                          Prescaler::PS_64,
                                          Prescaler::PS_256,
                                          Prescaler::PS_1024};
        hardware::timers::CTCModeCalculator sut;
    };

    TEST_F(hardware_timers_CTCModeCalculator,
           createSettings_GivenTooLowFrequencyToFit_ReturnsInvalid)
    {
        auto results = sut.createSettings(0.238);
        EXPECT_FALSE(results.valid);
    }

    TEST_F(hardware_timers_CTCModeCalculator,
           createSettings_GivenWayTooHighFrequencyToFit_ReturnsInvalid)
    {
        auto results = sut.createSettings(sut.CpuFrequencyMhz * 10e6 + 1e-1);
        EXPECT_FALSE(results.valid);
    }

    TEST_F(hardware_timers_CTCModeCalculator,
           createSettings_GivenCpuFrequencyToFit_ReturnsZeroRegister)
    {
        auto results = sut.createSettings(sut.CpuFrequencyMhz * 1e6);
        EXPECT_TRUE(results.valid);
        EXPECT_EQ(results.value.getCompareMatchRegister(), 0);
    }

    TEST_F(hardware_timers_CTCModeCalculator,
           createSettings_GivenFrequencyToFit_ReturnsRegister)
    {
        auto results = sut.createSettings(2);
        EXPECT_TRUE(results.valid);
        EXPECT_EQ(results.value.getCompareMatchRegister(), 31249);
    }

    TEST_F(hardware_timers_CTCModeCalculator,
           createSettings_GivenFrequencyToFit_ReturnsLowestPossiblePrescaler)
    {
        auto results = sut.createSettings(2);
        EXPECT_TRUE(results.valid);
        EXPECT_EQ(results.value.getPrescaler(), Prescaler::PS_256);
    }

    TEST_F(hardware_timers_CTCModeCalculator,
           constant_Prescalers_HasDefaultValue)
    {
        int arrayLength = sizeof(sut.Prescalers) / sizeof(sut.Prescalers[0]);

        EXPECT_EQ(arrayLength, 5);
        for (int index = 0; index < arrayLength; ++index)
        {
            EXPECT_EQ(sut.Prescalers[index], defaultPrescalers[index]);
        }
    }

    TEST_F(hardware_timers_CTCModeCalculator,
           constant_TimerBits_HasDefaultValue)
    {
        EXPECT_EQ(sut.TimerBits, 16);
    }

    TEST_F(hardware_timers_CTCModeCalculator,
           constant_CpuFrequency_HasDefaultValue)
    {
        EXPECT_EQ(sut.CpuFrequencyMhz, 16);
    }
} // namespace hardware_timers_tests
