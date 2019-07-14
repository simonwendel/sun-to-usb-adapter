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

#include "SunKeyboard.h"

#include "../hardware/ISerialPort.h"
#include "Command.h"
#include "LedCommand.h"

namespace adapter
{
    SunKeyboard::SunKeyboard(hardware::ISerialPort *serialPort) :
        serialPort{serialPort}
    {
    }

    void SunKeyboard::turnOnClicks()
    {
        serialPort->write(Command::ENABLE_CLICK);
    }

    void SunKeyboard::turnOffClicks()
    {
        serialPort->write(Command::DISABLE_CLICK);
    }

    void SunKeyboard::turnOnBell()
    {
        serialPort->write(Command::ENABLE_BELL);
    }

    void SunKeyboard::turnOffBell()
    {
        serialPort->write(Command::DISABLE_BELL);
    }

    void SunKeyboard::setLeds(LedCommand leds)
    {
        uint8_t compoundCommand[2] = {Command::SET_LEDS, (uint8_t)leds};
        serialPort->write(compoundCommand, 2);
    }

    int SunKeyboard::read()
    {
        int next;
        do
        {
            next = serialPort->read();
        } while (next <= 0 || next >= 256);

        return next;
    }
} // namespace adapter
