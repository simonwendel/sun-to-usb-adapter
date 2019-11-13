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

#pragma once

#include "../../../src/adapter/ILedConverter.h"
#include "../../../src/adapter/LedConfiguration.h"

#include <gmock/gmock.h>

namespace adapter_mocks
{
    class MockILedConverter : public adapter::ILedConverter
    {
    public:
        MOCK_METHOD1(fromUsbLeds, adapter::LedConfiguration(uint8_t));
    };
} // namespace adapter_mocks
