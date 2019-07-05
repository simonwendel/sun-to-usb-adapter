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

#include "../adapter/IKeyboardCommander.h"
#include "../adapter/ISetting.h"
#include "ILog.h"

namespace program
{
    class Program
    {
        ILog *log;

        adapter::ISetting *keyboardClicksSetting;
        adapter::ISetting *numLockSetting;
        adapter::IKeyboardCommander *keyboardCommander;

        bool started;

    public:
        Program(ILog *log,
                adapter::ISetting *keyboardClicksSetting,
                adapter::ISetting *numLockSetting,
                adapter::IKeyboardCommander *keyboardCommander);

        void setup();
        void loop();
    };
} // namespace program
