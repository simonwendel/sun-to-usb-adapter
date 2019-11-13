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

#include "../hardware/timers/ICTCModeCalculator.h"
#include "../hardware/timers/ICTCTimer.h"
#include "ILedChecker.h"
#include "ILedConverter.h"
#include "ISunKeyboard.h"
#include "IUsbKeyboard.h"
#include "LedConfiguration.h"

namespace adapter
{
    class LedChecker : public ILedChecker
    {
        LedConfiguration leds;
        hardware::timers::ICTCTimer *checkTimer;
        hardware::timers::ICTCModeCalculator *calculator;
        IUsbKeyboard *usbKeyboard;
        ISunKeyboard *sunKeyboard;
        ILedConverter *converter;

    public:
        LedChecker(hardware::timers::ICTCTimer *checkTimer,
                   hardware::timers::ICTCModeCalculator *calculator,
                   IUsbKeyboard *usbKeyboard,
                   ISunKeyboard *sunKeyboard,
                   ILedConverter *converter);

        void startChecking(float intervalHz) override;
        void stopChecking() override;
    };
} // namespace adapter
