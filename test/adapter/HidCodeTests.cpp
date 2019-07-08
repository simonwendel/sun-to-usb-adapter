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

#include <gtest/gtest.h>

namespace adapter_tests
{
    using namespace testing;

    class adapter_HidCode : public TestWithParam<bool>
    {
    public:
        int expectedUsageId = 13;
        bool expectedBreakFlag = GetParam();
    };

    TEST_P(adapter_HidCode, constructor_GivenUsageCode_SetsUsageCode)
    {
        adapter::HidCode sut{expectedUsageId, expectedBreakFlag};
        EXPECT_EQ(sut.getUsageId(), expectedUsageId);
    }

    TEST_P(adapter_HidCode, constructor_GivenBreakCodeFlag_SetsBreakCodeFlag)
    {
        adapter::HidCode sut{expectedUsageId, expectedBreakFlag};
        EXPECT_EQ(sut.isBreakCode(), expectedBreakFlag);
    }

    INSTANTIATE_TEST_CASE_P(adapter_HidCode_params, adapter_HidCode, Bool());
} // namespace adapter_tests
