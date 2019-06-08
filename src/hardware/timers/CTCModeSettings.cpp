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

#include "CTCModeSettings.h"

#include "Prescaler.h"

namespace hardware::timers
{
    CTCModeSettings::CTCModeSettings(int compareMatchRegister,
                                     Prescaler prescaler) :
        compareMatchRegister{compareMatchRegister},
        prescaler{prescaler}
    {
    }

    int CTCModeSettings::getCompareMatchRegister()
    {
        return compareMatchRegister;
    }

    int CTCModeSettings::getPrescalerRegister()
    {
        /*
            |CS12|CS11|CS10|Prescaler|
            +------------------------+
            |  0 |  0 |  1 | PS_1    |
            |  0 |  1 |  0 | PS_8    |
            |  0 |  1 |  1 | PS_64   |
            |  1 |  0 |  0 | PS_256  |
            |  1 |  0 |  1 | PS_1024 |
        */

        // let's do this the simplest possible way
        switch (prescaler)
        {
            case Prescaler::PS_1:
                return 1;

            case Prescaler::PS_8:
                return 2;

            case Prescaler::PS_64:
                return 3;

            case Prescaler::PS_256:
                return 4;

            case Prescaler::PS_1024:
                return 5;

            default:
                // setting all to zero will effectively
                // stop the clock
                return 0;
        }
    }

    Prescaler CTCModeSettings::getPrescaler()
    {
        return prescaler;
    }
} // namespace hardware::timers
