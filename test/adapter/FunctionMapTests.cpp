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

#include "../../src/adapter/Function.h"
#include "../../src/adapter/FunctionMap.h"

#include <gtest/gtest.h>

namespace adapter_tests
{
    using namespace testing;

    class adapter_FunctionMap : public ::testing::Test
    {
    public:
        int capacity = 100;
        int defaultCapacity = 255;
        adapter::FunctionMap sut;
    };

    namespace
    {
        void functionToMap(int param)
        {
        }
    } // namespace

    TEST_F(adapter_FunctionMap,
           constructor_GivenNoCapacity_AllocatesEmptyWithDefaultCapacity)
    {
        EXPECT_EQ(sut.getCount(), 0);
        EXPECT_EQ(sut.getCapacity(), defaultCapacity);
    }

    TEST_F(adapter_FunctionMap,
           constructor_GivenCapacity_AllocatesEmptyWithCapacity)
    {
        adapter::FunctionMap sut{capacity};
        EXPECT_EQ(sut.getCount(), 0);
        EXPECT_EQ(sut.getCapacity(), capacity);
    }

    TEST_F(adapter_FunctionMap,
           mapFunction_GivenKeyGreaterThanCapacity_ReturnsFalseAndDoesntAdd)
    {
        auto sucessfullyMapped =
        sut.mapFunction(defaultCapacity + 1, functionToMap);

        EXPECT_FALSE(sucessfullyMapped);
        EXPECT_EQ(sut.getCount(), 0);
    }

    TEST_F(adapter_FunctionMap,
           mapFunction_GivenKeyLessThanZero_ReturnsFalseAndDoesntAdd)
    {
        auto sucessfullyMapped = sut.mapFunction(-1, functionToMap);

        EXPECT_FALSE(sucessfullyMapped);
        EXPECT_EQ(sut.getCount(), 0);
    }

    TEST_F(adapter_FunctionMap,
           mapFunction_GivenKeyAndFunction_AddsFunctionToMap)
    {
        auto sucessfullyMapped = sut.mapFunction(10, functionToMap);

        EXPECT_TRUE(sucessfullyMapped);
        EXPECT_EQ(sut.getCount(), 1);
    }

    TEST_F(adapter_FunctionMap,
           getFunction_GivenNonExistantKey_ReturnsEmptyFunction)
    {
        auto function = sut.getFunction(1);
        EXPECT_EQ(function, nullptr);
    }

    TEST_F(adapter_FunctionMap,
           getFunction_GivenKeyLessThanZero_ReturnsEmptyFunction)
    {
        auto function = sut.getFunction(-1);
        EXPECT_EQ(function, nullptr);
    }

    TEST_F(adapter_FunctionMap,
           getFunction_GivenKeyGreaterThanCapacity_ReturnsEmptyFunction)
    {
        auto function = sut.getFunction(defaultCapacity + 1);
        EXPECT_EQ(function, nullptr);
    }

    TEST_F(adapter_FunctionMap,
           getFunction_GivenMappedKey_ReturnsMappedFunction)
    {
        sut.mapFunction(11, functionToMap);
        auto function = sut.getFunction(11);
        EXPECT_EQ(function, functionToMap);
    }
} // namespace adapter_tests
