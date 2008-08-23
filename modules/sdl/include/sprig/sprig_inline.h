#ifndef _SPG_INLINE_H__
#define _SPG_INLINE_H__


/* Surface */

#include "math.h"

static inline float SPG_sqrt(float x)
{
    /*float xhalf = 0.5f*x;  // From Wikipedia
    int i = *(int *)&x;
    i = 0x5f3759df - (i >> 1);
    x = *(float *)&i;
    x = x * (1.5f - xhalf * x * x);

    return 1/x;*/
    return sqrtf(x);
}

#ifdef _SPG_C_ONLY
static inline SDL_Surface* SPG_Rotate(SDL_Surface *src, float angle, Uint32 bcol)
{
   //return SPG_Transform(src, bcol, angle, 1.0, 1.0, 0);
   SDL_Surface *dest;

	/* Create the destination surface*/
	int max = (int)( SPG_sqrt( (src->h*src->h/2 + src->w*src->w/2) + 1 ) );
	dest=SDL_AllocSurface(SDL_SWSURFACE, max, max, src->format->BitsPerPixel, src->format->Rmask, src->format->Gmask, src->format->Bmask, src->format->Amask );
	if(!dest)
	{SPG_Error("SPG_Rotate could not allocate enough memory");return NULL;}

	SDL_FillRect(dest, NULL, bcol);
	SPG_TransformSurface(src, dest, angle, 1.0f, 1.0f, src->w/2, src->h/2, dest->w/2, dest->h/2, 0);

	return dest;
}

static inline SDL_Surface* SPG_RotateAA(SDL_Surface *src, float angle, Uint32 bcol)
{
   //return SPG_Transform(src, bcol, angle, 1.0, 1.0, SPG_TAA);
   SDL_Surface *dest;

	/* Create the destination surface*/
	int max = (int)( SPG_sqrt( (src->h*src->h/2 + src->w*src->w/2) + 1 ) );
	dest=SDL_AllocSurface(SDL_SWSURFACE, max, max, src->format->BitsPerPixel, src->format->Rmask, src->format->Gmask, src->format->Bmask, src->format->Amask );
	if(!dest)
	{SPG_Error("SPG_RotateAA could not allocate enough memory"); return NULL;}



	SDL_FillRect(dest, NULL, bcol);
	SPG_TransformSurface(src, dest, angle, 1.0f, 1.0f, src->w/2, src->h/2, dest->w/2, dest->h/2, SPG_TAA);

	return dest;
}
static inline SDL_Surface* SPG_Scale(SDL_Surface* src, float xscale, float yscale, Uint32 bcol)
{
    return SPG_Transform(src, bcol, 0, xscale, yscale, 0);
}

static inline SDL_Surface* SPG_ScaleAA(SDL_Surface* src, float xscale, float yscale, Uint32 bcol)
{
    return SPG_Transform(src, bcol, 0, xscale, yscale, SPG_TAA);
}
#else

static inline SDL_Surface* SPG_Rotate(SDL_Surface *src, float angle, Uint32 bcol = 0)
{
   //return SPG_Transform(src, bcol, angle, 1.0, 1.0, 0);
   SDL_Surface *dest;

	/* Create the destination surface*/
	int max = int( SPG_sqrt( (src->h*src->h/2 + src->w*src->w/2) + 1 ) );
	dest=SDL_AllocSurface(SDL_SWSURFACE, max, max, src->format->BitsPerPixel, src->format->Rmask, src->format->Gmask, src->format->Bmask, src->format->Amask );
	if(!dest)
	{SPG_Error("SPG_Rotate could not allocate enough memory");return NULL;}

	SDL_FillRect(dest, NULL, bcol);
	SPG_TransformSurface(src, dest, angle, 1.0f, 1.0f, src->w/2, src->h/2, dest->w/2, dest->h/2, 0);

	return dest;
}

static inline SDL_Surface* SPG_RotateAA(SDL_Surface *src, float angle, Uint32 bcol = 0)
{
   //return SPG_Transform(src, bcol, angle, 1.0, 1.0, SPG_TAA);
   SDL_Surface *dest;

	/* Create the destination surface*/
	int max = int( SPG_sqrt( (src->h*src->h/2 + src->w*src->w/2) + 1 ) );
	dest=SDL_AllocSurface(SDL_SWSURFACE, max, max, src->format->BitsPerPixel, src->format->Rmask, src->format->Gmask, src->format->Bmask, src->format->Amask );
	if(!dest)
	{SPG_Error("SPG_RotateAA could not allocate enough memory"); return NULL;}



	SDL_FillRect(dest, NULL, bcol);
	SPG_TransformSurface(src, dest, angle, 1.0f, 1.0f, src->w/2, src->h/2, dest->w/2, dest->h/2, SPG_TAA);

	return dest;
}
static inline SDL_Surface* SPG_Scale(SDL_Surface *src, float xscale, float yscale, Uint32 bcol = 0)
{
    return SPG_Transform(src, bcol, 0, xscale, yscale, 0);
}

static inline SDL_Surface* SPG_ScaleAA(SDL_Surface *src, float xscale, float yscale, Uint32 bcol = 0)
{
    return SPG_Transform(src, bcol, 0, xscale, yscale, SPG_TAA);
}
#endif




static inline void SPG_SetColorkey(SDL_Surface* surface, Uint32 color)
{
    SDL_SetColorKey(surface, SDL_SRCCOLORKEY, color);
}

static inline int SPG_Clamp(int value, int min, int max)
{
    return ((value < min)? min : (value > max)? max : value);
}

static inline SDL_Surface* SPG_DisplayFormat(SDL_Surface* surf)
{
    SDL_Surface* temp = SDL_DisplayFormat(surf);
    SDL_FreeSurface(surf);
    return temp;
}

static inline SDL_Surface* SPG_DisplayFormatAlpha(SDL_Surface* surf)
{
    SDL_Surface* temp = SDL_DisplayFormatAlpha(surf);
    SDL_FreeSurface(surf);
    return temp;
}

static inline SDL_Surface* SPG_CreateAlphaSurfaceFrom(void* linearArray, Uint16 width, Uint16 height, SDL_PixelFormat* format)
{
    SDL_Surface* result = SDL_CreateRGBSurfaceFrom(linearArray, width, height, 32, width*4, format->Rmask, format->Gmask, format->Bmask, format->Amask);
    SDL_SetAlpha(result, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
    return result;
}

static inline SDL_Rect SPG_GetClip(SDL_Surface* surface)
{
	if (surface)
		return surface->clip_rect;
	else
	{
        SDL_Rect r;
        r.x = 0;
        r.y = 0;
        r.w = 0;
        r.h = 0;
        return r;
	}
}

static inline void SPG_RestoreClip(SDL_Surface* surface)
{
    if(surface)
    {
        surface->clip_rect.x = 0;
        surface->clip_rect.y = 0;
        surface->clip_rect.w = surface->w;
        surface->clip_rect.h = surface->h;
    }
}

static inline SDL_Rect SPG_MakeRect(Sint16 x, Sint16 y, Uint16 w, Uint16 h)
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    return r;
}

static inline SDL_Rect SPG_MakeRectRelative(Sint16 x, Sint16 y, Sint16 x2, Sint16 y2)
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = x2 - x;
    r.h = y2 - y;
    return r;
}

static inline SDL_Surface* SPG_CreateAlphaSurface(Uint32 flags, Uint16 width, Uint16 height)
{
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_Surface* result = SDL_CreateRGBSurface(flags,width,height,32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    #else
        SDL_Surface* result = SDL_CreateRGBSurface(flags,width,height,32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
    #endif
    SDL_SetAlpha(result, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
	return result;
}


static inline Uint32 SPG_MixAlpha(SDL_Surface *surface, Uint32 color, Uint8 alpha)
{
    SDL_PixelFormat* format = surface->format;
    return (color & (format->Rmask | format->Gmask | format->Bmask)) | (alpha << format->Ashift);
}

static inline SDL_Surface* SPG_CopySurface(SDL_Surface* src)
{
	return SDL_ConvertSurface(src, src->format, SDL_SWSURFACE);
}



static inline void SPG_SetSurfaceAlpha(SDL_Surface* surface, Uint8 alpha)
{
    surface->format->alpha = alpha;
}

static inline void SPG_Fill(SDL_Surface* surface, Uint32 color)
{
	SDL_FillRect(surface, NULL, color);
}

static inline void SPG_FillAlpha(SDL_Surface* surface, Uint32 color, Uint8 alpha)
{
	SDL_FillRect(surface, NULL, SPG_MixAlpha(surface, color, alpha));
}

static inline SDL_Color SPG_FillPaletteEntry(Uint8 R, Uint8 G, Uint8 B)
{
   SDL_Color color;

   color.r = R;
   color.g = G;
   color.b = B;

   return color;
}

static inline SDL_Color SPG_GetRGB(SDL_Surface *Surface, Uint32 Color)
{
	SDL_Color rgb;
	SDL_GetRGB(Color, Surface->format, &(rgb.r), &(rgb.g), &(rgb.b));

	return(rgb);
}


static inline SDL_Color SPG_GetColor(SDL_Surface* Surface, Uint32 Color)
{
	SDL_Color rgb;
	SDL_GetRGB(Color, Surface->format, &(rgb.r), &(rgb.g), &(rgb.b));
	return rgb;
}

static inline SDL_Color SPG_ToColor(Uint8 R, Uint8 G, Uint8 B)
{
   SDL_Color color;
   color.r = R;
   color.g = G;
   color.b = B;
   return color;
}


static inline void SPG_BlockWrite8(SDL_Surface* Surface, Uint8* block, Sint16 y)
{
	memcpy(	(Uint8 *)Surface->pixels + y*Surface->pitch, block, sizeof(Uint8)*Surface->w );
}
static inline void SPG_BlockWrite16(SDL_Surface* Surface, Uint16* block, Sint16 y)
{
	memcpy(	(Uint16 *)Surface->pixels + y*Surface->pitch/2, block, sizeof(Uint16)*Surface->w );
}
static inline void SPG_BlockWrite32(SDL_Surface* Surface, Uint32* block, Sint16 y)
{
	memcpy(	(Uint32 *)Surface->pixels + y*Surface->pitch/4, block, sizeof(Uint32)*Surface->w );
}

static inline void SPG_BlockRead8(SDL_Surface* Surface, Uint8* block, Sint16 y)
{
	memcpy(	block,(Uint8 *)Surface->pixels + y*Surface->pitch, sizeof(Uint8)*Surface->w );
}
static inline void SPG_BlockRead16(SDL_Surface* Surface, Uint16* block, Sint16 y)
{
	memcpy(	block,(Uint16 *)Surface->pixels + y*Surface->pitch/2, sizeof(Uint16)*Surface->w );
}
static inline void SPG_BlockRead32(SDL_Surface* Surface, Uint32* block, Sint16 y)
{
	memcpy(	block,(Uint32 *)Surface->pixels + y*Surface->pitch/4, sizeof(Uint32)*Surface->w );
}



static inline SPG_Point SPG_MakePoint(Sint16 x, Sint16 y)
{
    SPG_Point p;
    p.x = x;
    p.y = y;
    return p;
}

static inline void SPG_Draw(SDL_Surface* source, SDL_Surface* dest, Sint16 x, Sint16 y)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_BlitSurface(source, NULL, dest, &rect);
}

static inline void SPG_DrawBlit(SDL_Surface* source, SDL_Surface* dest, Sint16 x, Sint16 y)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SPG_Blit(source, NULL, dest, &rect);
}













#ifdef _SPG_USE_POINTS
#ifdef _SPG_C_ONLY
#else
//inline




#endif
#endif









#endif



