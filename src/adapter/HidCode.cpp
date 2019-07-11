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

#include "HidCode.h"

namespace adapter
{
    const int HidCode::NoEvent = 0;

    HidCode::HidCode() : HidCode(NoEvent, false)
    {
    }

    HidCode::HidCode(int usageId, bool breakCode) :
        usageId{usageId}, breakCode{breakCode}
    {
    }

    bool HidCode::isBreakCode()
    {
        return breakCode;
    }

    int HidCode::getUsageId()
    {
        return usageId;
    }

    bool HidCode::operator==(const HidCode &rhs)
    {
        return breakCode == rhs.breakCode && usageId == rhs.usageId;
    }
} // namespace adapter
