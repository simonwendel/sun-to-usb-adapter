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

/*
 * Test program to test using the HID Project library.
 * Simon Wendel <mail@simonwendel.se>
 */

#include "../../src/adapter/FlashingLight.h"
#include "../../src/adapter/ScanCodeTranslationMap.h"
#include "../../src/adapter/ScanCodeTranslator.h"
#include "../../src/adapter/SunKeyboard.h"
#include "../../src/adapter/Toggle.h"
#include "../../src/board_config.h"
#include "../../src/hardware/InterruptsControl.h"
#include "../../src/hardware/OutputPin.h"
#include "../../src/hardware/PinControl.h"
#include "../../src/hardware/SerialPort.h"
#include "../../src/hardware/timers/CTCModeCalculator.h"
#include "../../src/hardware/timers/CTCTimer1.h"

#include <HID-Project.h>
#include <arduino-platform.h>

const int LED_PIN = 13;

hardware::PinControl pinControl;

hardware::OutputPin flashingLedPin{&pinControl, LED_PIN};

hardware::InterruptsControl interruptsControl;
hardware::timers::CTCTimer1 timer{&interruptsControl};

hardware::timers::CTCModeCalculator calculator;

adapter::Toggle toggle{&flashingLedPin};

adapter::FlashingLight light{&toggle, &timer, &calculator};

hardware::SerialPort sunSerialPort{
default_config.serial_rx, default_config.serial_tx, true};

adapter::SunKeyboard sunKeyboard{&sunSerialPort};

adapter::ScanCodeTranslationMap translationMap;
adapter::ScanCodeTranslator translator{&translationMap};

void setup()
{
    Serial.begin(9600);

    Keyboard.begin();
    Keyboard.releaseAll();

    sunKeyboard.turnOffClicks();
}

void loop()
{
    auto next = sunKeyboard.read();
    if (next == 127)
    {
        light.flashOnce(2400);
        Keyboard.releaseAll();
        return;
    }

    auto translation = translator.translate(next);
    if (translation.isValid())
    {
        auto hidCode = translation.getHidCode();
        auto usageId = hidCode.getUsageId();

        if (hidCode.isBreakCode())
        {
            Keyboard.release(KeyboardKeycode(usageId));
        }
        else
        {
            Keyboard.press(KeyboardKeycode(usageId));
        }
    }
    else
    {
        Serial.println("Ooopsie, translation failed!");
    }
}
