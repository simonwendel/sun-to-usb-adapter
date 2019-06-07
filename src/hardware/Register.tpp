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

#include "Register.h"

#include <stdint.h>

namespace hardware
{
    template <typename R>
    Register<R>::Register(volatile R *reg) : reg(reg)
    {
    }

    template <typename R>
    bool Register<R>::operator==(const IRegister<R> &theOther) const
    {
        const Register<R> *that = dynamic_cast<const Register<R> *>(&theOther);
        return that != nullptr && reg == that->reg;
    }

    template <typename R>
    void Register<R>::clearRegister()
    {
        setRegister(0);
    }

    template <typename R>
    void Register<R>::setRegister(R value)
    {
        *reg = value;
    }

    template <typename R>
    void Register<R>::turnOnBits(R bits)
    {
        *reg |= bits;
    }

    template <typename R>
    R Register<R>::readRegister()
    {
        return *reg;
    }
} // namespace hardware
