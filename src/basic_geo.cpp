#include "troll/basic_geo.h"

Rect::Rect(const Point& point1, const Point& point2)
{
    x = point1.x;
    y = point1.y;
    width = point2.x - point1.x;
    height = point2.y - point1.y;

    if (width < 0)
    {
        width = -width;
        x = point2.x;
    }
    width++;

    if (height < 0)
    {
        height = -height;
        y = point2.y;
    }
    height++;
}

bool Rect::operator==(const Rect& rect) const
{
    return ((x == rect.x) &&
            (y == rect.y) &&
            (width == rect.width) &&
            (height == rect.height));
}


Rect Rect::Union(const Rect& rect) const
{
	// TODO:
/*	Rect r(*this);
    // ignore empty rectangles: union with an empty rectangle shouldn't extend
    // this one to (0, 0)
    if ( !width || !height )
         return rect;
    
    if ( rect.width && rect.height )
    {
        int x1 = min(x, rect.x);
        int y1 = min(y, rect.y);
        int y2 = min(y + height, rect.height + rect.y);
        int x2 = min(x + width, rect.width + rect.x);

        r.x = x1;
        r.y = y1;
        r.width = x2 - x1;
        r.height = y2 - y1;
    }
    //else: we're not empty and rect is empty

    return r;*/
	return Rect();
}

Rect& Rect::Inflate(long dx, long dy)
{
     if (-2*dx>width)
     {
         // Don't allow deflate to eat more width than we have,
         // a well-defined rectangle cannot have negative width.
         x+=width/2;
         width=0;
     }
     else
     {
         // The inflate is valid.
         x-=dx;
         width+=2*dx;
     }

     if (-2*dy>height)
     {
         // Don't allow deflate to eat more height than we have,
         // a well-defined rectangle cannot have negative height.
         y+=height/2;
         height=0;
     }
     else
     {
         // The inflate is valid.
         y-=dy;
         height+=2*dy;
     }

    return *this;
}

bool Rect::Contains(int cx, int cy) const
{
    return ( (cx >= x) && (cy >= y)
          && ((cy - y) < height)
          && ((cx - x) < width)
          );
}

bool Rect::Contains(const Rect& rect) const
{
    return Contains(rect.GetTopLeft()) && Contains(rect.GetBottomRight());
}

Rect Rect::Intersect(const Rect& rect) const
{ // TODO: 
   /* int x2 = GetRight(),
        y2 = GetBottom();

    if ( x < rect.x )
        x = rect.x;
    if ( y < rect.y )
        y = rect.y;
    if ( x2 > rect.GetRight() )
        x2 = rect.GetRight();
    if ( y2 > rect.GetBottom() )
        y2 = rect.GetBottom();

    width = x2 - x + 1;
    height = y2 - y + 1;

    if ( width <= 0 || height <= 0 )
    {
        width =
        height = 0;
    }

    return *this;*/
	return Rect();
}

bool Rect::Intersects(const Rect& rect) const
{
    Rect r = Intersect(rect);

    // if there is no intersection, both width and height are 0
    return r.width != 0;
}