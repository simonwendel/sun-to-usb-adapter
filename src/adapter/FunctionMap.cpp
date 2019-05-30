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

#include "FunctionMap.h"

namespace adapter
{
    FunctionMap::FunctionMap(int capacity) : capacity(capacity)
    {
        count = 0;
        functions = new Function[capacity];
        for (int index = 0; index < capacity; ++index)
        {
            functions[index] = nullptr;
        }
    }

    int FunctionMap::getCount()
    {
        return count;
    }

    int FunctionMap::getCapacity()
    {
        return capacity;
    }

    bool FunctionMap::mapFunction(int key, Function function)
    {
        if (key < 0 || key >= capacity)
        {
            return false;
        }

        functions[key] = function;
        ++count;
        return true;
    }

    Function FunctionMap::getFunction(int key)
    {
        if (key < 0 || key >= capacity)
        {
            return nullptr;
        }

        return functions[key];
    }

    FunctionMap::~FunctionMap()
    {
        delete[] functions;
    }
} // namespace adapter
