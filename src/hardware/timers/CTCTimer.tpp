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

#include "CTCTimer.h"

namespace hardware::timers
{
    template <typename R>
    CTCTimer<R>::CTCTimer(volatile uint8_t *tccra,
                          volatile uint8_t *tccrb,
                          volatile uint8_t *timsk,
                          volatile R *tcnt,
                          volatile R *ocra) :
        ControlRegisterA{new hardware::Register<uint8_t>{tccra}},
        ControlRegisterB{new hardware::Register<uint8_t>{tccrb}},
        InterruptMaskRegister{new hardware::Register<uint8_t>{timsk}},
        CounterRegister{new hardware::Register<R>{tcnt}},
        CompareMatchRegister{new hardware::Register<R>{ocra}}
    {
    }
} // namespace hardware::timers
