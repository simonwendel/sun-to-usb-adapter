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

#include "../Register.h"
#include "ICTCTimer.h"

#include <stdint.h>

namespace hardware::timers
{
    /* A CTC Mode timer of register size R */
    template <typename R>
    class CTCTimer : public ICTCTimer
    {
    protected:
        /* TCCRxA */
        hardware::Register<uint8_t> *ControlRegisterA;

        /* TCCRxB */
        hardware::Register<uint8_t> *ControlRegisterB;

        /* TIMSKx */
        hardware::Register<uint8_t> *InterruptMaskRegister;

        /* TCNTx */
        hardware::Register<R> *CounterRegister;

        /* OCRxA */
        hardware::Register<R> *CompareMatchRegister;

        CTCTimer(volatile uint8_t *tccra,
                 volatile uint8_t *tccrb,
                 volatile uint8_t *timsk,
                 volatile R *tcnt,
                 volatile R *ocra);

    public:
        virtual ~CTCTimer();
    };
} // namespace hardware::timers

#include "CTCTimer.tpp"