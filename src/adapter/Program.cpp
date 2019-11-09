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

#include "Program.h"

#include "../adapter/LedConfiguration.h"

namespace adapter
{
    Program::Program(ILog *log,
                     ISetting *keyboardClicksSetting,
                     ISetting *numLockSetting,
                     ISunKeyboard *sunKeyboard,
                     IUsbKeyboard *usbKeyboard,
                     IScanCodeTranslator *translator,
                     IFlashingLight *errorIndicator) :
        log{log},
        keyboardClicksSetting{keyboardClicksSetting},
        numLockSetting{numLockSetting}, sunKeyboard{sunKeyboard},
        usbKeyboard{usbKeyboard}, translator{translator},
        errorIndicator{errorIndicator}, started{false}
    {
    }

    void Program::setup()
    {
        if (keyboardClicksSetting->isOn())
        {
            sunKeyboard->turnOnClicks();
        }

        if (numLockSetting->isOn())
        {
            leds.setNumLock();
            sunKeyboard->setLeds(leds);
        }

        log->info("Setup completed.");
    }

    // here's all the meaty bits!
    void Program::loop()
    {
        if (!started)
        {
            log->info("Adapter started.");
            started = true;
        }

        auto next = sunKeyboard->read();
        auto translation = translator->translate(next);

        if (translation.isValid())
        {
            usbKeyboard->emit(translation.getHidCode());
        }
        else
        {
            if (!errorIndicator->isFlashing())
            {
                errorIndicator->startFlashing(2);
            }
        }
    }
} // namespace adapter
