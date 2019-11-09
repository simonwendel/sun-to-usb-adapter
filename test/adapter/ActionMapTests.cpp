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

#include "../../src/adapter/Action.h"
#include "../../src/adapter/ActionMap.h"

#include <gtest/gtest.h>

namespace adapter_tests
{
    using namespace testing;

    class adapter_ActionMap : public Test
    {
    public:
        int capacity = 100;
        int defaultCapacity = 255;
        adapter::ActionMap<int> sut;
    };

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

    namespace
    {
        void actionToMap(int param)
        {
        }
    } // namespace

#pragma GCC diagnostic pop

    TEST_F(adapter_ActionMap,
           constructor_GivenNoCapacity_AllocatesEmptyWithDefaultCapacity)
    {
        EXPECT_EQ(sut.getCount(), 0);
        EXPECT_EQ(sut.getCapacity(), defaultCapacity);
    }

    TEST_F(adapter_ActionMap,
           constructor_GivenCapacity_AllocatesEmptyWithCapacity)
    {
        adapter::ActionMap<int> sut{capacity};
        EXPECT_EQ(sut.getCount(), 0);
        EXPECT_EQ(sut.getCapacity(), capacity);
    }

    TEST_F(adapter_ActionMap,
           mapAction_GivenKeyGreaterThanCapacity_ReturnsFalseAndDoesntAdd)
    {
        auto sucessfullyMapped =
        sut.mapAction(defaultCapacity + 1, actionToMap);

        EXPECT_FALSE(sucessfullyMapped);
        EXPECT_EQ(sut.getCount(), 0);
    }

    TEST_F(adapter_ActionMap,
           mapAction_GivenKeyLessThanZero_ReturnsFalseAndDoesntAdd)
    {
        auto sucessfullyMapped = sut.mapAction(-1, actionToMap);

        EXPECT_FALSE(sucessfullyMapped);
        EXPECT_EQ(sut.getCount(), 0);
    }

    TEST_F(adapter_ActionMap, mapAction_GivenKeyAndAction_AddsActionToMap)
    {
        auto sucessfullyMapped = sut.mapAction(10, actionToMap);

        EXPECT_TRUE(sucessfullyMapped);
        EXPECT_EQ(sut.getCount(), 1);
    }

    TEST_F(adapter_ActionMap, getAction_GivenNonMappedKey_ReturnsNullptr)
    {
        auto action = sut.getAction(1);
        EXPECT_EQ(action, nullptr);
    }
    
    TEST_F(adapter_ActionMap, getAction_GivenKeyLessThanZero_ReturnsNullptr)
    {
        auto action = sut.getAction(-1);
        EXPECT_EQ(action, nullptr);
    }

    TEST_F(adapter_ActionMap,
           getAction_GivenKeyGreaterThanCapacity_ReturnsNullptr)
    {
        auto action = sut.getAction(defaultCapacity + 1);
        EXPECT_EQ(action, nullptr);
    }

    TEST_F(adapter_ActionMap, getAction_GivenMappedKey_ReturnsMappedAction)
    {
        sut.mapAction(11, actionToMap);
        auto action = sut.getAction(11);
        EXPECT_EQ(action, actionToMap);
    }

    TEST_F(adapter_ActionMap, hasMapping_GivenNonMappedKey_ReturnsFalse)
    {
        EXPECT_FALSE(sut.hasMapping(11));
    }

    TEST_F(adapter_ActionMap, hasMapping_GivenNegativeKey_ReturnsFalse)
    {
        EXPECT_FALSE(sut.hasMapping(-1));
    }

    TEST_F(adapter_ActionMap,
           hasMapping_GivenKeyGreaterThanCapacity_ReturnsFalse)
    {
        EXPECT_FALSE(sut.hasMapping(defaultCapacity + 1));
    }

    TEST_F(adapter_ActionMap, hasMapping_GivenMappedKey_ReturnsTrue)
    {
        sut.mapAction(11, actionToMap);
        EXPECT_TRUE(sut.hasMapping(11));
    }
} // namespace adapter_tests
