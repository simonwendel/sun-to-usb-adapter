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

#include "../../board_config.h"
#include "CTCModeSettings.h"
#include "ICTCModeCalculator.h"
#include "Prescaler.h"

namespace hardware::timers
{
    class CTCModeCalculator : public ICTCModeCalculator
    {
    private:
        const int numberOfPrescalers = 5;

    public:
        const int CpuFrequencyMhz = default_config.cpu_frequency_mhz;
        const int TimerBits = 16;
        const Prescaler Prescalers[5] = {Prescaler::PS_1,
                                         Prescaler::PS_8,
                                         Prescaler::PS_64,
                                         Prescaler::PS_256,
                                         Prescaler::PS_1024};

        CalculationResult createSettings(float frequencyHz) override;
    };
} // namespace hardware::timers
