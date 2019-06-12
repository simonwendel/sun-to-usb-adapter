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

#include "Log.h"

#include "../hardware/ISerialPort.h"
#include "IErrorIndicator.h"

#include <arduino-platform.h>

namespace program
{
    Log::Log(hardware::ISerialPort *serialPort,
             program::IErrorIndicator *errorIndicator) :
        serialPort{serialPort},
        errorIndicator{errorIndicator}
    {
    }

    void Log::error(String message)
    {
        serialPort->print((String) "ERROR: ");
        serialPort->println(message);

        if (errorIndicator->isSet() == false)
        {
            errorIndicator->set();
        }
    }
} // namespace program
