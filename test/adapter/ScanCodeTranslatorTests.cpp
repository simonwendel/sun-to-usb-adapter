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
#include "../mocks/adapter/MockIScanCodeTranslationMap.h"

#include <arduino-platform.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace adapter_tests
{
    using namespace testing;

    class adapter_ScanCodeTranslator : public Test
    {
    public:
        int makeCodeA = 77;
        int breakCodeA = 205;
        int usageIdA = 4;

        adapter_mocks::MockIScanCodeTranslationMap translationMap;
        adapter::ScanCodeTranslator sut{&translationMap};

        adapter_ScanCodeTranslator()
        {
            ON_CALL(translationMap, getUsageId(makeCodeA))
            .WillByDefault(Return(usageIdA));

            ON_CALL(translationMap, contains(makeCodeA))
            .WillByDefault(Return(true));
        }
    };

    TEST_F(adapter_ScanCodeTranslator,
           translate_GivenNoMappingExists_ReturnsInvalidTranslation)
    {
        ON_CALL(translationMap, contains(makeCodeA))
        .WillByDefault(Return(false));
        auto translation = sut.translate(makeCodeA);
        EXPECT_FALSE(translation.isValid());
    }

    TEST_F(adapter_ScanCodeTranslator,
           translate_GivenMappingExists_ReturnsValidTranslation)
    {
        auto translation = sut.translate(makeCodeA);
        EXPECT_TRUE(translation.isValid());
    }

    TEST_F(adapter_ScanCodeTranslator, translate_GivenMakeCode_LooksUpMakeCode)
    {
        EXPECT_CALL(translationMap, getUsageId(makeCodeA)).Times(Exactly(1));
        auto translation = sut.translate(makeCodeA);
        EXPECT_EQ(translation.getHidCode().getUsageId(), usageIdA);
    }

    TEST_F(adapter_ScanCodeTranslator, translate_GivenBreakCode_LooksUpCorrespondingMakeCode)
    {
        EXPECT_CALL(translationMap, getUsageId(makeCodeA)).Times(Exactly(1));
        auto translation = sut.translate(makeCodeA);
        EXPECT_EQ(translation.getHidCode().getUsageId(), usageIdA);
    }

    TEST_F(adapter_ScanCodeTranslator,
           translate_GivenMakeCode_SetsBreakCodeFlagToFalse)
    {
        EXPECT_FALSE(sut.translate(makeCodeA).getHidCode().isBreakCode());
    }

    TEST_F(adapter_ScanCodeTranslator,
           translate_GivenBreakCode_SetsBreakCodeFlagToTrue)
    {
        EXPECT_TRUE(sut.translate(breakCodeA).getHidCode().isBreakCode());
    }
} // namespace adapter_tests
