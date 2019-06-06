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

#include "../../src/hardware/Register.h"

#include <gtest/gtest.h>
#include <stdint.h>

namespace hardware_tests
{
    using namespace testing;

    class hardware_Register : public ::testing::Test
    {
    public:
        uint16_t backingRegister = 0b1000000110100001;
        hardware::Register<uint16_t> sut{&backingRegister};
    };

    TEST_F(hardware_Register,
           constructor_GivenRegiser_RetainsInitialValue)
    {
        auto initialValue = 33185;
        EXPECT_EQ(backingRegister, initialValue);
    }

    TEST_F(hardware_Register,
           readRegister_WhenNoOperationsPerformed_ReadsInitialValue)
    {
        auto initialValue = 33185;
        EXPECT_EQ(sut.readRegister(), initialValue);
    }

    TEST_F(hardware_Register,
           clearRegister_GivenRegister_ZerosOutRegister)
    {
        auto cleared = 0;

        sut.clearRegister();

        EXPECT_EQ(sut.readRegister(), cleared);
        EXPECT_EQ(backingRegister, cleared);
    }

    TEST_F(hardware_Register,
           turnOnBits_GivenValue_TurnsOnBitsInRegister)
    {
        auto bits = 0b0010101010101010;
        auto expected = 0b1010101110101011;

        sut.turnOnBits(bits);

        EXPECT_EQ(sut.readRegister(), expected);
        EXPECT_EQ(backingRegister, expected);
    }

    TEST_F(hardware_Register,
           setRegister_GivenValue_SetsWholeRegister)
    {
        auto value = 16573;
        auto expected = 16573;

        sut.setRegister(value);

        EXPECT_EQ(sut.readRegister(), expected);
        EXPECT_EQ(backingRegister, expected);
    }
} // namespace hardware_registers_tests
