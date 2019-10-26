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

#include "../../src/adapter/Setting.h"
#include "../../src/hardware/InputPin.h"
#include "../../src/hardware/PinControl.h"

#include <HID-Project.h>
#include <arduino-platform.h>

const int LED_PIN = 13;
const int SWITCH_PIN = 8;

hardware::PinControl pinControl;
hardware::InputPin dipSwitchPin{&pinControl, SWITCH_PIN};
adapter::Setting dipSwitch{&dipSwitchPin};

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if (dipSwitch.isOn())
    {
        Keyboard.press(KEY_L);
        Keyboard.release(KEY_L);

        Keyboard.press(KEY_LEFT_SHIFT);

        Keyboard.press(KEY_E);
        Keyboard.release(KEY_E);

        Keyboard.press(KEY_E);
        Keyboard.release(KEY_E);

        Keyboard.release(KEY_LEFT_SHIFT);

        Keyboard.press(KEY_T);
        Keyboard.release(KEY_T);

        Keyboard.write(KEY_ENTER);
    }

    delay(500);
}
