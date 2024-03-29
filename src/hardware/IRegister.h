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

#include <stdint.h>

namespace hardware
{
    template <typename R>
    class IRegister
    {
    public:
        virtual void clearRegister() = 0;
        virtual void setRegister(R value) = 0;
        virtual void turnOnBits(R mask) = 0;
        virtual void turnOffBits(R mask) = 0;
        virtual R readRegister() = 0;

        virtual bool operator==(const IRegister<R> &rhs) const = 0;
    };
} // namespace hardware
