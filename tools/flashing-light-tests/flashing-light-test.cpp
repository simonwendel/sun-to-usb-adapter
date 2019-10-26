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
 * Test program to test using the dip-switch for settings.
 * Simon Wendel <mail@simonwendel.se>
 */

#include "../../src/adapter/FlashingLight.h"
#include "../../src/adapter/Setting.h"
#include "../../src/adapter/Toggle.h"
#include "../../src/hardware/InputPin.h"
#include "../../src/hardware/InterruptsControl.h"
#include "../../src/hardware/OutputPin.h"
#include "../../src/hardware/PinControl.h"
#include "../../src/hardware/timers/CTCModeCalculator.h"
#include "../../src/hardware/timers/CTCTimer1.h"

#include <arduino-platform.h>

const int LED_PIN = 13;
const int SWITCH_PIN = 8;

hardware::PinControl pinControl;

hardware::OutputPin flashingLedPin{&pinControl, LED_PIN};

hardware::InputPin dipSwitchPin{&pinControl, SWITCH_PIN};
adapter::Setting dipSwitch{&dipSwitchPin};

hardware::InterruptsControl interruptsControl;
hardware::timers::CTCTimer1 timer{&interruptsControl};

hardware::timers::CTCModeCalculator calculator;

adapter::Toggle toggle{&flashingLedPin};

adapter::FlashingLight light{&toggle, &timer, &calculator};

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if (dipSwitch.isOn() && !light.isFlashing())
    {
        light.startFlashing(4);
    }

    delay(500);
}
