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
 * Test program to find missing mappings in scancodes-table.txt. 
 * Generated from the document.
 * Simon Wendel <mail@simonwendel.se>
 */

#include "../../src/board_config.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

void testKey(int key);

SoftwareSerial sunSerial(default_config.serial_rx,
                         default_config.serial_tx,
                         true);

void setup()
{
    Serial.begin(default_config.serial_rate);
    while (!Serial)
    {
    }
    
    sunSerial.begin(default_config.serial_rate);
    Serial.println("debug started, now bash on all the keys!");
}

void loop()
{
    int key = sunSerial.read();

    // Filter noise
    if (isWithinValidRange(key))
    {
        checkIfKnown(key);
    }
}

bool isWithinValidRange(int key)
{
    return key != 0 && key != (int)0xFFFFFFFF;
}

void checkIfKnown(int key)
{
    if (key >= 127)
    {
        // only key up or clear-all are above 127
        return;
    }

    switch (key)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 14:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 68:
        case 69:
        case 70:
        case 71:
        case 72:
        case 73:
        case 74:
        case 76:
        case 77:
        case 78:
        case 79:
        case 80:
        case 81:
        case 82:
        case 83:
        case 84:
        case 85:
        case 86:
        case 87:
        case 88:
        case 89:
        case 90:
        case 91:
        case 92:
        case 93:
        case 94:
        case 95:
        case 96:
        case 97:
        case 98:
        case 99:
        case 100:
        case 101:
        case 102:
        case 103:
        case 104:
        case 105:
        case 106:
        case 107:
        case 108:
        case 109:
        case 110:
        case 112:
        case 113:
        case 114:
        case 118:
        case 119:
        case 120:
        case 121:
        case 122:
        case 123:
        case 125:
            Serial.println("Known!");
            return;
            break;
    }

    Serial.print("Unknown sun key code: ");
    Serial.println(key);
}
