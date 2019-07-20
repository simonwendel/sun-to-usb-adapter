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

#include "../../src/adapter/HidCode.h"
#include "../../src/adapter/ISetting.h"
#include "../../src/adapter/Program.h"
#include "../../src/adapter/Translation.h"
#include "../mocks/adapter/MockIFlashingLight.h"
#include "../mocks/adapter/MockILog.h"
#include "../mocks/adapter/MockIScanCodeTranslator.h"
#include "../mocks/adapter/MockISetting.h"
#include "../mocks/adapter/MockISunKeyboard.h"

#include <arduino-platform.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace adapter_tests
{
    using namespace testing;

    class adapter_Program : public Test
    {
    public:
        int invalidCode = 137;
        adapter::Translation invalidTranslation =
        adapter::Translation::makeInvalid();

        int validCode = 110;
        adapter::Translation validTranslation =
        adapter::Translation::makeValid(adapter::HidCode{});

        adapter::LedCommand leds;

        adapter_mocks::MockISetting keyboardClicks;
        adapter_mocks::MockISetting numLock;
        adapter_mocks::MockISunKeyboard sunKeyboard;
        adapter_mocks::MockILog log;
        adapter_mocks::MockIScanCodeTranslator translator;
        adapter_mocks::MockIFlashingLight errorIndicator;

        adapter::Program sut{&log,
                             &keyboardClicks,
                             &numLock,
                             &sunKeyboard,
                             &translator,
                             &errorIndicator};

        adapter_Program()
        {
            ON_CALL(sunKeyboard, read()).WillByDefault(Return(invalidCode));

            ON_CALL(translator, translate(invalidCode))
            .WillByDefault(Return(invalidTranslation));

            ON_CALL(translator, translate(validCode))
            .WillByDefault(Return(validTranslation));
        }
    };

    TEST_F(adapter_Program, setup_GivenKeyboardClickSetting_ReadsSetting)
    {
        EXPECT_CALL(keyboardClicks, isOn());
        sut.setup();
    }

    TEST_F(adapter_Program,
           setup_GivenKeyboardClickSettingIsOn_TurnsOnKeyboardClicks)
    {
        ON_CALL(keyboardClicks, isOn()).WillByDefault(Return(true));
        EXPECT_CALL(sunKeyboard, turnOnClicks());
        sut.setup();
    }

    TEST_F(adapter_Program,
           setup_GivenKeyboardClickSettingIsOff_DoesNotTurnOnKeyboardClicks)
    {
        ON_CALL(keyboardClicks, isOn()).WillByDefault(Return(false));
        EXPECT_CALL(sunKeyboard, turnOnClicks()).Times(Exactly(0));
        sut.setup();
    }

    TEST_F(adapter_Program, setup_GivenNumLockSetting_ReadsSetting)
    {
        EXPECT_CALL(numLock, isOn());
        sut.setup();
    }

    TEST_F(adapter_Program, setup_GivenNumLockSettingIsOn_TurnsOnNumLock)
    {
        leds.setNumLock();
        ON_CALL(numLock, isOn()).WillByDefault(Return(true));

        EXPECT_CALL(sunKeyboard, setLeds(leds));

        sut.setup();
    }

    TEST_F(adapter_Program, setup_GivenNumLockSettingIsOff_DoesNotTurnOnNumLock)
    {
        ON_CALL(numLock, isOn()).WillByDefault(Return(false));
        EXPECT_CALL(sunKeyboard, setLeds(_)).Times(Exactly(0));
        sut.setup();
    }

    TEST_F(adapter_Program, setup_WhenSetupCompletes_LogsInfoMessage)
    {
        String message{"Setup completed."};

        Expectation clicksSetup = EXPECT_CALL(keyboardClicks, isOn());
        Expectation numLockSetup = EXPECT_CALL(numLock, isOn());

        EXPECT_CALL(log, info(message)).After(clicksSetup, numLockSetup);

        sut.setup();
    }

    TEST_F(adapter_Program, loop_WhenFirstCalled_LogsInfoMessage)
    {
        String message{"Adapter started."};
        EXPECT_CALL(log, info(message));
        sut.loop();
    }

    TEST_F(adapter_Program, loop_WhenLaterCalled_DoesntLogInfoMessageAgain)
    {
        EXPECT_CALL(log, info(_)).Times(1);

        sut.loop();
        sut.loop();
        sut.loop();
        sut.loop();
    }

    TEST_F(adapter_Program, loop_WhenReadingFromSerialPort_AttemptsTranslation)
    {
        ON_CALL(sunKeyboard, read()).WillByDefault(Return(validCode));
        EXPECT_CALL(translator, translate(validCode));
        sut.loop();
    }

    TEST_F(adapter_Program, loop_WhenTranslationFails_LogsAnError)
    {
        String message{"Failed to translate, invalid code."};
        EXPECT_CALL(log, error(message));
        sut.loop();
    }

    TEST_F(
    adapter_Program,
    loop_WhenTranslationFailsAndErrorIndicatorFlashing_DoesNotStartFlashing)
    {
        ON_CALL(errorIndicator, isFlashing()).WillByDefault(Return(true));
        EXPECT_CALL(errorIndicator, startFlashing()).Times(0);
        sut.loop();
    }

    TEST_F(adapter_Program,
           loop_WhenTranslationFailsAndErrorIndicatorNotFlashing_StartsFlashing)
    {
        ON_CALL(errorIndicator, isFlashing()).WillByDefault(Return(false));
        EXPECT_CALL(errorIndicator, startFlashing());
        sut.loop();
    }
} // namespace adapter_tests
