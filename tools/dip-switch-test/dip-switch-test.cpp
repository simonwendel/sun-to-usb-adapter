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

#include <Arduino.h>
#include <SoftwareSerial.h>

int ledPin = 13;
int switchPin = 8;
bool lightOn = false;

void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(switchPin, INPUT);
}

void loop()
{
    if (digitalRead(switchPin) == HIGH && !lightOn)
    {
        Serial.println("Turning ON the LED.");
        digitalWrite(ledPin, HIGH);
        lightOn = true;
    }
    else if (digitalRead(switchPin) == LOW && lightOn)
    {
        Serial.println("Turning OFF the LED.");
        digitalWrite(ledPin, LOW);
        lightOn = false;
    }

    delay(100);
}
