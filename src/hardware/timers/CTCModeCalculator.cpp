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

#include "CTCModeCalculator.h"

#include "CTCModeSettings.h"

#include <math.h>

namespace hardware::timers
{
    CalculationResult CTCModeCalculator::createSettings(float frequencyHz)
    {
        auto actualMaxFrequency = CpuFrequencyMhz * 1e6;
        auto registerLimit = pow(2, TimerBits);

        auto currentRegister = registerLimit;

        Prescaler currentPrescaler;
        
        int index = 0;
        do
        {
            currentPrescaler = Prescalers[index];
            auto scalerFactor = (int)currentPrescaler;
            currentRegister =
            actualMaxFrequency / (scalerFactor * frequencyHz) - 1;

            if (currentRegister < registerLimit)
            {
                break;
            }
        } while (index++ < numberOfPrescalers);

        auto valid = currentRegister < registerLimit && currentRegister >= 0;
        return {valid, CTCModeSettings(currentRegister, currentPrescaler)};
    }
} // namespace hardware::timers
