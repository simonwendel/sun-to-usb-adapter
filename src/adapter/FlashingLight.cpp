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

#include "FlashingLight.h"

#include "../hardware/timers/CTCModeCalculator.h"
#include "../hardware/timers/ICTCTimer.h"

namespace adapter
{
    FlashingLight::FlashingLight(
    IToggle *toggle,
    hardware::timers::ICTCTimer *blinkTimer,
    hardware::timers::ICTCModeCalculator *calculator) :
        toggle{toggle},
        blinkTimer{blinkTimer}, calculator{calculator}
    {
    }

    // magic needed since capturing lambdas are not compatible with what we
    // need from TimerFunction
    namespace
    {
        IToggle *toggleCapture;
        void onTimer()
        {
            toggleCapture->toggle();
        }
    } // namespace

    bool FlashingLight::isFlashing()
    {
        return timerStarted;
    }

    void FlashingLight::startFlashing(float frequencyHz)
    {
        if (timerStarted == false)
        {
            auto results = calculator->createSettings(frequencyHz);

            toggleCapture = this->toggle;
            blinkTimer->setup(results.value, onTimer);

            blinkTimer->start();
            timerStarted = true;
        }
    }

    void FlashingLight::stopFlashing()
    {
        if (timerStarted)
        {
            blinkTimer->stop();
            toggle->reset();
            timerStarted = false;
        }
    }
} // namespace adapter
