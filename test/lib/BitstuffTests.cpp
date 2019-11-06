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

#include <bitstuff.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdint.h>
#include <tuple>

namespace lib_tests
{
    using namespace testing;

    class lib_Bitstuff : public TestWithParam<std::tuple<int, bool>>
    {
    public:
        uint8_t number = 0b0101010;
    };

    TEST_F(lib_Bitstuff, setBit_GivenWhichBit_SetsThatBit)
    {
        setBit(number, 2);
        EXPECT_EQ(number, 0b0101110);
    }

    TEST_F(lib_Bitstuff, unsetBit_GivenWhichBit_UnsetsThatBit)
    {
        unsetBit(number, 1);
        EXPECT_EQ(number, 0b0101000);
    }

    TEST_F(lib_Bitstuff, toggleBit_GivenSetBit_UnsetsThatBit)
    {
        toggleBit(number, 1);
        EXPECT_EQ(number, 0b0101000);
    }

    TEST_F(lib_Bitstuff, toggleBit_GivenUnsetBit_SetsThatBit)
    {
        toggleBit(number, 4);
        EXPECT_EQ(number, 0b0111010);
    }

    TEST_P(lib_Bitstuff, checkBit_GivenNthBit_ReturnsTrueifOneOtherwiseFalse)
    {
        auto nthBit = std::get<0>(GetParam());
        auto expected = std::get<1>(GetParam());
        EXPECT_EQ(checkBit(number, nthBit), expected);
    }

    INSTANTIATE_TEST_CASE_P(lib_Bitstuff_params,
                            lib_Bitstuff,
                            Values(std::make_tuple(1, true),
                                   std::make_tuple(3, true),
                                   std::make_tuple(5, true),
                                   std::make_tuple(0, false),
                                   std::make_tuple(2, false),
                                   std::make_tuple(4, false),
                                   std::make_tuple(6, false),
                                   std::make_tuple(7, false)));
} // namespace lib_tests
