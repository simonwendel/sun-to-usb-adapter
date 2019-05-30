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

#include "../../src/adapter/ScanCodeTranslator.h"
#include "mocks/MockIScanCodeTranslationMap.h"

#include <arduino-platform.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace adapter_tests
{
    using namespace testing;

    class adapter_ScanCodeTranslator : public ::testing::Test
    {
    public:
        int makeCodeA = 77;
        int breakCodeA = 205;
        int usageIdA = 4;

        MockIScanCodeTranslationMap translationMap;
        adapter::ScanCodeTranslator sut{&translationMap};

        adapter_ScanCodeTranslator()
        {
            ON_CALL(translationMap, getUsageId(makeCodeA))
            .WillByDefault(Return(usageIdA));
        }
    };

    TEST_F(adapter_ScanCodeTranslator, toHid_GivenMakeCode_LooksUpMakeCode)
    {
        EXPECT_CALL(translationMap, getUsageId(makeCodeA)).Times(Exactly(1));
        EXPECT_EQ(sut.toHid(makeCodeA).getUsageId(), usageIdA);
    }

    TEST_F(adapter_ScanCodeTranslator, toHid_GivenBreakCode_LooksUpMakeCode)
    {
        EXPECT_CALL(translationMap, getUsageId(makeCodeA)).Times(Exactly(1));
        EXPECT_EQ(sut.toHid(breakCodeA).getUsageId(), usageIdA);
    }

    TEST_F(adapter_ScanCodeTranslator,
           toHid_GivenMakeCode_SetsBreakCodeFlagToFalse)
    {
        EXPECT_EQ(sut.toHid(makeCodeA).isBreakCode(), false);
    }

    TEST_F(adapter_ScanCodeTranslator,
           toHid_GivenBreakCode_SetsBreakCodeFlagToTrue)
    {
        EXPECT_EQ(sut.toHid(breakCodeA).isBreakCode(), true);
    }
} // namespace adapter_tests
