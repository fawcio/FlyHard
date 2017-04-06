/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Sławomir Cielepak
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#pragma once

namespace fly_hard
{

struct CommandCategory
{
    enum value_t
    {
        eNone           = 0,
        eScene          = 1,
        ePlayerAircraft	= 2,
        eEnemyAircraft	= 4
    } value;

    explicit CommandCategory() : value(eNone) {}
    explicit CommandCategory(unsigned int val) : value(static_cast<value_t>(val)) {}

    explicit operator bool()
    {
        return ( this->value != eNone  );
    }
};

inline CommandCategory operator|(const CommandCategory left, CommandCategory right)
{
    return CommandCategory(left.value | right.value);
}

inline CommandCategory operator&(const CommandCategory left, CommandCategory right)
{
    return CommandCategory(left.value & right.value);
}

}
