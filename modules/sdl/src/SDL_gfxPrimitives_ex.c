/* 

 SDL_gfxPrimitives - Extensions

 Vinicius Jarina (viniciusjarina@gmail.com)

*/

#include <SDL.h>

#include "SDL_gfxPrimitives.h"
#include "do_arc.h"


typedef struct _gfx_point
{
	Sint16 * m_arr_x;
	Sint16 * m_arr_y;
} gfx_point;

/* SDL_gfx internal */
extern int fastPixelColorNolock(SDL_Surface * dst, Sint16 x, Sint16 y, Uint32 color);
extern int pixelColorNolock(SDL_Surface * dst, Sint16 x, Sint16 y, Uint32 color);

/* Custom primitives */
static void _RoundRectFill(SDL_Surface *bmp, short x,short y, short w,short h, short r, int color);
static void _RoundRect(SDL_Surface *dst, short x,short y, short w,short h, short r, int color);

static void _ArcFill(SDL_Surface *bmp, int x,int y, short ang1,short ang2, int r, int color);
static int  _Arc(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 r, Sint16 start, Sint16 end, Uint32 color);

static void _DrawPixelAlpha(void *bmp,int x, int y, void * d);
static void _DrawPixel(void *bmp,int x, int y, void * d);

int arcColorEx(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 r, Sint16 start, Sint16 end, Uint32 color)
{
	short ang1 = (start * 256)/360;
	short ang2 = (end   * 256)/360;
	
	return _Arc(dst,x,y,r,ang1,ang2,color);
}

int arcRGBAEx(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad, Sint16 start, Sint16 end, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    /*
     * Draw 
     */
    return (arcColorEx(dst, x, y, rad, start, end, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a));
}

int filledArcColorEx(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad, Sint16 start, Sint16 end, Uint32 color)
{
	short ang1 = (start * 256)/360;
	short ang2 = (end   * 256)/360;

	_ArcFill(dst,x,y,ang1,ang2,rad,color);
	return 0;
}

int filledArcRGBAEx(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad, Sint16 start, Sint16 end, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	return filledArcColorEx(dst, x, y, rad, start, end, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a);
}


int filledRoundRectRGBA(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 w, Sint16 h, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_RoundRectFill(dst, x, y, w, h, rad, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a);
	return 0;
}


int roundRectRGBA(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 w, Sint16 h, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_RoundRect(dst, x, y, w, h, rad, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a);
	return 0;
}


static void _DrawPixel(void *bmp,int x, int y, void * d)
{
	fastPixelColorNolock(bmp ,(Sint16)x, (Sint16)y,(Uint32)d);
}

static void _DrawPixelAlpha(void *bmp,int x, int y, void * d)
{
	pixelColorNolock(bmp ,(Sint16)x, (Sint16)y,(Uint32)d);
}

static void compute_arc_total_points(void *bmp,int x, int y, void * d)
{
	int * p_total_points = (int*)d;
	(*p_total_points)++;

}
// Store each point of arc
static int compute_arc_points(void *bmp,int x, int y, void * d)
{
	gfx_point * p_points = (gfx_point *)d;
	
	*(p_points->m_arr_x) = x;
	(p_points->m_arr_x)++;

	*(p_points->m_arr_y) = y;
	(p_points->m_arr_y)++;
	return 0;
}
	
// draw a filled arc (missing in allegro, I do the mine)
static void _ArcFill(SDL_Surface *bmp, int x,int y, short ang1,short ang2, int r, int color)
{
	gfx_point points;
	Sint16 * buffer;

	int total_points = 1;
		
	do_arc(NULL, x, y, ang1, ang2, r, &total_points, compute_arc_total_points);
		
	if(total_points < 2)
		return;
		
	buffer = calloc(2*total_points,sizeof(Sint16)); 

	points.m_arr_x = buffer;
	points.m_arr_y = buffer + total_points;

	*(points.m_arr_x) = x;
	*(points.m_arr_y) = y;

	points.m_arr_x++;
	points.m_arr_y++;

	do_arc(NULL, x, y, ang1, ang2, r, &points, compute_arc_points);

	points.m_arr_x = buffer;
	points.m_arr_y = buffer + total_points;
		
	filledPolygonColor(bmp,points.m_arr_x,points.m_arr_y,total_points,color);
		
	free(buffer);		
}

static int _Arc(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 r, Sint16 start, Sint16 end, Uint32 color)
{
    Sint16 left, right, top, bottom;
    int result;
    Sint16 x1, y1, x2, y2;
    Uint8 *colorptr;

    /* Check visibility of clipping rectangle */
    if ((dst->clip_rect.w == 0) || (dst->clip_rect.h == 0))
	{
		return(0);
    }

    /* Sanity check radius  */
    if (r < 0)
	{
		return -1;
    }

    /* Special case for r=0 - draw a point   */
    if (r == 0) 
	{
		return pixelColor(dst, x, y, color);
    }
 
    /*
     * Get arc's circle and clipping boundary and 
     * test if bounding box of circle is visible 
     */
    x2 = x + r;
    left = dst->clip_rect.x;
    if (x2 < left)
	{
		return 0;
    }

    x1 = x - r;
    right = dst->clip_rect.x + dst->clip_rect.w - 1;
    if (x1 > right)
	{
		return 0;
    }

    y2 = y + r;
    top = dst->clip_rect.y;
    if (y2 < top)
	{
		return 0;
    }

    y1 = y - r;
    bottom = dst->clip_rect.y + dst->clip_rect.h - 1;
    if (y1 > bottom)
	{
		return 0;
    }  

    /* Draw arc  */
    result = 0;

    /* Lock surface */
    if (SDL_MUSTLOCK(dst))
	{
		if (SDL_LockSurface(dst) < 0) 
			return -1;
	}

    /* Alpha Check  */
    if ((color & 255) == 255) 
	{
		/* No Alpha - direct memory writes  */

		/* Setup color  */
		colorptr = (Uint8 *) & color;
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) 
		{
			color = SDL_MapRGBA(dst->format, colorptr[0], colorptr[1], colorptr[2], colorptr[3]);
		}
		else
		{
			color = SDL_MapRGBA(dst->format, colorptr[3], colorptr[2], colorptr[1], colorptr[0]);
		}
		do_arc(dst, x, y, start, end, r, (void*)color,_DrawPixel);
		
	} 
	else
	{
	/* Using Alpha - blended pixel blits */
		do_arc(dst, x, y, start, end, r, (void*)color,_DrawPixelAlpha);

    }/* Alpha check */

    /* Unlock surface */
    if (SDL_MUSTLOCK(dst))
	{
		SDL_UnlockSurface(dst);
    }
    return result;
}

static void _RoundRectFill(SDL_Surface *bmp, short x,short y, short w,short h, short r, int color)
{
	gfx_point points;
	Sint16 * buffer;
	
	int total_points = 0;
	
	do_arc(NULL,0,0,0,64,r,&total_points,compute_arc_total_points);
	do_arc(NULL,0,0,64,128,r,&total_points,compute_arc_total_points);
	do_arc(NULL,0,0,128,192,r,&total_points,compute_arc_total_points);
	do_arc(NULL,0,0,192,255,r,&total_points,compute_arc_total_points);
	
	if(total_points < 2)
		return;
	
	buffer = calloc(2*total_points,sizeof(Sint16)); 
	
	points.m_arr_x = buffer;
	points.m_arr_y = buffer + total_points;
	
	do_arc(NULL,x + w - r,y + r,0,64,r,&points,compute_arc_points);
	do_arc(NULL,x + r,y + r,64,128,r,&points,compute_arc_points);
	do_arc(NULL,x + r,y + h - r,128,192,r,&points,compute_arc_points);
	do_arc(NULL,x + w - r,y + h - r,192,255,r,&points,compute_arc_points);
	
	
	points.m_arr_x = buffer;
	points.m_arr_y = buffer + total_points;
	
	filledPolygonColor(bmp,points.m_arr_x,points.m_arr_y,total_points,color);
	
	free(buffer);		
}

// draw a filled arc (missing in SDL_gfx)
static void _RoundRect(SDL_Surface *dst, short x,short y, short w,short h, short r, int color)
{
    Sint16 left, right, top, bottom;
    int c; /* Temp color */
    Sint16 x2, y2;
    Uint8 *colorptr;

    /* Check visibility of clipping rectangle */
    if ((dst->clip_rect.w == 0) || (dst->clip_rect.h == 0))
	{
		return;
    }

    /* Sanity check radius  */
    if (r < 0)
	{
		return;
    }


    /*
     * Get arc's circle and clipping boundary and 
     * test if bounding box of circle is visible 
     */
    x2 = x + w;
    left = dst->clip_rect.x;
    if (x2 < left)
	{
		return;
    }
  
    right = dst->clip_rect.x + dst->clip_rect.w - 1;
    if (x > right)
	{
		return;
    }

    y2 = y + h;
    top = dst->clip_rect.y;
    if (y2 < top)
	{
		return;
    }
    
    bottom = dst->clip_rect.y + dst->clip_rect.h - 1;
    if (y > bottom)
	{
		return;
    }  


    /* Lock surface */
    if (SDL_MUSTLOCK(dst))
	{
		if (SDL_LockSurface(dst) < 0) 
			return;
	}

    /* Alpha Check  */
    if ((color & 255) == 255) 
	{
		/* No Alpha - direct memory writes  */

		/* Setup color  */
		colorptr = (Uint8 *) & color;
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) 
		{
			c = SDL_MapRGBA(dst->format, colorptr[0], colorptr[1], colorptr[2], colorptr[3]);
		}
		else
		{
			c = SDL_MapRGBA(dst->format, colorptr[3], colorptr[2], colorptr[1], colorptr[0]);
		}

		do_arc(dst,x + w - r,y + r,0,64,r,(void*)c,_DrawPixel);
		hlineColor(dst,x + r + 1, x + w - r - 1,y ,color);
		
		do_arc(dst,x + r,y + r,64,128,r,(void*)c,_DrawPixel);
		vlineColor(dst,x ,y + r + 1,y + h - r - 1,color);

		do_arc(dst,x + r,y + h - r,128,192,r,(void*)c,_DrawPixel);
		hlineColor(dst,x + r + 1, x + w - r - 1,y + h,color);

		do_arc(dst,x + w - r,y + h - r,192,255,r,(void*)c,_DrawPixel);
		vlineColor(dst,x + w,y + h - r - 1,y + r + 1,color);
	} 
	else
	{
	/* Using Alpha - blended pixel blits */
		do_arc(dst,x + w - r,y + r,0,64,r,(void*)color,_DrawPixelAlpha);
		hlineColor(dst,x + r + 1, x + w - r - 1,y ,color);
		
		do_arc(dst,x + r,y + r,64,128,r,(void*)color,_DrawPixelAlpha);
		vlineColor(dst,x ,y + r + 1,y + h - r - 1,color);
		
		do_arc(dst,x + r,y + h - r,128,192,r,(void*)color,_DrawPixelAlpha);
		hlineColor(dst,x + r + 1, x + w - r - 1,y + h,color);
		
		do_arc(dst,x + w - r,y + h - r,192,255,r,(void*)color,_DrawPixelAlpha);
		vlineColor(dst,x + w,y + h - r - 1,y + r + 1,color);

    }/* Alpha check */

    /* Unlock surface */
    if (SDL_MUSTLOCK(dst))
	{
		SDL_UnlockSurface(dst);
    }
    return;
}
