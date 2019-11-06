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

#include "LedConfiguration.h"

#include <stdint.h>

namespace adapter
{
    static void setBit(uint8_t &value, int bit);
    static void unsetBit(uint8_t &value, int bit);

    LedConfiguration::LedConfiguration() : payload{0}
    {
    }

    LedConfiguration::LedConfiguration(uint8_t initialPayload) :
        payload{initialPayload}
    {
    }

    bool LedConfiguration::operator==(const int rhs) const
    {
        return payload == rhs;
    }

    bool LedConfiguration::operator==(const uint8_t rhs) const
    {
        return payload == rhs;
    }

    bool LedConfiguration::operator==(const LedConfiguration &rhs) const
    {
        return payload == rhs.payload;
    }

    LedConfiguration::operator uint8_t()
    {
        return payload;
    }

    void LedConfiguration::setNumLock()
    {
        setBit(payload, NUM_LOCK_BIT);
    }

    void LedConfiguration::unsetNumLock()
    {
        unsetBit(payload, NUM_LOCK_BIT);
    }

    void LedConfiguration::setCompose()
    {
        setBit(payload, COMPOSE_BIT);
    }

    void LedConfiguration::unsetCompose()
    {
        unsetBit(payload, COMPOSE_BIT);
    }

    void LedConfiguration::setScrollLock()
    {
        setBit(payload, SCROLL_LOCK_BIT);
    }

    void LedConfiguration::unsetScrollLock()
    {
        unsetBit(payload, SCROLL_LOCK_BIT);
    }

    void LedConfiguration::setCapsLock()
    {
        setBit(payload, CAPS_LOCK_BIT);
    }

    void LedConfiguration::unsetCapsLock()
    {
        unsetBit(payload, CAPS_LOCK_BIT);
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
