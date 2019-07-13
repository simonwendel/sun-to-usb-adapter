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

#include "../../../src/adapter/ILog.h"

#include <arduino-platform.h>
#include <gmock/gmock.h>

namespace adapter_mocks
{
    class MockILog : public adapter::ILog
    {
    public:
        MOCK_METHOD1(info, void(String));
        MOCK_METHOD1(error, void(String));
    };
} // namespace adapter_mocks
