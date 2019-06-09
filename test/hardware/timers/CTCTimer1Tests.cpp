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

#include "../../../src/hardware/timers/CTCTimer1.h"
#include "../../mocks/hardware/MockIInterruptsControl.h"

#include <arduino-platform.h>
#include <gtest/gtest.h>

// thanks to stack overflow for this nasty thing ;-P
// https://stackoverflow.com/a/523737
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

namespace hardware_timers_tests
{
    using namespace testing;
    using Prescaler = hardware::timers::Prescaler;

    class hardware_timers_CTCTimer1
        : public hardware::timers::CTCTimer1
        , public ::testing::Test
    {
    public:
        int shouldBeCleared = 0;

        hardware_mocks::MockIInterruptsControl interruptsControl;
        hardware::timers::CTCModeSettings settings{19999, Prescaler::PS_8};

        hardware_timers_CTCTimer1() : CTCTimer1(&interruptsControl)
        {
        }
    };

    TEST_F(hardware_timers_CTCTimer1,
           setup_GivenCTCModeSettings_ShouldUseTheInterruptsControl)
    {
        InSequence seq;
        EXPECT_CALL(interruptsControl, disableInterrupts());
        EXPECT_CALL(interruptsControl, enableInterrupts());

        setup(settings);
    }

    TEST_F(hardware_timers_CTCTimer1,
           setup_GivenCTCModeSettings_ShouldClearControlRegisterA)
    {
        setup(settings);
        EXPECT_EQ(ControlRegisterA->readRegister(), shouldBeCleared);
    }

    TEST_F(hardware_timers_CTCTimer1,
           setup_GivenCTCModeSettings_ShouldClearCounterRegister)
    {
        setup(settings);
        EXPECT_EQ(CounterRegister->readRegister(), shouldBeCleared);
    }

    TEST_F(hardware_timers_CTCTimer1,
           setup_GivenCTCModeSettings_ShouldSetCompareMatchRegister)
    {
        setup(settings);
        EXPECT_EQ(CompareMatchRegister->readRegister(),
                  settings.getCompareMatchRegister());
    }

    TEST_F(hardware_timers_CTCTimer1,
           setup_GivenCTCModeSettings_SetsUpCTCInControlRegisterB)
    {
        setup(settings);

        // CTCMode set on bit 3 in TCCR1B
        EXPECT_TRUE(CHECK_BIT(ControlRegisterB->readRegister(), 3));
    }

    TEST_F(hardware_timers_CTCTimer1,
           setup_GivenCTCModeSettings_SetsUpAppropriatePrescalerInRegisterB)
    {
        setup(settings);

        // Prescaler 8 is TCCR1B | 0b010
        EXPECT_FALSE(CHECK_BIT(ControlRegisterB->readRegister(), 0));
        EXPECT_TRUE(CHECK_BIT(ControlRegisterB->readRegister(), 1));
        EXPECT_FALSE(CHECK_BIT(ControlRegisterB->readRegister(), 2));
    }

    TEST_F(hardware_timers_CTCTimer1,
           setup_GivenCTCModeSettings_ShouldSetControlRegisterB)
    {
        setup(settings);

        // redundant, but to make sure
        EXPECT_EQ(ControlRegisterB->readRegister(), 0b1010);
    }

    TEST_F(hardware_timers_CTCTimer1,
           setup_GivenCTCModeSettings_DoesntEnableTimerCompareInterrupt)
    {
        setup(settings);
        EXPECT_FALSE(CHECK_BIT(InterruptMaskRegister->readRegister(), 1));
    }

    TEST_F(hardware_timers_CTCTimer1, start_WhenTimerSetUp_StartsCTCTimer)
    {
        setup(settings);
        Mock::VerifyAndClear(&interruptsControl);

        InSequence seq;
        EXPECT_CALL(interruptsControl, disableInterrupts());
        EXPECT_CALL(interruptsControl, enableInterrupts());

        start();
        EXPECT_TRUE(CHECK_BIT(InterruptMaskRegister->readRegister(), 1));
    }
} // namespace hardware_timers_tests
