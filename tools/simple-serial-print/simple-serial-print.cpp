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
 * Test program to output stuff from the sun_to_ascii map.
 * Simon Wendel <mail@simonwendel.se>
 */

#include "board_config.h"
#include "sun_keyboard_map.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial sunSerial(default_config.serial_rx,
                         default_config.serial_tx,
                         true);

void outputKey(int key);

void setup()
{
    Serial.begin(default_config.serial_rate);
    while (!Serial)
    {
    }

    sunSerial.begin(default_config.serial_rate);
    Serial.println("w00t! debug started, now bash on some keys!");
}

void loop()
{
    int key = sunSerial.read();

    // Filter noise
    if (key != 0 && key != (int)0xFFFFFFFF)
    {
        outputKey(key);
    }
}

void outputKey(int key)
{
    if (key > 127)
    {
        key -= 128;
        Serial.print("Key Up: ");
        Serial.println((char)sun_to_ascii[key]);
    }
    else if (key == 127)
    {
        Serial.println("All Keys Released");
        Serial.println();
    }
    else
    {
        Serial.print("Key Down: ");
        Serial.println((char)sun_to_ascii[key]);
    }
}
