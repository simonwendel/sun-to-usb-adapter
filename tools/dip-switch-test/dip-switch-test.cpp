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
#include "../../src/hardware/OutputPin.h"
#include "../../src/hardware/PinControl.h"

#include <arduino-platform.h>

int ledPin = 13;
int switchPin = 8;
bool lightOn = false;

hardware::PinControl pinControl;
hardware::InputPin input{&pinControl, switchPin};
hardware::OutputPin output{&pinControl, ledPin};
adapter::Setting dipSwitch{&input};

void setup()
{
}

void loop()
{
    if(dipSwitch.isOn() && !lightOn)
    {
        output.setState(HIGH);
        lightOn = true;
    }
    else if (!dipSwitch.isOn() && lightOn)
    {
        output.setState(LOW);
        lightOn = false;
    }
    
    delay(100);
}
