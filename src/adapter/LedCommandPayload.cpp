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

#include "LedCommandPayload.h"

#include <stdint.h>

namespace adapter
{
    static void setBit(uint8_t &value, int bit);
    static void unsetBit(uint8_t &value, int bit);

    LedCommandPayload::LedCommandPayload() : payload{0}
    {
    }

    LedCommandPayload::LedCommandPayload(uint8_t initialPayload) :
        payload{initialPayload}
    {
    }

    bool LedCommandPayload::operator==(const int rhs) const
    {
        return payload == rhs;
    }

    bool LedCommandPayload::operator==(const uint8_t rhs) const
    {
        return payload == rhs;
    }

    LedCommandPayload::operator uint8_t()
    {
        return payload;
    }

    void LedCommandPayload::setNumLock()
    {
        setBit(payload, 0);
    }

    void LedCommandPayload::unsetNumLock()
    {
        unsetBit(payload, 0);
    }

    void LedCommandPayload::setCompose()
    {
        setBit(payload, 1);
    }

    void LedCommandPayload::unsetCompose()
    {
        unsetBit(payload, 1);
    }

    void LedCommandPayload::setScrollLock()
    {
        setBit(payload, 2);
    }

    void LedCommandPayload::unsetScrollLock()
    {
        unsetBit(payload, 2);
    }

    void LedCommandPayload::setCapsLock()
    {
        setBit(payload, 3);
    }

    void LedCommandPayload::unsetCapsLock()
    {
        unsetBit(payload, 3);
    }

    static void setBit(uint8_t &value, int bit)
    {
        value |= 1 << bit;
    }

    static void unsetBit(uint8_t &value, int bit)
    {
        value &= ~(1 << bit);
    }
} // namespace adapter
