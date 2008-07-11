/*
 *
 *  ______             ___    ___      
 * /\__  _\           /\_ \  /\_ \     
 * \/_/\ \/ _ __   ___\//\ \ \//\ \    
 *    \ \ \/\`'__\/ __`\\ \ \  \ \ \   
 *     \ \ \ \ \//\ \L\ \\_\ \_ \_\ \_ 
 *      \ \_\ \_\\ \____//\____\/\____\
 *       \/_/\/_/ \/___/ \/____/\/____/
 *
 * Copyright (c) 2008, JarinSoft
 * All rights reserved.
 *
 * Vinicius Jarina (viniciusjarina@gmail.com)
 *
 * Visit: http://troll2d.googlecode.com
 *
 * Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *      * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the JarinSoft nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY JarinSoft ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL JARINSOFT BE LIABLE FOR ANY
 *   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __TROLL_SIZE_H__
#define __TROLL_SIZE_H__

namespace Troll
{

class Size
{
public:
    // x - store the width of size
	// y - store the height of size
    int x, y;

    // constructors
    Size() : x(0), y(0) { }
    Size(int xx, int yy) : x(xx), y(yy) { }

    // no copy ctor or assignment operator - the defaults are ok
    inline bool operator==(const Size& sz) const { return x == sz.x && y == sz.y; }
    inline bool operator!=(const Size& sz) const { return x != sz.x || y != sz.y; }

    inline Size operator+(const Size& sz) const { return Size(x + sz.x, y + sz.y); }
    inline Size operator-(const Size& sz) const { return Size(x - sz.x, y - sz.y); }
    inline Size operator/(int i) const { return Size(x / i, y / i); }
    inline Size operator*(int i) const { return Size(x * i, y * i); }

    inline Size& operator+=(const Size& sz) { x += sz.x; y += sz.y; return *this; }
    inline Size& operator-=(const Size& sz) { x -= sz.x; y -= sz.y; return *this; }
    inline Size& operator/=(const int i) { x /= i; y /= i; return *this; }
    inline Size& operator*=(const int i) { x *= i; y *= i; return *this; }

    Size& Scale(float xscale, float yscale)
        { x = (int)(x*xscale); y = (int)(y*yscale); return *this; }

    // accessors
    inline void Set(int xx, int yy) { x = xx; y = yy; }
    inline void SetWidth(int w) { x = w; }
    inline void SetHeight(int h) { y = h; }

    inline int GetWidth() const { return x; }
    inline int GetHeight() const { return y; }
};

}
#endif // __TROLL_SIZE_H__