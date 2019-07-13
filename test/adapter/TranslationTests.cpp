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

#include "../../src/adapter/Translation.h"

#include <gtest/gtest.h>

namespace adapter_tests
{
    using namespace testing;

    class adapter_Translation : public Test
    {
    public:
        adapter::HidCode defaultHidCode;
        adapter::HidCode hidCode{17, true};
    };

    TEST_F(adapter_Translation, makeInvalid_ConstructsInvalidObject)
    {
        EXPECT_FALSE(adapter::Translation::makeInvalid().isValid());
    }

    TEST_F(adapter_Translation, makeInvalid_SetsDefaultHidCodeValue)
    {
        EXPECT_EQ(adapter::Translation::makeInvalid().getHidCode(),
                  defaultHidCode);
    }

    TEST_F(adapter_Translation, makeValid_GivenHidCode_ConstructsValidObject)
    {
        EXPECT_TRUE(adapter::Translation::makeValid(hidCode).isValid());
    }

    TEST_F(adapter_Translation, makeValid_GivenHidCode_SetsHidCodeValue)
    {
        EXPECT_EQ(adapter::Translation::makeValid(hidCode).getHidCode(),
                  hidCode);
    }
} // namespace adapter_tests
