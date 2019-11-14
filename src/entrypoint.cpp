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

#include "adapter/FlashingLight.h"
#include "adapter/LedChecker.h"
#include "adapter/LedConverter.h"
#include "adapter/Log.h"
#include "adapter/Program.h"
#include "adapter/ScanCodeTranslationMap.h"
#include "adapter/ScanCodeTranslator.h"
#include "adapter/Setting.h"
#include "adapter/SunKeyboard.h"
#include "adapter/Toggle.h"
#include "board_config.h"
#include "hardware/InputPin.h"
#include "hardware/InterruptsControl.h"
#include "hardware/OutputPin.h"
#include "hardware/PinControl.h"
#include "hardware/SerialMonitor.h"
#include "hardware/SerialPort.h"
#include "hardware/timers/CTCModeCalculator.h"
#include "hardware/timers/CTCTimer1.h"
#include "hardware/timers/CTCTimer3.h"
#include "hid/HidDevice.h"
#include "hid/UsbKeyboard.h"

#include <arduino-platform.h>

const int ERROR_LED_PIN = default_config.onboard_led;
const int CHECK_LEDS_DIP_SWITCH = 7;
const int KEYBOARD_CLICKS_DIP_SWITCH = 8;

// logger
hardware::SerialMonitor logSerialPort;
adapter::Log logger{&logSerialPort};

// dip switch settings
hardware::PinControl pinControl;

hardware::InputPin keyboardClicksInput{&pinControl, KEYBOARD_CLICKS_DIP_SWITCH};
hardware::InputPin checkLedsInput{&pinControl, CHECK_LEDS_DIP_SWITCH};

adapter::Setting keyboardClicksSetting{&keyboardClicksInput};
adapter::Setting checkLedsSetting{&checkLedsInput};

// actual Sun hardware
hardware::SerialPort sunSerial{
default_config.serial_rx, default_config.serial_tx, true};
adapter::SunKeyboard sunKeyboard{&sunSerial};

// usb keyboard
hid::HidDevice hidDevice;
hid::UsbKeyboard usbKeyboard{&hidDevice};

// translator
adapter::ScanCodeTranslationMap translationMap;
adapter::ScanCodeTranslator translator{&translationMap};

// timer setup
hardware::timers::CTCModeCalculator calculator;
hardware::InterruptsControl interruptsControl;

// error indicator, flashing light
hardware::OutputPin flashingLedPin{&pinControl, ERROR_LED_PIN};
adapter::Toggle toggle{&flashingLedPin};
hardware::timers::CTCTimer1 timer{&interruptsControl};
adapter::FlashingLight errorIndicator{&toggle, &timer, &calculator};

// led checking to sync with Sun keyboard
hardware::timers::CTCTimer3 ledTimer{&interruptsControl};
adapter::LedConverter ledConverter;
adapter::LedChecker ledChecker{
&ledTimer, &calculator, &usbKeyboard, &sunKeyboard, &ledConverter};

// and now the final piece
adapter::Program program{&logger,
                         &keyboardClicksSetting,
                         &checkLedsSetting,
                         &sunKeyboard,
                         &usbKeyboard,
                         &translator,
                         &errorIndicator,
                         &ledChecker};

void setup()
{
    logSerialPort.begin(9600);
    program.setup();
}

void loop()
{
    program.loop();
}
