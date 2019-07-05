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

#include <arduino-platform.h>

namespace program
{
    static void write(hardware::ISerialPort *serialPort,
                      String logLevel,
                      String message);

    Log::Log(hardware::ISerialPort *serialPort) : serialPort{serialPort}
    {
    }

    void Log::info(String message)
    {
        write(serialPort, (String) "INFO: ", message);
    }

    void Log::error(String message)
    {
        write(serialPort, (String) "ERROR: ", message);
    }

    static void write(hardware::ISerialPort *serialPort,
                      String logLevel,
                      String message)
    {
        serialPort->print(logLevel);
        serialPort->println(message);
    }
} // namespace program
