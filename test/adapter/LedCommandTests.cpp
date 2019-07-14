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

#include "../../src/adapter/SunKeyboard.h"
#include "../../src/adapter/LedCommand.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace adapter_tests
{
    using namespace testing;

    class adapter_LedCommand : public Test
    {
    public:
        adapter::LedCommand sutInitiallyZeros;
        adapter::LedCommand sutInitiallyOnes{0b11111111};
    };

    TEST_F(adapter_LedCommand,
           constructor_GivenNoInitialPayload_SetsEmptyPayload)
    {
        EXPECT_EQ(sutInitiallyZeros, 0);
    }

    TEST_F(adapter_LedCommand,
           constructor_GivenInitialPayload_SetsPayload)
    {
        adapter::LedCommand sutSomeNumber{0b10101010};
        EXPECT_EQ(sutSomeNumber, 170);
        EXPECT_EQ(sutInitiallyOnes, 255);
    }

    TEST_F(adapter_LedCommand, setNumLock_SetsBitZero)
    {
        sutInitiallyZeros.setNumLock();
        EXPECT_EQ(sutInitiallyZeros, 0b00000001);
    }

    TEST_F(adapter_LedCommand, setNumLock_UnsetsBitZero)
    {
        sutInitiallyOnes.unsetNumLock();
        EXPECT_EQ(sutInitiallyOnes, 0b11111110);
    }

    TEST_F(adapter_LedCommand, setCompose_SetsBitOne)
    {
        sutInitiallyZeros.setCompose();
        EXPECT_EQ(sutInitiallyZeros, 0b00000010);
    }

    TEST_F(adapter_LedCommand, unsetCompose_UnsetsBitOne)
    {
        sutInitiallyOnes.unsetCompose();
        EXPECT_EQ(sutInitiallyOnes, 0b11111101);
    }

    TEST_F(adapter_LedCommand, setScrollLock_SetsBitTwo)
    {
        sutInitiallyZeros.setScrollLock();
        EXPECT_EQ(sutInitiallyZeros, 0b00000100);
    }

    TEST_F(adapter_LedCommand, unsetScrollLock_UnsetsBitTwo)
    {
        sutInitiallyOnes.unsetScrollLock();
        EXPECT_EQ(sutInitiallyOnes, 0b11111011);
    }

    TEST_F(adapter_LedCommand, setCapsLock_SetsBitThree)
    {
        sutInitiallyZeros.setCapsLock();
        EXPECT_EQ(sutInitiallyZeros, 0b00001000);
    }

    TEST_F(adapter_LedCommand, unsetCapsLock_unsetsBitThree)
    {
        sutInitiallyOnes.unsetCapsLock();
        EXPECT_EQ(sutInitiallyOnes, 0b11110111);
    }
} // namespace adapter_tests
