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

#include "../IInterruptsControl.h"
#include "CTCModeSettings.h"
#include "CTCTimer.h"
#include "ICTCTimer.h"

#include <stdint.h>

namespace hardware::timers
{
    /*
        Because of how timer interrupts work, creating more than one instance
        of this class will not work. Much static-ness ahead!
    */
    class CTCTimer3 : public CTCTimer<uint16_t>
    {
        hardware::IInterruptsControl *interruptsControl;

    public:
        CTCTimer3(hardware::IInterruptsControl *interruptsControl);
        void setup(CTCModeSettings settings,
                   TimerFunction timerFunction) override;
        void start() override;
        void stop() override;
    };
} // namespace hardware::timers
