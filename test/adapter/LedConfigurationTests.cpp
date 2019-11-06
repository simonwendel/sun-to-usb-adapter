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
#include "../../src/adapter/LedConfiguration.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace adapter_tests
{
    using namespace testing;

    class adapter_LedConfiguration : public Test
    {
    public:
        adapter::LedConfiguration sutInitiallyZeros;
        adapter::LedConfiguration sutInitiallyOnes{0b11111111};
    };

    TEST_F(adapter_LedConfiguration,
           constructor_GivenNoInitialPayload_SetsEmptyPayload)
    {
        EXPECT_EQ(sutInitiallyZeros, 0);
    }

    TEST_F(adapter_LedConfiguration,
           constructor_GivenInitialPayload_SetsPayload)
    {
        adapter::LedConfiguration sutSomeNumber{0b10101010};
        EXPECT_EQ(sutSomeNumber, 170);
        EXPECT_EQ(sutInitiallyOnes, 255);
    }

    TEST_F(adapter_LedConfiguration, setNumLock_SetsBitZero)
    {
        sutInitiallyZeros.setNumLock();
        EXPECT_EQ(sutInitiallyZeros, 0b00000001);
    }

    TEST_F(adapter_LedConfiguration, setNumLock_UnsetsBitZero)
    {
        sutInitiallyOnes.unsetNumLock();
        EXPECT_EQ(sutInitiallyOnes, 0b11111110);
    }

    TEST_F(adapter_LedConfiguration, toggleNumLock_TogglesBitZero)
    {
        sutInitiallyOnes.toggleNumLock();
        EXPECT_EQ(sutInitiallyOnes, 0b11111110);
        
        sutInitiallyZeros.toggleNumLock();
        EXPECT_EQ(sutInitiallyZeros, 0b00000001);
    }

    TEST_F(adapter_LedConfiguration, setCompose_SetsBitOne)
    {
        sutInitiallyZeros.setCompose();
        EXPECT_EQ(sutInitiallyZeros, 0b00000010);
    }

    TEST_F(adapter_LedConfiguration, unsetCompose_UnsetsBitOne)
    {
        sutInitiallyOnes.unsetCompose();
        EXPECT_EQ(sutInitiallyOnes, 0b11111101);
    }

    TEST_F(adapter_LedConfiguration, toggleCompose_TogglesBitOne)
    {
        sutInitiallyOnes.toggleCompose();
        EXPECT_EQ(sutInitiallyOnes, 0b11111101);
        
        sutInitiallyZeros.toggleCompose();
        EXPECT_EQ(sutInitiallyZeros, 0b00000010);
    }

    TEST_F(adapter_LedConfiguration, setScrollLock_SetsBitTwo)
    {
        sutInitiallyZeros.setScrollLock();
        EXPECT_EQ(sutInitiallyZeros, 0b00000100);
    }

    TEST_F(adapter_LedConfiguration, unsetScrollLock_UnsetsBitTwo)
    {
        sutInitiallyOnes.unsetScrollLock();
        EXPECT_EQ(sutInitiallyOnes, 0b11111011);
    }

    TEST_F(adapter_LedConfiguration, toggleScrollLock_TogglesBitTwo)
    {
        sutInitiallyOnes.toggleScrollLock();
        EXPECT_EQ(sutInitiallyOnes, 0b11111011);
        
        sutInitiallyZeros.toggleScrollLock();
        EXPECT_EQ(sutInitiallyZeros, 0b00000100);
    }

    TEST_F(adapter_LedConfiguration, setCapsLock_SetsBitThree)
    {
        sutInitiallyZeros.setCapsLock();
        EXPECT_EQ(sutInitiallyZeros, 0b00001000);
    }

    TEST_F(adapter_LedConfiguration, unsetCapsLock_unsetsBitThree)
    {
        sutInitiallyOnes.unsetCapsLock();
        EXPECT_EQ(sutInitiallyOnes, 0b11110111);
    }

    TEST_F(adapter_LedConfiguration, toggleCapsLock_TogglesBitThree)
    {
        sutInitiallyOnes.toggleCapsLock();
        EXPECT_EQ(sutInitiallyOnes, 0b11110111);
        
        sutInitiallyZeros.toggleCapsLock();
        EXPECT_EQ(sutInitiallyZeros, 0b00001000);
    }
} // namespace adapter_tests
