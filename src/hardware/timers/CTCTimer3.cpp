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

#include "CTCTimer3.h"

#include <arduino-platform.h>

namespace hardware::timers
{
    namespace
    {
        TimerFunction timerF;
        bool started = false;
    } // namespace

    CTCTimer3::CTCTimer3(hardware::IInterruptsControl *interruptsControl) :
        CTCTimer(&TCCR3A, &TCCR3B, &TIMSK3, &TCNT3, &OCR3A)
    {
        this->interruptsControl = interruptsControl;
    }

    void CTCTimer3::setup(CTCModeSettings settings, TimerFunction timerFunction)
    {
        // because of low-level bullshit, the order here is important

        interruptsControl->disableInterrupts();

        timerF = timerFunction;

        ControlRegisterA->clearRegister();
        ControlRegisterB->clearRegister();

        CounterRegister->clearRegister();
        CompareMatchRegister->setRegister(settings.getCompareMatchRegister());

        ControlRegisterB->turnOnBits(1 << WGM32);
        ControlRegisterB->turnOnBits(settings.getPrescalerRegister());

        interruptsControl->enableInterrupts();
    }

    void CTCTimer3::start()
    {
        interruptsControl->disableInterrupts();

        InterruptMaskRegister->turnOnBits(1 << OCIE3A);
        started = true;

        interruptsControl->enableInterrupts();
    }

    void CTCTimer3::stop()
    {
        interruptsControl->disableInterrupts();

        // basically clock source 'none'
        ControlRegisterB->turnOffBits(1 << CS32 | 1 << CS31 | 1 << CS30);

        interruptsControl->enableInterrupts();
    }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"

    ISR(TIMER3_COMPA_vect)
    {
        if (started)
        {
            timerF();
        }
    }

#pragma GCC diagnostic pop
} // namespace hardware::timers
