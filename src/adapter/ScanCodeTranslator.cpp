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

#include "ScanCodeTranslator.h"

#include "HidCode.h"
#include "IScanCodeTranslationMap.h"

namespace adapter
{
    ScanCodeTranslator::ScanCodeTranslator(
    IScanCodeTranslationMap *translationMap) :
        translationMap(translationMap)
    {
    }

    HidCode ScanCodeTranslator::toHid(int fromSun)
    {
        auto isBreakCode = fromSun > 128;
        if (isBreakCode)
        {
            fromSun -= 128;
        }

        auto usageId = translationMap->getUsageId(fromSun);
        return HidCode{usageId, isBreakCode};
    }
} // namespace adapter