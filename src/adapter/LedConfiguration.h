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

namespace adapter
{
    class LedConfiguration
    {
        static const int NUM_LOCK_BIT = 0;
        static const int COMPOSE_BIT = 1;
        static const int SCROLL_LOCK_BIT = 2;
        static const int CAPS_LOCK_BIT = 3;

        uint8_t payload;

    public:
        LedConfiguration();
        LedConfiguration(uint8_t initialPayload);

        void setNumLock();
        void unsetNumLock();
        void toggleNumLock();

        void setCompose();
        void unsetCompose();
        void toggleCompose();

        void setScrollLock();
        void unsetScrollLock();
        void toggleScrollLock();

        void setCapsLock();
        void unsetCapsLock();
        void toggleCapsLock();

        bool operator==(const int rhs) const;
        bool operator==(const uint8_t rhs) const;
        bool operator==(const LedConfiguration &rhs) const;

        operator uint8_t();
    };
} // namespace adapter
