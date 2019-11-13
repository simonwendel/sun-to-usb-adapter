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
#include "../../src/adapter/LedChecker.h"
#include "../mocks/adapter/MockILedConverter.h"
#include "../mocks/adapter/MockISunKeyboard.h"
#include "../mocks/adapter/MockIUsbKeyboard.h"
#include "../mocks/hardware/timers/MockICTCModeCalculator.h"
#include "../mocks/hardware/timers/MockICTCTimer.h"

#include <gtest/gtest.h>

namespace adapter_tests
{
    using namespace testing;
    using Prescaler = hardware::timers::Prescaler;
    using CalculationResult = hardware::timers::CalculationResult;

    class adapter_LedChecker : public Test
    {
    public:
        float frequencyHz = 2;
        hardware::timers::CTCModeSettings settings{31249, Prescaler::PS_256};
        uint8_t someUsbLeds = 0b0011;
        adapter::LedConfiguration defaultLeds;
        adapter::LedConfiguration changedLeds{0b0101};

        testing::internal::AnythingMatcher anyTimerFunction = _;

        hardware_timers_mocks::MockICTCTimer timer;
        hardware_timers_mocks::MockICTCModeCalculator calculator;
        adapter_mocks::MockIUsbKeyboard usbKeyboard;
        adapter_mocks::MockISunKeyboard sunKeyboard;
        adapter_mocks::MockILedConverter ledConverter;

        adapter::LedChecker sut{
        &timer, &calculator, &usbKeyboard, &sunKeyboard, &ledConverter};

        adapter_LedChecker()
        {
            CalculationResult calculationResults{true, settings};
            ON_CALL(calculator, createSettings(frequencyHz))
            .WillByDefault(Return(calculationResults));

            ON_CALL(usbKeyboard, getLeds()).WillByDefault(Return(someUsbLeds));
        }
    };

    TEST_F(adapter_LedChecker,
           startChecking_GivenFrequency_CalculatesTimerSettings)
    {
        EXPECT_CALL(calculator, createSettings(frequencyHz)).Times(1);
        sut.startChecking(frequencyHz);
    }

    TEST_F(adapter_LedChecker, startChecking_GivenFrequency_SetsUpCheckTimer)
    {
        EXPECT_CALL(timer, setup(settings, _)).Times(1);
        sut.startChecking(frequencyHz);
    }

    TEST_F(adapter_LedChecker, startChecking_GivenFrequency_StartsCheckTimer)
    {
        EXPECT_CALL(timer, start()).Times(1);
        sut.startChecking(frequencyHz);
    }

    TEST_F(adapter_LedChecker, stopChecking_WhenCalled_StopsCheckTimer)
    {
        EXPECT_CALL(timer, stop()).Times(1);
        sut.stopChecking();
    }

    TEST_F(adapter_LedChecker,
           startChecking_WhenTimerFunctionCalled_ChecksUsbLeds)
    {
        ON_CALL(timer, setup(settings, _)).WillByDefault(InvokeArgument<1>());
        EXPECT_CALL(usbKeyboard, getLeds()).Times(1);
        sut.startChecking(frequencyHz);
    }

    TEST_F(adapter_LedChecker,
           startChecking_WhenTimerFunctionCalled_ConvertsUsbLedsToSun)
    {
        ON_CALL(timer, setup(settings, _)).WillByDefault(InvokeArgument<1>());
        EXPECT_CALL(ledConverter, fromUsbLeds(someUsbLeds)).Times(1);
        sut.startChecking(frequencyHz);
    }

    TEST_F(adapter_LedChecker,
           startChecking_WhenTimerFunctionCalledAndLedsNotChanged_DoesntSetLeds)
    {
        ON_CALL(timer, setup(settings, _)).WillByDefault(InvokeArgument<1>());
        ON_CALL(ledConverter, fromUsbLeds(_))
        .WillByDefault(Return(defaultLeds));
        EXPECT_CALL(sunKeyboard, setLeds(_)).Times(0);
        sut.startChecking(frequencyHz);
    }

    TEST_F(adapter_LedChecker,
           startChecking_WhenTimerFunctionCalledAndLedsChanged_SetLeds)
    {
        ON_CALL(timer, setup(settings, _)).WillByDefault(InvokeArgument<1>());
        ON_CALL(ledConverter, fromUsbLeds(_))
        .WillByDefault(Return(changedLeds));
        EXPECT_CALL(sunKeyboard, setLeds(changedLeds)).Times(1);
        sut.startChecking(frequencyHz);
    }
} // namespace adapter_tests
