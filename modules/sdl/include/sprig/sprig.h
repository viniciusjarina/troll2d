/*
    SPriG - SDL Primitive Generator
    by Jonathan Dearborn

    (consolidated header file for simplicity and ease of installation...)
*/

#ifndef _SPRIG_H__
#define _SPRIG_H__


#define SPG_VER 0.941  // use this if you need to check for deprecated functionality
#define _SPG_C_AND_CPP  // undef this if you're compiling for C
//#define _SPG_USE_EXTENDED  // Build Sprig with this to add some extra functions
#define _SPG_USE_POINTS  // use inline functions for calls using SPG_Point
#define _SPG_DEFINE_PI  // Allow defines of pi variations
#define SPG_MAX_ERRORS 40  // Max size of error message stack

/*
*	SDL Graphics Extension
*
*	Started 990815
*
*	License: LGPL v2+ (see the file LICENSE)
*	(c)1999-2003 Anders Lindström
*/

/*********************************************************************
 *  This library is free software; you can redistribute it and/or    *
 *  modify it under the terms of the GNU Library General Public      *
 *  License as published by the Free Software Foundation; either     *
 *  version 2 of the License, or (at your option) any later version. *
 *********************************************************************/

#include "SDL.h"

/*
*  C compatibility
*  Thanks to Ohbayashi Ippei (ohai@kmc.gr.jp) for this clever hack!
*/
#ifdef _SPG_C_AND_CPP
	#ifdef __cplusplus
		#define _SPG_CPP           /* use extern "C" on base functions */
	#else
		#define _SPG_C_ONLY       /* remove overloaded functions */
	#endif
#else
    #define _SPG_C_ONLY
#endif

#ifdef _SPG_DEFINE_PI
    #ifndef PI
        #define PI    3.14159265
    #endif
    #ifndef PI_2
        #define PI_2  1.57079633
    #endif
    #ifndef PI_4
        #define PI_4  0.785398163
    #endif
    #ifndef PI2
        #define PI2   6.28318531
    #endif
    #ifndef PI3_2
        #define PI3_2 4.71238898
    #endif
    #ifndef DEGPERRAD
        #define DEGPERRAD 57.2957795
    #endif
    #ifndef RADPERDEG
        #define RADPERDEG 0.0174532925
    #endif
#endif


/*
*  Bit flags
*/
#define SPG_FLAG0 0
#define SPG_FLAG1 0x01
#define SPG_FLAG2 0x02
#define SPG_FLAG3 0x04
#define SPG_FLAG4 0x08
#define SPG_FLAG5 0x10
#define SPG_FLAG6 0x20
#define SPG_FLAG7 0x40
#define SPG_FLAG8 0x80


/*
*  Define the right alpha values
*  (they were flipped in SDL 1.1.5+)
*  That means alpha is now a measure of opacity
*/
#ifndef SDL_ALPHA_OPAQUE
	#define SDL_ALPHA_OPAQUE 255
#endif
#ifndef SDL_ALPHA_TRANSPARENT
	#define SDL_ALPHA_TRANSPARENT 0
#endif


/*
*  Older versions of SDL don't have SDL_VERSIONNUM
*/
#ifndef SDL_VERSIONNUM
	#define SDL_VERSIONNUM(X, Y, Z)      \
		(X)*1000 + (Y)*100 + (Z)
#endif


/*
*  Older versions of SDL don't have SDL_CreateRGBSurface
*/
#ifndef SDL_AllocSurface
	#define SDL_CreateRGBSurface  SDL_AllocSurface
#endif


/*
*  Macro to get clipping
*/
#if SDL_VERSIONNUM(SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL) >= \
    SDL_VERSIONNUM(1, 1, 5)
	#define SPG_clip_xmin(pnt) pnt->clip_rect.x
	#define SPG_clip_xmax(pnt) pnt->clip_rect.x + pnt->clip_rect.w-1
	#define SPG_clip_ymin(pnt) pnt->clip_rect.y
	#define SPG_clip_ymax(pnt) pnt->clip_rect.y + pnt->clip_rect.h-1
#else
	#define SPG_clip_xmin(pnt) pnt->clip_minx
	#define SPG_clip_xmax(pnt) pnt->clip_maxx
	#define SPG_clip_ymin(pnt) pnt->clip_miny
	#define SPG_clip_ymax(pnt) pnt->clip_maxy
#endif


/*
*  We need to use alpha sometimes but older versions of SDL don't have
*  alpha support.
*/
#if SDL_VERSIONNUM(SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL) >= \
    SDL_VERSIONNUM(1, 1, 5)
	#define SPG_MapRGBA SDL_MapRGBA
	#define SPG_GetRGBA SDL_GetRGBA
#else
	#define SPG_MapRGBA(fmt, r, g, b, a) SDL_MapRGB(fmt, r, g, b)
	#define SPG_GetRGBA(pixel, fmt, r, g, b, a) SDL_GetRGB(pixel, fmt, r, g, b)
#endif


/*
*  Some compilers use a special export keyword
*  Thanks to Seung Chan Lim (limsc@maya.com or slim@djslim.com) to pointing this out
*  (From SDL)
*/
#ifndef DECLSPEC
	#ifdef __BEOS__
		#if defined(__GNUC__)
			#define DECLSPEC 
		#else
			#define DECLSPEC 
		#endif
	#else
		#ifdef WIN32
			#define DECLSPEC 
		#else
			#define DECLSPEC
		#endif
	#endif
#endif

typedef struct SPG_Point
{
    Sint16 x;
    Sint16 y;
}SPG_Point;


#define SPG_bool Uint8

extern SPG_bool _SPG_lock;

// default = 0
#define SPG_DEST_ALPHA 0
#define SPG_SRC_ALPHA 1
#define SPG_COMBINE_ALPHA 2
#define SPG_COPY_NO_ALPHA 3
#define SPG_COPY_SRC_ALPHA 4
#define SPG_COPY_DEST_ALPHA 5
#define SPG_COPY_COMBINE_ALPHA 6
#define SPG_COPY_ALPHA_ONLY 7
#define SPG_COMBINE_ALPHA_ONLY 8

// Alternate names:
#define SPG_SRC_MASK 4
#define SPG_DEST_MASK 5


/* Transformation flags */
#define SPG_NONE SPG_FLAG0
#define SPG_TAA SPG_FLAG1
#define SPG_TSAFE SPG_FLAG2
#define SPG_TTMAP SPG_FLAG3
#define SPG_TCOLORKEY SPG_FLAG4


#ifdef _SPG_CPP // BOTH C and C++
extern "C" {
#endif


// MISC
DECLSPEC void SPG_Lock(SPG_bool enable);
DECLSPEC SPG_bool SPG_GetLock();
DECLSPEC void SPG_PushBlend(Uint8 state);
DECLSPEC Uint8 SPG_PopBlend();
DECLSPEC Uint8 SPG_GetBlend();
DECLSPEC void SPG_PushAA(SPG_bool state);
DECLSPEC SPG_bool SPG_PopAA();
DECLSPEC SPG_bool SPG_GetAA();
DECLSPEC void SPG_PushSurfaceAlpha(SPG_bool state);
DECLSPEC SPG_bool SPG_PopSurfaceAlpha();
DECLSPEC SPG_bool SPG_GetSurfaceAlpha();
DECLSPEC void SPG_Error(const char* err);
DECLSPEC char* SPG_GetError();
DECLSPEC Uint16 SPG_NumErrors();
DECLSPEC void SPG_EnableErrors(SPG_bool enable);


// PALETTE

DECLSPEC void SPG_Fader(SDL_Surface *surface, Uint8 sR,Uint8 sG,Uint8 sB, Uint8 dR,Uint8 dG,Uint8 dB,Uint32 *ctab,int start, int stop);
DECLSPEC void SPG_AlphaFader(SDL_Surface *surface, Uint8 sR,Uint8 sG,Uint8 sB,Uint8 sA, Uint8 dR,Uint8 dG,Uint8 dB,Uint8 dA, Uint32 *ctab,int start, int stop);
DECLSPEC void SPG_SetupRainbowPalette(SDL_Surface *surface,Uint32 *ctab,Uint8 intensity, int start, int stop);
DECLSPEC void SPG_SetupBWPalette(SDL_Surface *surface,Uint32 *ctab,int start, int stop);

// SURFACE

DECLSPEC int SPG_Blit(SDL_Surface *Src, SDL_Rect* srcRect, SDL_Surface *Dest, SDL_Rect* destRect);
DECLSPEC void SPG_SetBlit(void (*blitfn)(SDL_Surface*, SDL_Rect*, SDL_Surface*, SDL_Rect*));
DECLSPEC void (*SPG_GetBlit())(SDL_Surface*, SDL_Rect*, SDL_Surface*, SDL_Rect*);
DECLSPEC SDL_Rect SPG_TransformSurface(SDL_Surface *src, SDL_Surface *dst, float angle, float xscale, float yscale, Uint16 px, Uint16 py, Uint16 qx, Uint16 qy, Uint8 flags);
DECLSPEC SDL_Surface* SPG_Transform(SDL_Surface *src, Uint32 bcol, float angle, float xscale, float yscale, Uint8 flags);


DECLSPEC Uint32 SPG_GetPixel(SDL_Surface *surface, Sint16 x, Sint16 y);


// DRAWING

DECLSPEC void SPG_FloodFill(SDL_Surface *dst, Sint16 x, Sint16 y, Uint32 color);

DECLSPEC void SPG_Pixel(SDL_Surface *surface, Sint16 x, Sint16 y, Uint32 color);
DECLSPEC void SPG_PixelBlend(SDL_Surface *surface, Sint16 x, Sint16 y, Uint32 color, Uint8 alpha);
DECLSPEC void SPG_PixelPattern(SDL_Surface *surface, SDL_Rect target, SPG_bool* pattern, Uint32* colors);
DECLSPEC void SPG_PixelPatternBlend(SDL_Surface *surface, SDL_Rect target, SPG_bool* pattern, Uint32* colors, Uint8* pixelAlpha);


// PRIMITIVES

DECLSPEC void SPG_LineH(SDL_Surface *surface, Sint16 x1, Sint16 y, Sint16 x2, Uint32 Color);
DECLSPEC void SPG_LineHBlend(SDL_Surface *surface, Sint16 x1, Sint16 y, Sint16 x2, Uint32 color, Uint8 alpha);

DECLSPEC void SPG_LineV(SDL_Surface *surface, Sint16 x, Sint16 y1, Sint16 y2, Uint32 Color);
DECLSPEC void SPG_LineVBlend(SDL_Surface *surface, Sint16 x, Sint16 y1, Sint16 y2, Uint32 color, Uint8 alpha);

DECLSPEC void SPG_LineFn(SDL_Surface *surface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 Color, void Callback(SDL_Surface *Surf, Sint16 X, Sint16 Y, Uint32 Color));
DECLSPEC void SPG_Line(SDL_Surface *surface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 Color);
DECLSPEC void SPG_LineBlend(SDL_Surface *surface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color, Uint8 alpha);

DECLSPEC void SPG_LineFadeFn(SDL_Surface *surface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color1, Uint32 color2, void Callback(SDL_Surface *Surf, Sint16 X, Sint16 Y, Uint32 Color));
DECLSPEC void SPG_LineFade(SDL_Surface *surface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color1, Uint32 color2);
DECLSPEC void SPG_LineFadeBlend(SDL_Surface *surface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color1, Uint8 alpha1, Uint32 color2, Uint8 alpha2);

DECLSPEC void SPG_LineTex(SDL_Surface *dest,Sint16 x1,Sint16 x2,Sint16 y,SDL_Surface *source,Sint16 sx1,Sint16 sy1,Sint16 sx2,Sint16 sy2);


DECLSPEC void SPG_Rect(SDL_Surface *surface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color);
DECLSPEC void SPG_RectBlend(SDL_Surface *surface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color, Uint8 alpha);

DECLSPEC void SPG_RectFilled(SDL_Surface *surface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color);
DECLSPEC void SPG_RectFilledBlend(SDL_Surface *surface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color, Uint8 alpha);


DECLSPEC void SPG_RectRound(SDL_Surface *surface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, float r, Uint32 color);
DECLSPEC void SPG_RectRoundBlend(SDL_Surface *surface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, float r, Uint32 color, Uint8 alpha);

DECLSPEC void SPG_RectRoundFilled(SDL_Surface *surface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, float r, Uint32 color);
DECLSPEC void SPG_RectRoundFilledBlend(SDL_Surface *surface, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, float r, Uint32 color, Uint8 alpha);


DECLSPEC void SPG_EllipseFn(SDL_Surface *surface, Sint16 x, Sint16 y, float rx, float ry, Uint32 color, void Callback(SDL_Surface *Surf, Sint16 X, Sint16 Y, Uint32 Color));
DECLSPEC void SPG_Ellipse(SDL_Surface *surface, Sint16 x, Sint16 y, float rx, float ry, Uint32 color);
DECLSPEC void SPG_EllipseBlend(SDL_Surface *surface, Sint16 x, Sint16 y, float rx, float ry, Uint32 color, Uint8 alpha);

DECLSPEC void SPG_EllipseFilled(SDL_Surface *surface, Sint16 x, Sint16 y, float rx, float ry, Uint32 color);
DECLSPEC void SPG_EllipseFilledBlend(SDL_Surface *surface, Sint16 x, Sint16 y, float rx, float ry, Uint32 color, Uint8 alpha);


DECLSPEC void SPG_CircleFn(SDL_Surface *surface, Sint16 x, Sint16 y, float r, Uint32 color, void Callback(SDL_Surface *Surf, Sint16 X, Sint16 Y, Uint32 Color));
DECLSPEC void SPG_Circle(SDL_Surface *surface, Sint16 x, Sint16 y, float r, Uint32 color);
DECLSPEC void SPG_CircleBlend(SDL_Surface *surface, Sint16 x, Sint16 y, float r, Uint32 color, Uint8 alpha);

DECLSPEC void SPG_CircleFilled(SDL_Surface *surface, Sint16 x, Sint16 y, float r, Uint32 color);
DECLSPEC void SPG_CircleFilledBlend(SDL_Surface *surface, Sint16 x, Sint16 y, float r, Uint32 color, Uint8 alpha);


DECLSPEC void SPG_ArcFn(SDL_Surface* surface, Sint16 cx, Sint16 cy, float radius, float startAngle, float endAngle, Uint32 color, void Callback(SDL_Surface *Surf, Sint16 X, Sint16 Y, Uint32 Color));
DECLSPEC void SPG_Arc(SDL_Surface* surface, Sint16 x, Sint16 y, float radius, float startAngle, float endAngle, Uint32 color);
DECLSPEC void SPG_ArcBlend(SDL_Surface* surface, Sint16 x, Sint16 y, float radius, float startAngle, float endAngle, Uint32 color, Uint8 alpha);

DECLSPEC void SPG_ArcFilled(SDL_Surface* surface, Sint16 cx, Sint16 cy, float radius, float startAngle, float endAngle, Uint32 color);
DECLSPEC void SPG_ArcFilledBlend(SDL_Surface* surface, Sint16 cx, Sint16 cy, float radius, float startAngle, float endAngle, Uint32 color, Uint8 alpha);


DECLSPEC void SPG_Bezier(SDL_Surface *surface, Sint16 startX, Sint16 startY, Sint16 cx1, Sint16 cy1, Sint16 cx2, Sint16 cy2, Sint16 endX, Sint16 endY, Uint8 quality, Uint32 color);
DECLSPEC void SPG_BezierBlend(SDL_Surface *surface, Sint16 startX, Sint16 startY, Sint16 cx1, Sint16 cy1, Sint16 cx2, Sint16 cy2, Sint16 endX, Sint16 endY, Uint8 quality, Uint32 color, Uint8 alpha);


// POLYGONS

DECLSPEC void SPG_Trigon(SDL_Surface *surface,Sint16 x1,Sint16 y1,Sint16 x2,Sint16 y2,Sint16 x3,Sint16 y3,Uint32 color);
DECLSPEC void SPG_TrigonBlend(SDL_Surface *surface,Sint16 x1,Sint16 y1,Sint16 x2,Sint16 y2,Sint16 x3,Sint16 y3,Uint32 color, Uint8 alpha);

DECLSPEC void SPG_TrigonFilled(SDL_Surface *surface,Sint16 x1,Sint16 y1,Sint16 x2,Sint16 y2,Sint16 x3,Sint16 y3,Uint32 color);
DECLSPEC void SPG_TrigonFilledBlend(SDL_Surface *surface,Sint16 x1,Sint16 y1,Sint16 x2,Sint16 y2,Sint16 x3,Sint16 y3,Uint32 color, Uint8 alpha);

DECLSPEC void SPG_TrigonFade(SDL_Surface *surface,Sint16 x1,Sint16 y1,Sint16 x2,Sint16 y2,Sint16 x3,Sint16 y3,Uint32 color1,Uint32 color2,Uint32 color3);
DECLSPEC void SPG_TrigonTex(SDL_Surface *surface,Sint16 x1,Sint16 y1,Sint16 x2,Sint16 y2,Sint16 x3,Sint16 y3,SDL_Surface *source,Sint16 sx1,Sint16 sy1,Sint16 sx2,Sint16 sy2,Sint16 sx3,Sint16 sy3);


DECLSPEC void SPG_QuadTex(SDL_Surface *surface,Sint16 x1,Sint16 y1,Sint16 x2,Sint16 y2,Sint16 x3,Sint16 y3,Sint16 x4,Sint16 y4,SDL_Surface *source,Sint16 sx1,Sint16 sy1,Sint16 sx2,Sint16 sy2,Sint16 sx3,Sint16 sy3,Sint16 sx4,Sint16 sy4);


DECLSPEC void SPG_Polygon(SDL_Surface *dest, Uint16 n, Sint16* x, Sint16* y, Uint32 color);
DECLSPEC void SPG_PolygonBlend(SDL_Surface *dest, Uint16 n, Sint16* x, Sint16* y, Uint32 color, Uint8 alpha);

DECLSPEC void SPG_PolygonFilled(SDL_Surface *surface, Uint16 n, Sint16 *x, Sint16 *y, Uint32 color);
DECLSPEC void SPG_PolygonFilledBlend(SDL_Surface *surface, Uint16 n, Sint16 *x, Sint16 *y, Uint32 color, Uint8 alpha);

DECLSPEC void SPG_PolygonFade(SDL_Surface *surface, Uint16 n, Sint16 *x, Sint16 *y, Uint32* colors);
DECLSPEC void SPG_PolygonFadeBlend(SDL_Surface *surface, Uint16 n, Sint16 *x, Sint16 *y, Uint32* colors, Uint8 alpha);

DECLSPEC void SPG_RectOR(const SDL_Rect rect1, const SDL_Rect rect2, SDL_Rect* dst_rect);
DECLSPEC SPG_bool SPG_RectAND(const SDL_Rect A, const SDL_Rect B, SDL_Rect* intersection);
DECLSPEC void SPG_SetClip(SDL_Surface *surface, const SDL_Rect rect);

#ifdef _SPG_CPP
}  // extern "C"
#endif




// Include all convenience calls
#include "sprig_inline.h"

// Include extended calls
#ifdef _SPG_USE_EXTENDED


    #ifdef _SPG_CPP // BOTH C and C++
    extern "C" {
    #endif


        DECLSPEC void SPG_FloodFill8(SDL_Surface* dest, Sint16 x, Sint16 y, Uint32 newColor);


    #ifdef _SPG_CPP // BOTH C and C++
    }  // extern "C"
    #endif


#endif




#endif /* _SPRIG_H__ */

