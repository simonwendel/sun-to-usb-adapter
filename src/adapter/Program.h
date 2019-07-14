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

#pragma once

#include "../hardware/ISerialPort.h"
#include "IFlashingLight.h"
#include "ISunKeyboard.h"
#include "ILog.h"
#include "IScanCodeTranslator.h"
#include "ISetting.h"

namespace adapter
{
    class Program
    {
        ILog *log;

        ISetting *keyboardClicksSetting;
        ISetting *numLockSetting;
        ISunKeyboard *sunKeyboard;
        hardware::ISerialPort *serialPort;
        IScanCodeTranslator *translator;
        IFlashingLight *errorIndicator;
        bool started;

    public:
        Program(ILog *log,
                ISetting *keyboardClicksSetting,
                ISetting *numLockSetting,
                ISunKeyboard *sunKeyboard,
                hardware::ISerialPort *serialPort,
                IScanCodeTranslator *translator,
                IFlashingLight *errorIndicator);

        void setup();
        void loop();
    };
} // namespace adapter
