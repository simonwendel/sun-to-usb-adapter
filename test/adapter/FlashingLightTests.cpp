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

#include "../../src/adapter/FlashingLight.h"
#include "../mocks/adapter/MockIToggle.h"
#include "../mocks/hardware/timers/MockICTCModeCalculator.h"
#include "../mocks/hardware/timers/MockICTCTimer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace adapter_tests
{
    using namespace testing;
    using Prescaler = hardware::timers::Prescaler;
    using CalculationResult = hardware::timers::CalculationResult;

    class adapter_FlashingLight : public Test
    {
    public:
        float frequencyHz = 2;
        hardware::timers::CTCModeSettings settings{31249, Prescaler::PS_256};

        testing::internal::AnythingMatcher anyTimerFunction = _;
        hardware_timers_mocks::MockICTCTimer timer;
        hardware_timers_mocks::MockICTCModeCalculator calculator;
        adapter_mocks::MockIToggle toggle;

        adapter::FlashingLight sut{&toggle, &timer, &calculator};

        adapter_FlashingLight()
        {
            CalculationResult calculationResults{true, settings};
            ON_CALL(calculator, createSettings(frequencyHz))
            .WillByDefault(Return(calculationResults));
        }
    };

    TEST_F(adapter_FlashingLight,
           isFlashing_BeforeCallingStartFlashing_ReturnsFalse)
    {
        EXPECT_FALSE(sut.isFlashing());
    }

    TEST_F(adapter_FlashingLight,
           isFlashing_AfterCallingStartFlashing_ReturnsTrue)
    {
        sut.startFlashing(frequencyHz);
        EXPECT_TRUE(sut.isFlashing());
    }

    TEST_F(adapter_FlashingLight,
           startFlashing_WhenCalledFirstTime_CalculatesTimerSettings)
    {
        EXPECT_CALL(calculator, createSettings(frequencyHz)).Times(1);
        sut.startFlashing(frequencyHz);
    }

    TEST_F(adapter_FlashingLight,
           startFlashing_WhenCalledFirstTime_SetsUpBlinkTimer)
    {
        EXPECT_CALL(timer, setup(settings, anyTimerFunction)).Times(1);
        sut.startFlashing(frequencyHz);
    }

    TEST_F(adapter_FlashingLight,
           startFlashing_WhenCalledFirstTime_StartsBlinkTimer)
    {
        EXPECT_CALL(timer, start()).Times(1);
        sut.startFlashing(frequencyHz);
    }

    TEST_F(adapter_FlashingLight,
           startFlashing_WhenCalledMoreThanOnce_OnlyCalculatesTimerSettingsOnce)
    {
        EXPECT_CALL(calculator, createSettings(frequencyHz)).Times(1);
        sut.startFlashing(frequencyHz);
        sut.startFlashing(frequencyHz);
    }

    TEST_F(adapter_FlashingLight,
           startFlashing_WhenCalledMoreThanOnce_OnlySetsUpBlinkTimerOnce)
    {
        EXPECT_CALL(timer, setup(settings, anyTimerFunction)).Times(1);
        sut.startFlashing(frequencyHz);
        sut.startFlashing(frequencyHz);
    }

    TEST_F(adapter_FlashingLight,
           startFlashing_WhenCalledMoreThanOnce_OnlyStartsBlinkTimerOnce)
    {
        EXPECT_CALL(timer, start()).Times(1);
        sut.startFlashing(frequencyHz);
        sut.startFlashing(frequencyHz);
    }

    TEST_F(adapter_FlashingLight,
           startFlashing_WhenSetupCallbackInvoked_TogglesOutput)
    {
        // invoke the callback provided to timer setup
        EXPECT_CALL(timer, setup(settings, anyTimerFunction))
        .WillRepeatedly(testing::InvokeArgument<1>());

        EXPECT_CALL(toggle, toggle()).Times(1);

        sut.startFlashing(2);
    }

    TEST_F(adapter_FlashingLight,
           stopFlashing_WhenTimerHasNotStarted_DoesntStopBlinkTimer)
    {
        EXPECT_CALL(timer, stop()).Times(0);
        sut.stopFlashing();
    }

    TEST_F(adapter_FlashingLight,
           stopFlashing_WhenTimerHasNotStarted_DoesntResetOutputToggle)
    {
        EXPECT_CALL(toggle, reset()).Times(0);
        sut.stopFlashing();
    }

    TEST_F(adapter_FlashingLight,
           stopFlashing_WhenTimerHasStarted_StopsBlinkTimer)
    {
        EXPECT_CALL(timer, stop());
        sut.startFlashing(frequencyHz);
        sut.stopFlashing();
    }

    TEST_F(adapter_FlashingLight,
           stopFlashing_WhenTimerHasStarted_ResetsOutputToggle)
    {
        EXPECT_CALL(toggle, reset());
        sut.startFlashing(frequencyHz);
        sut.stopFlashing();
    }
} // namespace adapter_tests
