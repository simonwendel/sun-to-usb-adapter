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

#include "../../src/adapter/LedConfiguration.h"
#include "../../src/adapter/LedConverter.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace adapter_tests
{
    using namespace testing;

    class adapter_LedConverter : public Test
    {
    public:
        adapter::LedConfiguration allTurnedOff;
        adapter::LedConfiguration allTurnedOn{0b1111};

        adapter::LedConfiguration numLock{0b0001};
        adapter::LedConfiguration compose{0b0010};
        adapter::LedConfiguration scrollLock{0b0100};
        adapter::LedConfiguration capsLock{0b1000};

        uint8_t usbNumLock = 0b0001;
        uint8_t usbCapsLock = 0b0010;
        uint8_t usbScrollLock = 0b0100;
        uint8_t usbCompose = 0b1000;

        adapter::LedConverter sut;
    };

    TEST_F(adapter_LedConverter, fromUsbLeds_GivenAllOff_ReturnsAllOff)
    {
        EXPECT_EQ(sut.fromUsbLeds(0), allTurnedOff);
    }

    TEST_F(adapter_LedConverter, fromUsbLeds_GivenAllOn_ReturnsAllOn)
    {
        EXPECT_EQ(sut.fromUsbLeds(0), allTurnedOff);
    }

    TEST_F(adapter_LedConverter, fromUsbLeds_GivenNumLockOn_ReturnsNumLockOn)
    {
        EXPECT_EQ(sut.fromUsbLeds(usbNumLock), numLock);
    }

    TEST_F(adapter_LedConverter, fromUsbLeds_GivenCapsLockOn_ReturnsCapsLockOn)
    {
        EXPECT_EQ(sut.fromUsbLeds(usbCapsLock), capsLock);
    }

    TEST_F(adapter_LedConverter,
           fromUsbLeds_GivenScrollLockOn_ReturnsScrollLockOn)
    {
        EXPECT_EQ(sut.fromUsbLeds(usbScrollLock), scrollLock);
    }

    TEST_F(adapter_LedConverter, fromUsbLeds_GivenComposeOn_ReturnsComposeOn)
    {
        EXPECT_EQ(sut.fromUsbLeds(usbCompose), compose);
    }

    TEST_F(adapter_LedConverter, fromUsbLeds_GivenPattern_ReturnsComposite)
    {
        uint8_t usbPattern = 0b1011;
        uint8_t sunPattern = 0b1011;
        EXPECT_EQ(sut.fromUsbLeds(usbPattern), adapter::LedConfiguration{sunPattern});
        
        usbPattern = 0b1001;
        sunPattern = 0b0011;
        EXPECT_EQ(sut.fromUsbLeds(usbPattern), adapter::LedConfiguration{sunPattern});
    }
} // namespace adapter_tests
