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

#include "ActionMap.h"

namespace adapter
{
    template <typename TParam>
    ActionMap<TParam>::ActionMap(int capacity) : capacity{capacity}
    {
        count = 0;
        actions = new Action<TParam>[capacity];
        for (int index = 0; index < capacity; ++index)
        {
            actions[index] = nullptr;
        }
    }

    template <typename TParam>
    int ActionMap<TParam>::getCount()
    {
        return count;
    }

    template <typename TParam>
    int ActionMap<TParam>::getCapacity()
    {
        return capacity;
    }

    template <typename TParam>
    bool ActionMap<TParam>::hasMapping(int key)
    {
        return getAction(key) != nullptr;
    }

    template <typename TParam>
    bool ActionMap<TParam>::mapAction(int key, Action<TParam> action)
    {
        if (key < 0 || key >= capacity)
        {
            return false;
        }

        actions[key] = action;
        ++count;
        return true;
    }

    template <typename TParam>
    Action<TParam> ActionMap<TParam>::getAction(int key)
    {
        if (key < 0 || key >= capacity)
        {
            return nullptr;
        }

        return actions[key];
    }

    template <typename TParam>
    ActionMap<TParam>::~ActionMap()
    {
        delete[] actions;
    }
} // namespace adapter
