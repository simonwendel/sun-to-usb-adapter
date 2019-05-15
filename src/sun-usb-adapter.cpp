/*
 * MIT License
 *
 * Copyright (c) 2017 Ben Rockwood
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ***
 *
 * USB Adapter for Sun Type 5 Keyboard
 * Ben Rockwood <benr@cuddletech.com> 1/1/17
 * Sven Guenther <sven.guenther@gmail.com> 02/10/18
 *  -  Changes to use the sun keyboard at macos with support for the special
 * keys
 */

#include "board_config.h"
#include "sun_keyboard_map.h"

#include <Arduino.h>
#include <HID-Project.h>
#include <SoftwareSerial.h>

void outputKey(int key);

// Software serial for Sun KBD
SoftwareSerial sunSerial(default_config.serial_rx,
                         default_config.serial_tx,
                         true);

boolean NUM_LOCK_ON = false;  // led bitfield xxx1 (1)
boolean CAPS_LOCK_ON = false; // led bitfield 1xxx (8)

byte led_cmd[2] = {
0x0E, 0x01}; // Used for sending the 2 byte commands to the keyboard

void setup()
{
    Serial.begin(
    default_config.serial_rate); // Normal serial for Serial Monitor Debugging
    sunSerial.begin(
    default_config.serial_rate); // Serial Connection to Sun Keyboard

    led_cmd[1] = 0x0;
    sunSerial.write(led_cmd, 2); // Enable Number Lock by Default

    Keyboard.begin(); // Initialize USB Keyboard Interface
    Consumer.begin();

    led_cmd[1] = 0x01;
    sunSerial.write(led_cmd, 2); // Enable Number Lock by Default
}

void loop()
{
    char c = sunSerial.read();

    if ((unsigned int)c != 0xFFFFFFFF)
    {
        switch (c)
        {
            case 45:
                Consumer.write(MEDIA_VOL_MUTE);
                break;
            case 2:
                Consumer.write(MEDIA_VOL_DOWN);
                break;
            case 4:
                Consumer.write(MEDIA_VOL_UP);
                break;

            case 3: // Again
                Keyboard.press(KEY_LEFT_WINDOWS);
                Keyboard.write('Z');
                Keyboard.release(KEY_LEFT_WINDOWS);
                break;

            case 25: // Preferences
                Keyboard.press(KEY_LEFT_WINDOWS);
                Keyboard.write(',');
                Keyboard.release(KEY_LEFT_WINDOWS);
                break;

            case 26:
                Keyboard.press(KEY_LEFT_WINDOWS);
                Keyboard.write('z');
                Keyboard.release(KEY_LEFT_WINDOWS);
                break;

            case 51: // Copy
                Keyboard.press(KEY_LEFT_WINDOWS);
                Keyboard.write('c');
                Keyboard.release(KEY_LEFT_WINDOWS);
                break;

            case 97: // cut
                Keyboard.press(KEY_LEFT_WINDOWS);
                Keyboard.write('x');
                Keyboard.release(KEY_LEFT_WINDOWS);
                break;

            case 73: // paste
                Keyboard.press(KEY_LEFT_WINDOWS);
                Keyboard.write('v');
                Keyboard.release(KEY_LEFT_WINDOWS);
                break;

            case 72: // open
                Keyboard.press(KEY_LEFT_WINDOWS);
                Keyboard.write('o');
                Keyboard.release(KEY_LEFT_WINDOWS);
                break;

            case 95: // find
                Keyboard.press(KEY_LEFT_WINDOWS);
                Keyboard.write('f');
                Keyboard.release(KEY_LEFT_WINDOWS);
                break;

            case 118: // help
                Keyboard.press(KEY_LEFT_WINDOWS);
                Keyboard.write('?');
                Keyboard.release(KEY_LEFT_WINDOWS);
                break;

            case 29:
                Keyboard.write(KEY_ESC);
                break;

            case 19:
                Keyboard.press(HID_KEYBOARD_LEFT_ALT);
                break;
            case -109:
                Keyboard.release(HID_KEYBOARD_LEFT_ALT);
                break;

            case 96:
                Keyboard.press(HID_KEYBOARD_PAGE_UP);
                break;
            case -32:
                Keyboard.release(HID_KEYBOARD_PAGE_UP);
                break;

            case 123:
                Keyboard.press(HID_KEYBOARD_PAGE_DOWN);
                break;
            case -5:
                Keyboard.release(HID_KEYBOARD_PAGE_DOWN);
                break;

            case 52:
                Keyboard.press(KEY_HOME);
                break;
            case -76:
                Keyboard.release(KEY_HOME);
                break;

            case 74:
                Keyboard.press(KEY_END);
                break;
            case -54:
                Keyboard.release(KEY_END);
                break;

            case 76:
                Keyboard.press(HID_KEYBOARD_LEFT_CONTROL);
                break;
            case -52:
                Keyboard.release(HID_KEYBOARD_LEFT_CONTROL);
                break;

            case 89:
                Keyboard.press(KEY_RETURN);
                break;
            case -39:
                Keyboard.release(KEY_RETURN);
                break;

            case 90:
                Keyboard.press(KEY_ENTER);
                break;
            case -38:
                Keyboard.release(KEY_ENTER);
                break;

            case 44:
                Keyboard.press(KEY_INSERT);
                break;
            case -84:
                Keyboard.release(KEY_INSERT);
                break;

            case 20:
                Keyboard.press(KEY_UP);
                break; // Up
            case -108:
                Keyboard.release(KEY_UP);
                break;

            case 24:
                Keyboard.press(KEY_LEFT);
                break; // Left
            case -104:
                Keyboard.release(KEY_LEFT);
                break;

            case 27:
                Keyboard.press(KEY_DOWN);
                break; // Down
            case -101:
                Keyboard.release(KEY_DOWN);
                break;

            case 28:
                Keyboard.press(KEY_RIGHT);
                break; // Right
            case -100:
                Keyboard.release(KEY_RIGHT);
                break;

            case 53:
                Keyboard.press(KEY_TAB);
                break;
            case -75:
                Keyboard.release(KEY_TAB);
                break;

            case 43:
                Keyboard.press(KEY_BACKSPACE);
                break; // Backspace
            case -85:
                Keyboard.release(KEY_BACKSPACE);
                break;

            case 66:
                Keyboard.press(KEY_DELETE);
                break; // Delete
            case -62:
                Keyboard.release(KEY_DELETE);
                break;

            case 99:
                Keyboard.press(KEY_LEFT_SHIFT);
                break;
            case -29:
                Keyboard.release(KEY_LEFT_SHIFT);
                break;

            case 110:
                Keyboard.press(KEY_RIGHT_SHIFT);
                break;
            case -18:
                Keyboard.release(KEY_RIGHT_SHIFT);
                break;

            case 120:
                Keyboard.press(KEY_LEFT_WINDOWS);
                break;
            case -8:
                Keyboard.release(KEY_LEFT_WINDOWS);
                break;

            case 122:
                Keyboard.press(KEY_RIGHT_WINDOWS);
                break;
            case -6:
                Keyboard.release(KEY_RIGHT_WINDOWS);
                break;

            case 98:
                if (!NUM_LOCK_ON)
                {
                    NUM_LOCK_ON = true;
                    led_cmd[1] ^= 1;
                    sunSerial.write(led_cmd, 2);
                    Keyboard.press(KEY_NUM_LOCK);
                }
                else
                {
                    NUM_LOCK_ON = false;
                    led_cmd[1] ^= 1;
                    sunSerial.write(led_cmd, 2);
                    Keyboard.press(KEY_NUM_LOCK);
                    Keyboard.release(KEY_NUM_LOCK);
                }
                break;

            case 119:
                Keyboard.press(HID_KEYBOARD_LEFT_CONTROL);
                break;
            case -9:
                Keyboard.release(HID_KEYBOARD_LEFT_CONTROL);
                break;

            case 42:
                Keyboard.press(KEY_TILDE);
                break;
            case -86:
                Keyboard.release(KEY_TILDE);
                break;

                // case 119: if (!CAPS_LOCK_ON) {
                //               CAPS_LOCK_ON = true;
                //               led_cmd[1] += 8;
                //               sunSerial.write(led_cmd, 2);
                //               Keyboard.press(KEY_CAPS_LOCK);
                //           } else {
                //               CAPS_LOCK_ON = false;
                //               led_cmd[1] -= 8;
                //               sunSerial.write(led_cmd, 2);
                //               Keyboard.press(KEY_CAPS_LOCK);
                //               Keyboard.release(KEY_CAPS_LOCK);
                //           }
                //           break;

            case 5:
                Keyboard.write(KEY_F1);
                break;
            case 6:
                Keyboard.write(KEY_F2);
                break;
            case 8:
                Keyboard.write(KEY_F3);
                break;
            case 10:
                Keyboard.write(KEY_F4);
                break;
            case 12:
                Keyboard.write(KEY_F5);
                break;
            case 14:
                Keyboard.write(KEY_F6);
                break;
            case 16:
                Keyboard.write(KEY_F7);
                break;
            case 17:
                Keyboard.write(KEY_F8);
                break;
            case 18:
                Keyboard.write(KEY_F9);
                break;
            case 7:
                Keyboard.write(KEY_F10);
                break;
            case 9:
                Keyboard.write(KEY_F11);
                break;
            case 11:
                Keyboard.write(KEY_F12);
                break;

            default:
                outputKey(c);
                break; // All other Keys
        }
    }
}

void outputKey(int key)
{
    if (key < 0)
    {
        key += 128;
        Serial.print("Key Up: ");
        Serial.println(sun_to_ascii[key]);
        Keyboard.release(sun_to_ascii[key]);
    }
    else if (key == 127)
    {
        Serial.println("All Keys Released");
        Keyboard.releaseAll();
    }
    else
    {
        Serial.print("Key Down: ");
        Serial.println(sun_to_ascii[key]);
        Keyboard.press(sun_to_ascii[key]);
    }
}
