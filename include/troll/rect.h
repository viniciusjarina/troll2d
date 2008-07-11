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

#ifndef __TROLL_RECT_H__
#define __TROLL_RECT_H__

namespace Troll
{


class  Rect
{
public:
    Rect()
        : x(0), y(0), width(0), height(0)
        { }
    Rect(int xx, int yy, int ww, int hh)
        : x(xx), y(yy), width(ww), height(hh)
        { }
    Rect(const Point& topLeft, const Point& bottomRight);
    Rect(const Point& pt, const Size& size)
        : x(pt.x), y(pt.y), width(size.x), height(size.y)
        { }
    Rect(const Size& size)
        : x(0), y(0), width(size.x), height(size.y)
        { }

    // default copy ctor and assignment operators ok

    inline int GetX() const { return x; }
    inline void SetX(int xx) { x = xx; }

    inline int GetY() const { return y; }
    inline void SetY(int yy) { y = yy; }

    inline int GetWidth() const { return width; }
    inline void SetWidth(int w) { width = w; }

    inline int GetHeight() const { return height; }
    inline void SetHeight(int h) { height = h; }

    inline Point GetPosition() const { return Point(x, y); }
    inline void SetPosition( const Point &p ) { x = p.x; y = p.y; }

    inline Size GetSize() const { return Size(width, height); }
    inline void SetSize( const Size &s ) { width = s.GetWidth(); height = s.GetHeight(); }

    inline bool IsEmpty() const { return (width <= 0) || (height <= 0); }

    inline int GetLeft()   const { return x; }
    inline int GetTop()    const { return y; }
    inline int GetBottom() const { return y + height - 1; }
    inline int GetRight()  const { return x + width - 1; }

    inline void SetLeft(int left) { x = left; }
    inline void SetRight(int right) { width = right - x + 1; }
    inline void SetTop(int top) { y = top; }
    inline void SetBottom(int bottom) { height = bottom - y + 1; }

    inline Point GetTopLeft() const { return GetPosition(); }
    inline Point GetLeftTop() const { return GetTopLeft(); }
    inline void SetTopLeft(const Point &p) { SetPosition(p); }
    inline void SetLeftTop(const Point &p) { SetTopLeft(p); }

    inline Point GetBottomRight() const { return Point(GetRight(), GetBottom()); }
    inline Point GetRightBottom() const { return GetBottomRight(); }
    inline void SetBottomRight(const Point &p) { SetRight(p.x); SetBottom(p.y); }
    inline void SetRightBottom(const Point &p) { SetBottomRight(p); }

    inline Point GetTopRight() const { return Point(GetRight(), GetTop()); }
    inline Point GetRightTop() const { return GetTopRight(); }
    inline void SetTopRight(const Point &p) { SetRight(p.x); SetTop(p.y); }
    inline void SetRightTop(const Point &p) { SetTopLeft(p); }

    inline Point GetBottomLeft() const { return Point(GetLeft(), GetBottom()); }
    inline Point GetLeftBottom() const { return GetBottomLeft(); }
    inline void SetBottomLeft(const Point &p) { SetLeft(p.x); SetBottom(p.y); }
    inline void SetLeftBottom(const Point &p) { SetBottomLeft(p); }

	inline Point GetCenterPoint() const { return Point(x + width/2,y + height/2); }

    // operations with rect
    inline Rect& Inflate(long dx, long dy);
    inline Rect& Inflate(const Size& d) { return Inflate(d.x, d.y); }
    inline Rect& Inflate(long d) { return Inflate(d, d); }
    inline Rect Inflate(long dx, long dy) const
    {
        Rect r = *this;
        r.Inflate(dx, dy);
        return r;
    }

    inline Rect& Deflate(long dx, long dy) { return Inflate(-dx, -dy); }
    inline Rect& Deflate(const Size& d) { return Inflate(-d.x, -d.y); }
    inline Rect& Deflate(long d) { return Inflate(-d); }
    inline Rect Deflate(long dx, long dy) const
    {
        Rect r = *this;
        r.Deflate(dx, dy);
        return r;
    }

    inline void Offset(long dx, long dy) { x += dx; y += dy; }
    inline void Offset(const Point& pt) { Offset(pt.x, pt.y); }

    Rect Intersect(const Rect& rect) const;
    Rect Union(const Rect& rect) const;
    

    // compare rectangles
    bool operator==(const Rect& rect) const;
    bool operator!=(const Rect& rect) const { return !(*this == rect); }

    // return true if the point is (not strcitly) inside the rect
    bool Contains(int x, int y) const;
    inline bool Contains(const Point& pt) const { return Contains(pt.x, pt.y); }
    // return true if the rectangle is (not strcitly) inside the rect
    bool Contains(const Rect& rect) const;

    // return true if the rectangles have a non empty intersection
    bool Intersects(const Rect& rect) const;

public:
    int x, y, width, height;
};

}
#endif // __TROLL_RECT_H__