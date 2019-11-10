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
#include "hid/HidDevice.h"
#include "hid/UsbKeyboard.h"

#include <arduino-platform.h>

const int ERROR_LED_PIN = default_config.onboard_led;
const int NUM_LOCK_ON_RESET_DIP_SWITCH = 7;
const int KEYBOARD_CLICKS_DIP_SWITCH = 8;

// logger
hardware::SerialMonitor logSerialPort;
adapter::Log logger{&logSerialPort};

// dip switch settings
hardware::PinControl pinControl;
hardware::InputPin numLockInput{&pinControl, NUM_LOCK_ON_RESET_DIP_SWITCH};
hardware::InputPin keyboardClicksInput{&pinControl, KEYBOARD_CLICKS_DIP_SWITCH};

adapter::Setting numLockSetting{&numLockInput};
adapter::Setting keyboardClicksSetting{&keyboardClicksInput};

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

// error indicator, flashing light
hardware::OutputPin flashingLedPin{&pinControl, ERROR_LED_PIN};
adapter::Toggle toggle{&flashingLedPin};

hardware::InterruptsControl interruptsControl;
hardware::timers::CTCTimer1 timer{&interruptsControl};
hardware::timers::CTCModeCalculator calculator;

adapter::FlashingLight errorIndicator{&toggle, &timer, &calculator};

// and now the final piece
adapter::Program program{&logger,
                         &keyboardClicksSetting,
                         &numLockSetting,
                         &sunKeyboard,
                         &usbKeyboard,
                         &translator,
                         &errorIndicator};

void setup()
{
    logSerialPort.begin(9600);
    program.setup();
}

void loop()
{
    program.loop();
}
