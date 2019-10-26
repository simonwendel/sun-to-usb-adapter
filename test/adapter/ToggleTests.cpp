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

#include "../../src/adapter/Toggle.h"
#include "../mocks/hardware/MockIOutputPin.h"

#include <arduino-platform.h>
#include <gtest/gtest.h>

namespace adapter_tests
{
    using namespace testing;

    class adapter_Toggle : public Test
    {
    public:
        hardware_mocks::MockIOutputPin output;
        adapter::Toggle sut{&output};
    };

    TEST_F(adapter_Toggle,
           toggle_WhenCalledSequentially_TogglesOutputBetweenHighAndLow)
    {
        InSequence seq;
        EXPECT_CALL(output, setState(HIGH));
        EXPECT_CALL(output, setState(LOW));
        EXPECT_CALL(output, setState(HIGH));
        EXPECT_CALL(output, setState(LOW));
        EXPECT_CALL(output, setState(HIGH));
        EXPECT_CALL(output, setState(LOW));
        EXPECT_CALL(output, setState(HIGH));
        EXPECT_CALL(output, setState(LOW));

        sut.toggle();
        sut.toggle();
        sut.toggle();
        sut.toggle();
        sut.toggle();
        sut.toggle();
        sut.toggle();
        sut.toggle();
    }
} // namespace adapter_tests
