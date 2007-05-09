#if !defined(__TROLL2D_BASIC_GEO_H__
#define __TROLL2D_BASIC_GEO_H__

class Size
{
public:
    // members are public for compatibility, don't use them directly.
    int x, y;

    // constructors
    Size() : x(0), y(0) { }
    Size(int xx, int yy) : x(xx), y(yy) { }

    // no copy ctor or assignment operator - the defaults are ok

    bool operator==(const Size& sz) const { return x == sz.x && y == sz.y; }
    bool operator!=(const Size& sz) const { return x != sz.x || y != sz.y; }

    Size operator+(const Size& sz) const { return Size(x + sz.x, y + sz.y); }
    Size operator-(const Size& sz) const { return Size(x - sz.x, y - sz.y); }
    Size operator/(int i) const { return Size(x / i, y / i); }
    Size operator*(int i) const { return Size(x * i, y * i); }

    Size& operator+=(const Size& sz) { x += sz.x; y += sz.y; return *this; }
    Size& operator-=(const Size& sz) { x -= sz.x; y -= sz.y; return *this; }
    Size& operator/=(const int i) { x /= i; y /= i; return *this; }
    Size& operator*=(const int i) { x *= i; y *= i; return *this; }

    Size& Scale(float xscale, float yscale)
        { x = (int)(x*xscale); y = (int)(y*yscale); return *this; }

    // accessors
    void Set(int xx, int yy) { x = xx; y = yy; }
    void SetWidth(int w) { x = w; }
    void SetHeight(int h) { y = h; }

    int GetWidth() const { return x; }
    int GetHeight() const { return y; }
};


class Point
{
public:
    int x, y;

    Point() : x(0), y(0) { }
    Point(int xx, int yy) : x(xx), y(yy) { }

    // no copy ctor or assignment operator - the defaults are ok

    // comparison
    bool operator==(const Point& p) const { return x == p.x && y == p.y; }
    bool operator!=(const Point& p) const { return !(*this == p); }

    // arithmetic operations (component wise)
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }

    Point& operator+=(const Point& p) { x += p.x; y += p.y; return *this; }
    Point& operator-=(const Point& p) { x -= p.x; y -= p.y; return *this; }

    Point& operator+=(const Size& s) { x += s.GetWidth(); y += s.GetHeight(); return *this; }
    Point& operator-=(const Size& s) { x -= s.GetWidth(); y -= s.GetHeight(); return *this; }

    Point operator+(const Size& s) const { return Point(x + s.GetWidth(), y + s.GetHeight()); }
    Point operator-(const Size& s) const { return Point(x - s.GetWidth(), y - s.GetHeight()); }

    Point operator-() const { return Point(-x, -y); }
};


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

    int GetX() const { return x; }
    void SetX(int xx) { x = xx; }

    int GetY() const { return y; }
    void SetY(int yy) { y = yy; }

    int GetWidth() const { return width; }
    void SetWidth(int w) { width = w; }

    int GetHeight() const { return height; }
    void SetHeight(int h) { height = h; }

    Point GetPosition() const { return Point(x, y); }
    void SetPosition( const Point &p ) { x = p.x; y = p.y; }

    Size GetSize() const { return Size(width, height); }
    void SetSize( const Size &s ) { width = s.GetWidth(); height = s.GetHeight(); }

    bool IsEmpty() const { return (width <= 0) || (height <= 0); }

    int GetLeft()   const { return x; }
    int GetTop()    const { return y; }
    int GetBottom() const { return y + height - 1; }
    int GetRight()  const { return x + width - 1; }

    void SetLeft(int left) { x = left; }
    void SetRight(int right) { width = right - x + 1; }
    void SetTop(int top) { y = top; }
    void SetBottom(int bottom) { height = bottom - y + 1; }

    Point GetTopLeft() const { return GetPosition(); }
    Point GetLeftTop() const { return GetTopLeft(); }
    void SetTopLeft(const Point &p) { SetPosition(p); }
    void SetLeftTop(const Point &p) { SetTopLeft(p); }

    Point GetBottomRight() const { return Point(GetRight(), GetBottom()); }
    Point GetRightBottom() const { return GetBottomRight(); }
    void SetBottomRight(const Point &p) { SetRight(p.x); SetBottom(p.y); }
    void SetRightBottom(const Point &p) { SetBottomRight(p); }

    Point GetTopRight() const { return Point(GetRight(), GetTop()); }
    Point GetRightTop() const { return GetTopRight(); }
    void SetTopRight(const Point &p) { SetRight(p.x); SetTop(p.y); }
    void SetRightTop(const Point &p) { SetTopLeft(p); }

    Point GetBottomLeft() const { return Point(GetLeft(), GetBottom()); }
    Point GetLeftBottom() const { return GetBottomLeft(); }
    void SetBottomLeft(const Point &p) { SetLeft(p.x); SetBottom(p.y); }
    void SetLeftBottom(const Point &p) { SetBottomLeft(p); }

    // operations with rect
    Rect& Inflate(long dx, long dy);
    Rect& Inflate(const Size& d) { return Inflate(d.x, d.y); }
    Rect& Inflate(long d) { return Inflate(d, d); }
    Rect Inflate(long dx, long dy) const
    {
        Rect r = *this;
        r.Inflate(dx, dy);
        return r;
    }

    Rect& Deflate(long dx, long dy) { return Inflate(-dx, -dy); }
    Rect& Deflate(const Size& d) { return Inflate(-d.x, -d.y); }
    Rect& Deflate(long d) { return Inflate(-d); }
    Rect Deflate(long dx, long dy) const
    {
        Rect r = *this;
        r.Deflate(dx, dy);
        return r;
    }

    void Offset(long dx, long dy) { x += dx; y += dy; }
    void Offset(const Point& pt) { Offset(pt.x, pt.y); }

    Rect Intersect(const Rect& rect) const;


    Rect Union(const Rect& rect) const;
    

    // compare rectangles
    bool operator==(const Rect& rect) const;
    bool operator!=(const Rect& rect) const { return !(*this == rect); }

    // return true if the point is (not strcitly) inside the rect
    bool Contains(int x, int y) const;
    bool Contains(const Point& pt) const { return Contains(pt.x, pt.y); }
    // return true if the rectangle is (not strcitly) inside the rect
    bool Contains(const Rect& rect) const;

    // return true if the rectangles have a non empty intersection
    bool Intersects(const Rect& rect) const;


public:
    int x, y, width, height;
};

#endif // __TROLL2D_BASIC_GEO_H__