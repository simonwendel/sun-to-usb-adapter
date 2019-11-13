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

#include "LedChecker.h"

namespace adapter
{
    LedChecker::LedChecker(hardware::timers::ICTCTimer *checkTimer,
                           hardware::timers::ICTCModeCalculator *calculator,
                           IUsbKeyboard *usbKeyboard,
                           ISunKeyboard *sunKeyboard,
                           ILedConverter *converter) :
        checkTimer{checkTimer},
        calculator{calculator}, usbKeyboard{usbKeyboard},
        sunKeyboard{sunKeyboard}, converter{converter}
    {
    }

    // magic needed since capturing lambdas are not compatible with what we
    // need from TimerFunction
    namespace
    {
        LedConfiguration *ledsCapture;
        IUsbKeyboard *usbKeyboardCapture;
        ISunKeyboard *sunKeyboardCapture;
        ILedConverter *converterCapture;
        void onTimer()
        {
            auto usbLeds = usbKeyboardCapture->getLeds();
            auto sunLeds = converterCapture->fromUsbLeds(usbLeds);
            if (sunLeds != *ledsCapture)
            {
                sunKeyboardCapture->setLeds(sunLeds);
            }
        }
    } // namespace

    void LedChecker::startChecking(float intervalHz)
    {
        auto settings = calculator->createSettings(intervalHz);
        checkTimer->setup(settings.value, onTimer);

        ledsCapture = &leds;
        usbKeyboardCapture = usbKeyboard;
        sunKeyboardCapture = sunKeyboard;
        converterCapture = converter;

        checkTimer->start();
    }

    void LedChecker::stopChecking()
    {
        checkTimer->stop();
    }
} // namespace adapter
