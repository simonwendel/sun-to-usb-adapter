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

#include "IRegister.h"

#include <stdint.h>

namespace hardware
{
    template <typename R>
    class Register : public IRegister<R>
    {
        volatile R *reg;

    public:
        Register(volatile R *reg);

        void clearRegister() override;
        void setRegister(R value) override;
        void turnOnBits(R mask) override;
        void turnOffBits(R mask) override;

        R readRegister() override;

        bool operator==(const IRegister<R> &rhs) const override;
    };
} // namespace hardware

#include "Register.tpp"
