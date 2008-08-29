/*
    SPriG - SDL Primitive Generator
    by Jonathan Dearborn
*/



/*
*	SDL Graphics Extension
*	Pixel, surface and color functions
*
*	Started 990815 (split from sge_draw 010611)
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

/*
*  Some of this code is taken from the "Introduction to SDL" and
*  John Garrison's PowerPak	
*/

#include "sprig.h"
#ifdef _SPG_C_ONLY
    #include <math.h>
    #include <string.h>
    #include <stdarg.h>
#else
    #include <cmath>
    #include <string>
    #include <cstdarg>
#endif


/* Global used for SPG_Lock */
SPG_bool _SPG_lock = 1;
void (*_SPG_BlitFunc)(SDL_Surface*, SDL_Rect*, SDL_Surface*, SDL_Rect*) = NULL;


struct _uint8_node
{
    Uint8 datum;
    struct _uint8_node* next;
};

struct _bool_node
{
    SPG_bool datum;
    struct _bool_node* next;
};

struct _string_node
{
    char* datum;
    struct _string_node* next;
};


struct _uint8_node* _SPG_blend_state = NULL;
struct _bool_node* _SPG_AA_state = NULL;
struct _bool_node* _SPG_blit_surface_alpha_state = NULL;

struct _string_node* _spg_errors = NULL;
struct _string_node* _spg_errors_tail = NULL;
Uint16 _spg_numerrors = 0;
SPG_bool _spg_useerrors = 0;

void _SetPixel8(SDL_Surface *surface, Sint16 x, Sint16 y, Uint32 color);
void _SetPixel16(SDL_Surface *surface, Sint16 x, Sint16 y, Uint32 color);
void _SetPixel24(SDL_Surface *surface, Sint16 x, Sint16 y, Uint32 color);
void _SetPixel32(SDL_Surface *surface, Sint16 x, Sint16 y, Uint32 color);
void _SetPixelX(SDL_Surface *dest,Sint16 x,Sint16 y,Uint32 color);


/**********************************************************************************/
/**                            Misc. functions                                   **/
/**********************************************************************************/


void SPG_Lock(SPG_bool enable)
{ _SPG_lock = enable;}

SPG_bool SPG_GetLock()
{ return _SPG_lock;}

void SPG_PushBlend(Uint8 state)
{
    struct _uint8_node* node = (struct _uint8_node*)malloc(sizeof(struct _uint8_node));
    node->datum = state;
    node->next = _SPG_blend_state;
    _SPG_blend_state = node;
}
Uint8 SPG_PopBlend()
{
    if(_SPG_blend_state == NULL)
    {
        if(_spg_useerrors)
            SPG_Error("SPG_PopBlend popped an empty stack!");
        return 0;
    }
    struct _uint8_node* temp = _SPG_blend_state;
    Uint8 result = _SPG_blend_state->datum;
    _SPG_blend_state = _SPG_blend_state->next;
    free(temp);
    return result;
}
Uint8 SPG_GetBlend()
{
    if(_SPG_blend_state == NULL)
    {
        // Without initialization, this overfills the stack.
        //if(_spg_useerrors)
        //SPG_Error("SPG_GetBlend checked an empty stack!");
        return 0;
    }
    return _SPG_blend_state->datum;
}

void SPG_PushAA(SPG_bool state)
{
    struct _bool_node* node = (struct _bool_node*)malloc(sizeof(struct _bool_node));
    node->datum = state;
    node->next = _SPG_AA_state;
    _SPG_AA_state = node;
}
SPG_bool SPG_PopAA()
{
    if(_SPG_AA_state == NULL)
    {
        if(_spg_useerrors)
            SPG_Error("SPG_PopAA popped an empty stack!");
        return 0;
    }
    struct _bool_node* temp = _SPG_AA_state;
    SPG_bool result = _SPG_AA_state->datum;
    _SPG_AA_state = _SPG_AA_state->next;
    free(temp);
    return result;
}
SPG_bool SPG_GetAA()
{
    if(_SPG_AA_state == NULL)
    {
        // Without initialization, this overfills the stack.
        //if(_spg_useerrors)
        //SPG_Error("SPG_GetAA checked an empty stack!");
        return 0;
    }
    return _SPG_AA_state->datum;
}

void SPG_PushSurfaceAlpha(SPG_bool state)
{
    struct _bool_node* node = (struct _bool_node*)malloc(sizeof(struct _bool_node));
    node->datum = state;
    node->next = _SPG_blit_surface_alpha_state;
    _SPG_blit_surface_alpha_state = node;
}
SPG_bool SPG_PopSurfaceAlpha()
{
    if(_SPG_blit_surface_alpha_state == NULL)
    {
        if(_spg_useerrors)
            SPG_Error("SPG_PopSurfaceAlpha popped an empty stack!");
        return 0;
    }
    struct _bool_node* temp = _SPG_blit_surface_alpha_state;
    SPG_bool result = _SPG_blit_surface_alpha_state->datum;
    _SPG_blit_surface_alpha_state = _SPG_blit_surface_alpha_state->next;
    free(temp);
    return result;
}
SPG_bool SPG_GetSurfaceAlpha()
{
    if(_SPG_blit_surface_alpha_state == NULL)
    {
        // Without initialization, this overfills the stack.
        //if(_spg_useerrors)
        //SPG_Error("SPG_GetSurfaceAlpha checked an empty stack!");
        return 1;
    }
    return _SPG_blit_surface_alpha_state->datum;
}


void SPG_Error(const char* err)
{
    if(err == NULL || _spg_numerrors >= SPG_MAX_ERRORS)
        return;
    struct _string_node* node = (struct _string_node*)malloc(sizeof(struct _string_node));
    node->datum = (char*)malloc(strlen(err)+20);
    sprintf(node->datum, "%s at time %ums\0", err, SDL_GetTicks());
    // push to front
    //node->next = _spg_errors;
    //_spg_errors = node;
    
    // push to back
    node->next = NULL;
    if(_spg_errors == NULL || _spg_errors_tail == NULL)
        _spg_errors = node;
    else
        _spg_errors_tail->next = node;
    _spg_errors_tail = node;
    
    _spg_numerrors++;
}

char* SPG_GetError()
{
    if(_spg_numerrors == 0 || _spg_errors == NULL)
        return NULL;
    
    struct _string_node* temp = _spg_errors;
    char* result = _spg_errors->datum;
    _spg_errors = _spg_errors->next;
    _spg_numerrors--;
    free(temp);
    return result;
}

Uint16 SPG_NumErrors()
{
    return _spg_numerrors;
}

void SPG_EnableErrors(SPG_bool enable)
{
    _spg_useerrors = enable;
}



/*
*  Get the smallest bounding box from two (SDL_Rect) rectangles
*/
void SPG_RectOR(const SDL_Rect rect1, const SDL_Rect rect2, SDL_Rect* dst_rect)
{
    if(dst_rect == NULL)
        return;
    
	dst_rect->x = (rect1.x < rect2.x)? rect1.x : rect2.x;
	dst_rect->y = (rect1.y < rect2.y)? rect1.y : rect2.y;
	dst_rect->w = (rect1.x + rect1.w > rect2.x + rect2.w)? rect1.x + rect1.w - dst_rect->x : rect2.x + rect2.w - dst_rect->x;
	dst_rect->h = (rect1.y + rect1.h > rect2.y + rect2.h)? rect1.y + rect1.h - dst_rect->y : rect2.y + rect2.h - dst_rect->y;
}

// Adapted from SDL_IntersectRect
SPG_bool SPG_RectAND(const SDL_Rect A, const SDL_Rect B, SDL_Rect* intersection)
{
    int resX, resY, resW, resH;
	int Amin, Amax, Bmin, Bmax;

	// Horizontal intersection
	Amin = A.x;
	Amax = Amin + A.w;
	Bmin = B.x;
	Bmax = Bmin + B.w;
	if(Bmin > Amin)
	        Amin = Bmin;
	resX = Amin;
	if(Bmax < Amax)
	        Amax = Bmax;
	resW = Amax - Amin > 0 ? Amax - Amin : 0;

	// Vertical intersection
	Amin = A.y;
	Amax = Amin + A.h;
	Bmin = B.y;
	Bmax = Bmin + B.h;
	if(Bmin > Amin)
	        Amin = Bmin;
	resY = Amin;
	if(Bmax < Amax)
	        Amax = Bmax;
	resH = Amax - Amin > 0 ? Amax - Amin : 0;
    
    if(intersection != NULL)
    {
        intersection->x = resX;
        intersection->y = resY;
        intersection->w = resW;
        intersection->h = resH;
    }
    
	return (resW && resH);
}


// Adapted from SDL_SetClipRect
void SPG_SetClip(SDL_Surface *surface, const SDL_Rect rect)
{
	int Amin, Amax, Bmax;
	
	if (!surface)
		return;
	
	// Set the clipping rectangle with the intersection of 
	//   the given rect with the full surface.
	// Horizontal intersection
	Amin = rect.x;
	Amax = Amin + rect.w;
	Bmax = surface->w;
	if(Amin < 0)
	        Amin = 0;
	surface->clip_rect.x = Amin;
	if(Bmax < Amax)
	        Amax = Bmax;
	surface->clip_rect.w = Amax - Amin > 0 ? Amax - Amin : 0;

	// Vertical intersection
	Amin = rect.y;
	Amax = Amin + rect.h;
	Bmax = surface->h;
	if(Amin < 0)
	        Amin = 0;
	surface->clip_rect.y = Amin;
	if(Bmax < Amax)
	        Amax = Bmax;
	surface->clip_rect.h = Amax - Amin > 0 ? Amax - Amin : 0;
}










/**********************************************************************************/
/**                            Pixel functions                                   **/
/**********************************************************************************/

//==================================================================================
// Fast set pixel
//==================================================================================
void _SetPixel(SDL_Surface *surface, Sint16 x, Sint16 y, Uint32 color)
{
	if(x>=SPG_clip_xmin(surface) && x<=SPG_clip_xmax(surface) && y>=SPG_clip_ymin(surface) && y<=SPG_clip_ymax(surface)){
		switch (surface->format->BytesPerPixel) {
			case 1: { /* Assuming 8-bpp */
				*((Uint8 *)surface->pixels + y*surface->pitch + x) = color;
			}
			break;

			case 2: { /* Probably 15-bpp or 16-bpp */
				*((Uint16 *)surface->pixels + y*surface->pitch/2 + x) = color;
			}
			break;

			case 3: { /* Slow 24-bpp mode, usually not used */
				Uint8 *pix = (Uint8 *)surface->pixels + y * surface->pitch + x*3;

  				/* Gack - slow, but endian correct */
				*(pix+surface->format->Rshift/8) = color>>surface->format->Rshift;
  				*(pix+surface->format->Gshift/8) = color>>surface->format->Gshift;
  				*(pix+surface->format->Bshift/8) = color>>surface->format->Bshift;
				*(pix+surface->format->Ashift/8) = color>>surface->format->Ashift;
			}
			break;

			case 4: { /* Probably 32-bpp */
				*((Uint32 *)surface->pixels + y*surface->pitch/4 + x) = color;
			}
			break;
		}
	}

}


//==================================================================================
// Fast set pixel (RGB)
//==================================================================================
void _SetPixelRGB(SDL_Surface *surface, Sint16 x, Sint16 y, Uint8 R, Uint8 G, Uint8 B)
{
	_SetPixel(surface,x,y, SDL_MapRGB(surface->format, R, G, B));
}


//==================================================================================
// Fastest set pixel functions (don't mess up indata, thank you)
//==================================================================================
void _SetPixel8(SDL_Surface *surface, Sint16 x, Sint16 y, Uint32 color)
{
	*((Uint8 *)surface->pixels + y*surface->pitch + x) = color;
}
void _SetPixel16(SDL_Surface *surface, Sint16 x, Sint16 y, Uint32 color)
{
	*((Uint16 *)surface->pixels + y*surface->pitch/2 + x) = color;
}
void _SetPixel24(SDL_Surface *surface, Sint16 x, Sint16 y, Uint32 color)
{
	Uint8 *pix = (Uint8 *)surface->pixels + y * surface->pitch + x*3;

  	/* Gack - slow, but endian correct */
	*(pix+surface->format->Rshift/8) = color>>surface->format->Rshift;
  	*(pix+surface->format->Gshift/8) = color>>surface->format->Gshift;
  	*(pix+surface->format->Bshift/8) = color>>surface->format->Bshift;
	*(pix+surface->format->Ashift/8) = color>>surface->format->Ashift;
}
void _SetPixel32(SDL_Surface *surface, Sint16 x, Sint16 y, Uint32 color)
{
	*((Uint32 *)surface->pixels + y*surface->pitch/4 + x) = color;
}
void _SetPixelX(SDL_Surface *dest,Sint16 x,Sint16 y,Uint32 color)
{
	switch ( dest->format->BytesPerPixel ) {
	case 1:
		*((Uint8 *)dest->pixels + y*dest->pitch + x) = color;
		break;
	case 2:
		*((Uint16 *)dest->pixels + y*dest->pitch/2 + x) = color;
		break;
	case 3:
		_SetPixel24(dest,x,y,color);
		break;
	case 4:
		*((Uint32 *)dest->pixels + y*dest->pitch/4 + x) = color;
		break;
	}
}



//==================================================================================
// Safe set pixel
//==================================================================================
void SPG_Pixel(SDL_Surface *surface, Sint16 x, Sint16 y, Uint32 color)
{

	if ( SDL_MUSTLOCK(surface) && _SPG_lock ) {
		if ( SDL_LockSurface(surface) < 0 ) {
            if(_spg_useerrors)
                SPG_Error("SPG_Pixel could not lock surface");
			return;
		}
	}

	_SetPixel(surface, x, y, color);

	if ( SDL_MUSTLOCK(surface) && _SPG_lock ) {
		SDL_UnlockSurface(surface);
	}
}



//==================================================================================
// Calculate y pitch offset
// (the y pitch offset is constant for the same y coord and surface)
//==================================================================================
Sint32 SPG_CalcYPitch(SDL_Surface *dest,Sint16 y)
{
	if(y>=SPG_clip_ymin(dest) && y<=SPG_clip_ymax(dest)){
		switch ( dest->format->BytesPerPixel ) {
		case 1:
			return y*dest->pitch;
			break;
		case 2:
			return y*dest->pitch/2;
			break;
		case 3:
			return y*dest->pitch;
			break;
		case 4:
			return y*dest->pitch/4;
			break;
		}
	}
	
	return -1;
}


//==================================================================================
// Set pixel with precalculated y pitch offset
//==================================================================================
void SPG_pSetPixel(SDL_Surface *surface, Sint16 x, Sint32 ypitch, Uint32 color)
{
	if(x>=SPG_clip_xmin(surface) && x<=SPG_clip_xmax(surface) && ypitch>=0){
		switch (surface->format->BytesPerPixel) {
			case 1: { /* Assuming 8-bpp */
				*((Uint8 *)surface->pixels + ypitch + x) = color;
			}
			break;

			case 2: { /* Probably 15-bpp or 16-bpp */
				*((Uint16 *)surface->pixels + ypitch + x) = color;
			}
			break;

			case 3: { /* Slow 24-bpp mode, usually not used */
  				/* Gack - slow, but endian correct */
  				Uint8 *pix = (Uint8 *)surface->pixels + ypitch + x*3;

				*(pix+surface->format->Rshift/8) = color>>surface->format->Rshift;
  				*(pix+surface->format->Gshift/8) = color>>surface->format->Gshift;
  				*(pix+surface->format->Bshift/8) = color>>surface->format->Bshift;
				*(pix+surface->format->Ashift/8) = color>>surface->format->Ashift;
			}
			break;

			case 4: { /* Probably 32-bpp */
				*((Uint32 *)surface->pixels + ypitch + x) = color;
			}
			break;
		}
	}
}


//==================================================================================
// Get pixel
//==================================================================================
Uint32 SPG_GetPixel(SDL_Surface *surface, Sint16 x, Sint16 y)
{
	if(x<0 || x>=surface->w || y<0 || y>=surface->h)
	{
	    if(_spg_useerrors)
            SPG_Error("SPG_GetPixel was used out of the surface bounds");
		return 0;
	}

	switch (surface->format->BytesPerPixel) {
		case 1: { /* Assuming 8-bpp */
			return *((Uint8 *)surface->pixels + y*surface->pitch + x);
		}
		break;

		case 2: { /* Probably 15-bpp or 16-bpp */
			return *((Uint16 *)surface->pixels + y*surface->pitch/2 + x);
		}
		break;

		case 3: { /* Slow 24-bpp mode, usually not used */
			Uint8 *pix;
			int shift;
			Uint32 color=0;

			pix = (Uint8 *)surface->pixels + y * surface->pitch + x*3;
			shift = surface->format->Rshift;
			color = *(pix+shift/8)<<shift;
			shift = surface->format->Gshift;
			color|= *(pix+shift/8)<<shift;
			shift = surface->format->Bshift;
			color|= *(pix+shift/8)<<shift;
			shift = surface->format->Ashift;
			color|= *(pix+shift/8)<<shift;
			return color;
		}
		break;

		case 4: { /* Probably 32-bpp */
			return *((Uint32 *)surface->pixels + y*surface->pitch/4 + x);
		}
		break;
	}
	return 0;
}


//==================================================================================
// Put pixel with alpha blending
//==================================================================================
void _PutPixelAlpha(SDL_Surface *surface, Sint16 x, Sint16 y, Uint32 color, Uint8 alpha)
{
	if(x>=SPG_clip_xmin(surface) && x<=SPG_clip_xmax(surface) && y>=SPG_clip_ymin(surface) && y<=SPG_clip_ymax(surface)){
		Uint32 Rmask = surface->format->Rmask, Gmask = surface->format->Gmask, Bmask = surface->format->Bmask, Amask = surface->format->Amask;
		Uint32 R,G,B,A=SDL_ALPHA_OPAQUE;
	Uint32* pixel;
		switch (surface->format->BytesPerPixel) {
			case 1: { /* Assuming 8-bpp */
			    
					Uint8 *pixel = (Uint8 *)surface->pixels + y*surface->pitch + x;
					
					Uint8 dR = surface->format->palette->colors[*pixel].r;
					Uint8 dG = surface->format->palette->colors[*pixel].g;
					Uint8 dB = surface->format->palette->colors[*pixel].b;
					Uint8 sR = surface->format->palette->colors[color].r;
					Uint8 sG = surface->format->palette->colors[color].g;
					Uint8 sB = surface->format->palette->colors[color].b;
					
                    dR = dR + ((sR-dR)*alpha >> 8);
                    dG = dG + ((sG-dG)*alpha >> 8);
                    dB = dB + ((sB-dB)*alpha >> 8);
				
					*pixel = SDL_MapRGB(surface->format, dR, dG, dB);
					
			}
			break;

			case 2: { /* Probably 15-bpp or 16-bpp */		
			    
					Uint16 *pixel = (Uint16 *)surface->pixels + y*surface->pitch/2 + x;
					Uint32 dc = *pixel;
				
					R = ((dc & Rmask) + (( (color & Rmask) - (dc & Rmask) ) * alpha >> 8)) & Rmask;
					G = ((dc & Gmask) + (( (color & Gmask) - (dc & Gmask) ) * alpha >> 8)) & Gmask;
					B = ((dc & Bmask) + (( (color & Bmask) - (dc & Bmask) ) * alpha >> 8)) & Bmask;
					if( Amask )
						A = ((dc & Amask) + (( (color & Amask) - (dc & Amask) ) * alpha >> 8)) & Amask;

					*pixel= R | G | B | A;
					
			}
			break;

			case 3: { /* Slow 24-bpp mode, usually not used */
				Uint8 *pix = (Uint8 *)surface->pixels + y * surface->pitch + x*3;
				Uint8 rshift8=surface->format->Rshift/8;
				Uint8 gshift8=surface->format->Gshift/8;
				Uint8 bshift8=surface->format->Bshift/8;
				Uint8 ashift8=surface->format->Ashift/8;
				
				
				
					Uint8 dR, dG, dB, dA=0;
					Uint8 sR, sG, sB, sA=0;
					
					pix = (Uint8 *)surface->pixels + y * surface->pitch + x*3;
					
					dR = *((pix)+rshift8); 
            		dG = *((pix)+gshift8);
            		dB = *((pix)+bshift8);
					dA = *((pix)+ashift8);
					
					sR = (color>>surface->format->Rshift)&0xff;
					sG = (color>>surface->format->Gshift)&0xff;
					sB = (color>>surface->format->Bshift)&0xff;
					sA = (color>>surface->format->Ashift)&0xff;
					
					dR = dR + ((sR-dR)*alpha >> 8);
					dG = dG + ((sG-dG)*alpha >> 8);
					dB = dB + ((sB-dB)*alpha >> 8);
					dA = dA + ((sA-dA)*alpha >> 8);

					*((pix)+rshift8) = dR; 
            		*((pix)+gshift8) = dG;
            		*((pix)+bshift8) = dB;
					*((pix)+ashift8) = dA;
					
			}
			break;

			case 4: /* Probably 32-bpp */
                pixel = (Uint32*)surface->pixels + y*surface->pitch/4 + x;
                Uint32 dc = *pixel;
                R = color & Rmask;
                G = color & Gmask;
                B = color & Bmask;
                A = 0;  // keep this as 0 to avoid corruption of non-alpha surfaces
                
                
                switch(SPG_GetBlend())
                {
                    case SPG_COMBINE_ALPHA:  // Blend and combine src and dest alpha
                        if( alpha != SDL_ALPHA_OPAQUE ){
                            R = ((dc & Rmask) + (( R - (dc & Rmask) ) * alpha >> 8)) & Rmask;
                            G = ((dc & Gmask) + (( G - (dc & Gmask) ) * alpha >> 8)) & Gmask;
                            B = ((dc & Bmask) + (( B - (dc & Bmask) ) * alpha >> 8)) & Bmask;
                        }
                        if(Amask)
                            A = ((((dc & Amask) >> surface->format->Ashift) + alpha) >> 1) << surface->format->Ashift;
                        break;
                    case SPG_DEST_ALPHA:  // Blend and keep dest alpha
                        if( alpha != SDL_ALPHA_OPAQUE ){
                            R = ((dc & Rmask) + (( R - (dc & Rmask) ) * alpha >> 8)) & Rmask;
                            G = ((dc & Gmask) + (( G - (dc & Gmask) ) * alpha >> 8)) & Gmask;
                            B = ((dc & Bmask) + (( B - (dc & Bmask) ) * alpha >> 8)) & Bmask;
                        }
                        if(Amask)
                            A = (dc & Amask);
                        break;
                    case SPG_SRC_ALPHA:  // Blend and keep src alpha
                        if( alpha != SDL_ALPHA_OPAQUE ){
                            R = ((dc & Rmask) + (( R - (dc & Rmask) ) * alpha >> 8)) & Rmask;
                            G = ((dc & Gmask) + (( G - (dc & Gmask) ) * alpha >> 8)) & Gmask;
                            B = ((dc & Bmask) + (( B - (dc & Bmask) ) * alpha >> 8)) & Bmask;
                        }
                        if(Amask)
                            A = (alpha << surface->format->Ashift);
                        break;
                    case SPG_COPY_SRC_ALPHA: // Direct copy with src alpha
                        if(Amask)
                            A = (alpha << surface->format->Ashift);
                        break;
                    case SPG_COPY_DEST_ALPHA: // Direct copy with dest alpha
                        if(Amask)
                            A = (dc & Amask);
                        break;
                    case SPG_COPY_COMBINE_ALPHA: // Direct copy with combined alpha
                        if(Amask)
                            A = ((((dc & Amask) >> surface->format->Ashift) + alpha) >> 1) << surface->format->Ashift;
                        break;
                    case SPG_COPY_NO_ALPHA:  // Direct copy, alpha opaque
                        if(Amask)
                            A = (SDL_ALPHA_OPAQUE << surface->format->Ashift);
                        break;
                    case SPG_COPY_ALPHA_ONLY:  // Direct copy of just the alpha
                        R = dc & Rmask;
                        G = dc & Gmask;
                        B = dc & Bmask;
                        if(Amask)
                            A = (alpha << surface->format->Ashift);
                        break;
                    case SPG_COMBINE_ALPHA_ONLY:  // Blend of just the alpha
                        R = dc & Rmask;
                        G = dc & Gmask;
                        B = dc & Bmask;
                        if(Amask)
                            A = ((((dc & Amask) >> surface->format->Ashift) + alpha) >> 1) << surface->format->Ashift;
                        break;
                }
                
                *pixel = R | G | B | A;
			break;
		}
	}
}

void SPG_PixelBlend(SDL_Surface *surface, Sint16 x, Sint16 y, Uint32 color, Uint8 alpha)
{
	if ( SDL_MUSTLOCK(surface) && _SPG_lock )
		if ( SDL_LockSurface(surface) < 0 )
		{
		    if(_spg_useerrors)
                SPG_Error("SPG_PixelBlend could not lock surface");
			return;
		}

	_PutPixelAlpha(surface,x,y,color, alpha);
	
	/* unlock the display */
	if (SDL_MUSTLOCK(surface) && _SPG_lock) {
		SDL_UnlockSurface(surface);
	}
}






/**********************************************************************************/
/**                            Block functions                                   **/
/**********************************************************************************/

//==================================================================================
// The SPG_write_block* functions copies the given block (a surface line) directly
// to the surface. This is *much* faster then using the put pixel functions to
// update a line. The block consist of Surface->w (the width of the surface) numbers
// of color values. Note the difference in byte size for the block elements for
// different color depths. 24 bpp is slow and not included!
//==================================================================================
// See sprig_inline.h






// SDL's clipping
SDL_Rect* SPG_BlitClip(SDL_Surface* source, SDL_Rect* srect, SDL_Surface* dest, SDL_Rect* drect)
{
    // Clip rects
    SDL_Rect fulldst;
	int srcx, srcy, w, h;


	/* If the destination rectangle is NULL, use the entire dest surface */
	if ( drect == NULL ) {
	        fulldst.x = fulldst.y = 0;
	        fulldst.w = dest->w;
	        fulldst.h = dest->h;
		drect = &fulldst;
	}

	/* clip the source rectangle to the source surface */
	if(srect) {
	        int maxw, maxh;
	
		srcx = srect->x;
		w = srect->w;
		if(srcx < 0) {
		        w += srcx;
			drect->x -= srcx;
			srcx = 0;
		}
		maxw = source->w - srcx;
		if(maxw < w)
			w = maxw;

		srcy = srect->y;
		h = srect->h;
		if(srcy < 0) {
		        h += srcy;
			drect->y -= srcy;
			srcy = 0;
		}
		maxh = source->h - srcy;
		if(maxh < h)
			h = maxh;
	    
	} else {
	        srcx = srcy = 0;
		w = source->w;
		h = source->h;
	}

	/* clip the destination rectangle against the clip rectangle */
	{
	        SDL_Rect *clip = &dest->clip_rect;
		int dx, dy;

		dx = clip->x - drect->x;
		if(dx > 0) {
			w -= dx;
			drect->x += dx;
			srcx += dx;
		}
		dx = drect->x + w - clip->x - clip->w;
		if(dx > 0)
			w -= dx;

		dy = clip->y - drect->y;
		if(dy > 0) {
			h -= dy;
			drect->y += dy;
			srcy += dy;
		}
		dy = drect->y + h - clip->y - clip->h;
		if(dy > 0)
			h -= dy;
	}

	if(w <= 0 || h <= 0)
		return NULL;
    
    
    SDL_Rect* result = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    
    
    result->x = srcx;
    result->y = srcy;
    result->w = drect->w = w;
    result->h = drect->h = h;
    
    return result;
}

void SPG_BlendBlit(SDL_Surface* source, SDL_Rect* srect, SDL_Surface* dest, SDL_Rect* drect)
{
    int lowSX, highSX, lowSY, highSY;
    
    if(srect)
    {
        lowSX = srect->x;
        highSX = srect->x + srect->w;
        lowSY = srect->y;
        highSY = srect->y + srect->h;
    }
    else
    {
        lowSX = 0;
        highSX = dest->w;
        lowSY = 0;
        highSY = dest->h;
    }
    
    int lowDX, highDX, lowDY, highDY;
    
    if(drect)
    {
        lowDX = drect->x;
        highDX = drect->x + drect->w;
        lowDY = drect->y;
        highDY = drect->y + drect->h;
    }
    else
    {
        lowDX = 0;
        highDX = dest->w;
        lowDY = 0;
        highDY = dest->h;
    }
    
    

    // Get the per-surface alpha
    Uint8 perSAlpha = source->format->alpha;

    // Ready the recycling loop variables
    int sx = 0, sy = 0, dx = 0, dy = 0;
    Uint32 color;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
    
    
    /*if ( SDL_MUSTLOCK(surface) && _SPG_lock )
        if ( SDL_LockSurface(surface) < 0 )
            return;
    if ( SDL_MUSTLOCK(dest) && _SPG_lock )
        if ( SDL_LockSurface(dest) < 0 )
            return;*/
            
    SPG_bool ncolorkeyed = !(source->flags & SDL_SRCCOLORKEY);
    Uint32 colorkey = source->format->colorkey;
    
    // Go through the rect we made
    for (sx = lowSX, sy = lowSY, dx = lowDX, dy = lowDY; sy < highSY;)
    {
        // Get the source color
        color = SPG_GetPixel(source, sx, sy);
        SDL_GetRGBA(color, source->format, &r, &g, &b, &a);
        
        // Combine per-surface and per-pixel alpha
        if(SPG_GetSurfaceAlpha())
            a = (Uint8)(a*(perSAlpha)/255.0);
        
        // Convert color to dest color
        color = SDL_MapRGB(dest->format, r, g, b);
        // If not a colorkeyed color, then draw the pixel (blending done in put pixel function)
        if(ncolorkeyed || color != colorkey)
            _PutPixelAlpha(dest, dx, dy, color, a);
        
        // Increment here so we can use the auto test on dy
        sx++;
        dx++;

        // Check sx bound to move on to the next horizontal line
        if (sx >= highSX)
        {
            sx = lowSX;
            sy++;
            dx = lowDX;
            dy++;
        }
    }
    
    /*if ( SDL_MUSTLOCK(surface) && _SPG_lock )
        SDL_UnlockSurface(surface);
    if ( SDL_MUSTLOCK(dest) && _SPG_lock )
        SDL_UnlockSurface(dest);*/
}

// SDL's clipping
int SPG_Blit(SDL_Surface* source, SDL_Rect* srect, SDL_Surface* dest, SDL_Rect* drect)
{
	/* Make sure the surfaces aren't locked */
	if ( ! source || ! dest ) {
		SDL_SetError("SPG_Blit was passed a NULL surface");
		return -1;
	}
	if ( source->locked || dest->locked ) {
		SDL_SetError("SPG_Blit was passed a locked surface");
		return -1;
	}
    
    
    srect = SPG_BlitClip(source, srect, dest, drect);
    if(_SPG_BlitFunc == NULL)
        _SPG_BlitFunc = SPG_BlendBlit;
    _SPG_BlitFunc(source, srect, dest, drect);
    
    
    free(srect);
    
    return 0;
}

void SPG_SetBlit(void (*blitfn)(SDL_Surface*, SDL_Rect*, SDL_Surface*, SDL_Rect*))
{
    _SPG_BlitFunc = blitfn;
}

void (*SPG_GetBlit())(SDL_Surface*, SDL_Rect*, SDL_Surface*, SDL_Rect*)
{
    return _SPG_BlitFunc;
}











/**********************************************************************************/
/**                            Palette functions                                 **/
/**********************************************************************************/



//==================================================================================
// Fades from (sR,sG,sB) to (dR,dG,dB), puts result in ctab[start] to ctab[stop]
//==================================================================================
void SPG_Fader(SDL_Surface *Surface, Uint8 sR,Uint8 sG,Uint8 sB, Uint8 dR,Uint8 dG,Uint8 dB,Uint32 *ctab,int start, int stop)
{
	// (sR,sG,sB) and (dR,dG,dB) are two points in space (the RGB cube). 	

	/* The vector for the straight line */
	int v[3];
	v[0]=dR-sR; v[1]=dG-sG; v[2]=dB-sB;

	/* Ref. point */
	int x0=sR, y0=sG, z0=sB;

	// The line's equation is:
	// x= x0 + v[0] * t
	// y= y0 + v[1] * t
	// z= z0 + v[2] * t
	//
	// (x,y,z) will travel between the two points when t goes from 0 to 1.

	int i=start;
 	double step=1.0/((stop+1)-start);
    double t;
	for(t=0.0; t<=1.0 && i<=stop ; t+=step){
		ctab[i++]=SDL_MapRGB(Surface->format, (Uint8)(x0+v[0]*t), (Uint8)(y0+v[1]*t), (Uint8)(z0+v[2]*t) );
	}			
}


//==================================================================================
// Fades from (sR,sG,sB,sA) to (dR,dG,dB,dA), puts result in ctab[start] to ctab[stop]
//==================================================================================
void SPG_AlphaFader(SDL_Surface *Surface, Uint8 sR,Uint8 sG,Uint8 sB,Uint8 sA, Uint8 dR,Uint8 dG,Uint8 dB,Uint8 dA, Uint32 *ctab,int start, int stop)
{
	// (sR,sG,sB,sA) and (dR,dG,dB,dA) are two points in hyperspace (the RGBA hypercube). 	

	/* The vector for the straight line */
	int v[4];
	v[0]=dR-sR; v[1]=dG-sG; v[2]=dB-sB; v[3]=dA-sA;

	/* Ref. point */
	int x0=sR, y0=sG, z0=sB, w0=sA;

	// The line's equation is:
	// x= x0 + v[0] * t
	// y= y0 + v[1] * t
	// z= z0 + v[2] * t
	// w= w0 + v[3] * t
	//
	// (x,y,z,w) will travel between the two points when t goes from 0 to 1.

	int i=start;
 	double step=1.0/((stop+1)-start);
    double t;
	for(t=0.0; t<=1.0 && i<=stop ; t+=step)
		ctab[i++]=SDL_MapRGBA(Surface->format, (Uint8)(x0+v[0]*t), (Uint8)(y0+v[1]*t), (Uint8)(z0+v[2]*t), (Uint8)(w0+v[3]*t));
					
}


//==================================================================================
// Copies a nice rainbow palette to the color table (ctab[start] to ctab[stop]).
// You must also set the intensity of the palette (0-bright 255-dark)
//==================================================================================
void SPG_SetupRainbowPalette(SDL_Surface *Surface,Uint32 *ctab,Uint8 intensity, int start, int stop)
{
	int slice=(int)((stop-start)/6);

	/* Red-Yellow */
	SPG_Fader(Surface, 255,intensity,intensity, 255,255,intensity, ctab, start,slice);
 	/* Yellow-Green */
	SPG_Fader(Surface, 255,255,intensity, intensity,255,intensity, ctab, slice+1, 2*slice);
 	/* Green-Turquoise blue */
	SPG_Fader(Surface, intensity,255,intensity, intensity,255,255, ctab, 2*slice+1, 3*slice);
 	/* Turquoise blue-Blue */
	SPG_Fader(Surface, intensity,255,255, intensity,intensity,255, ctab, 3*slice+1, 4*slice);
 	/* Blue-Purple */
	SPG_Fader(Surface, intensity,intensity,255, 255,intensity,255, ctab, 4*slice+1, 5*slice);	
 	/* Purple-Red */
	SPG_Fader(Surface, 255,intensity,255, 255,intensity,intensity, ctab, 5*slice+1, stop);	
}


//==================================================================================
// Copies a B&W palette to the color table (ctab[start] to ctab[stop]).
//==================================================================================
void SPG_SetupBWPalette(SDL_Surface *Surface,Uint32 *ctab,int start, int stop)
{
	SPG_Fader(Surface, 0,0,0, 255,255,255, ctab,start,stop);
}



/**********************************************************************************/
/**                          Color filling functions                             **/
/**********************************************************************************/

//==================================================================================
// SPG_FloodFill: Fast non-recursive flood fill
//
// Algorithm originally written by
// Paul Heckbert, 13 Sept 1982, 28 Jan 1987
//==================================================================================
/* horizontal segment of scan line y */
typedef struct seg{ 
	Sint16 y, xl, xr, dy;
}seg;

#define MAX 1000		/* max depth of stack */

#define PUSH(Y, XL, XR, DY){\
	if (sp<stack+MAX && Y+(DY)>=SPG_clip_ymin(dst) && Y+(DY)<=SPG_clip_ymax(dst)){\
		sp->y = Y;\
		sp->xl = XL;\
		sp->xr = XR;\
		sp->dy = DY;\
		sp++;\
	}\
}

#define POP(Y, XL, XR, DY){\
	sp--;\
	DY = sp->dy;\
	Y = sp->y + sp->dy;\
	XL = sp->xl;\
	XR = sp->xr;\
}
	

/*
 * set the pixel at (x,y) and all of its 4-connected neighbors
 * with the same pixel value to the new pixel color.
 * A 4-connected neighbor is a pixel above, below, left, or right of a pixel.
 */
// First a generic (slow) version and then 8/16/32 bpp versions
static void _FloodFillX(SDL_Surface *dst, Sint16 x, Sint16 y, Uint32 color)
{
	Sint16 l, x1, x2, dy;
	Uint32 oc;						/* old pixel color */
	seg stack[MAX], *sp = stack;	/* stack of filled segments */

	if (x<SPG_clip_xmin(dst) || x>SPG_clip_xmax(dst) || y<SPG_clip_ymin(dst) || y>SPG_clip_ymax(dst))
		return;
	
	oc = SPG_GetPixel(dst, x,y);	/* read color at seed point */
	
	if (oc == color) 
		return;
	
	PUSH(y, x, x, 1);			/* needed in some cases */
	PUSH(y+1, x, x, -1);		/* seed segment (popped 1st) */

	while (sp>stack) {
		/* pop segment off stack and fill a neighboring scan line */
		POP(y, x1, x2, dy);

		/*
		* segment of scan line y-dy for x1<=x<=x2 was previously filled,
		* now explore adjacent pixels in scan line y
		*/
		for (x=x1; x>=SPG_clip_xmin(dst); x--){
			if( SPG_GetPixel(dst, x,y) != oc )
				break;
			
			_SetPixel(dst, x, y, color);
		}
			
		if (x>=x1)
			goto skip;
		
		l = x+1;
		if (l<x1) 
			PUSH(y, l, x1-1, -dy);		/* leak on left? */
	
		x = x1+1;
		
		do {
			for (; x<=SPG_clip_xmax(dst); x++){
				if( SPG_GetPixel(dst, x,y) != oc )
					break;
					
				_SetPixel(dst, x, y, color);
			}
	    
			PUSH(y, l, x-1, dy);
			
			if (x>x2+1) 
				PUSH(y, x2+1, x-1, -dy);	/* leak on right? */
skip:		
			for (x++; x<=x2; x++)
				if( SPG_GetPixel(dst, x,y) == oc )
					break;
			
			l = x;
		} while (x<=x2);
	}
}

/* Macro for 8/16/32 bpp */
#define DO_FILL(UintXX, label)\
{\
	Sint16 l, x1, x2, dy;\
	Uint32 oc;						/* old pixel color */\
	seg stack[MAX], *sp = stack;	/* stack of filled segments */\
	Uint16 pitch = dst->pitch/dst->format->BytesPerPixel;\
	UintXX *row = (UintXX*)dst->pixels + y*pitch;\
	UintXX *pixel = row + x;\
\
	if (x<SPG_clip_xmin(dst) || x>SPG_clip_xmax(dst) || y<SPG_clip_ymin(dst) || y>SPG_clip_ymax(dst))\
		return;\
\
	oc = *pixel;	/* read color at seed point */\
\
	if (oc == color)\
		return;\
\
	PUSH(y, x, x, 1);			/* needed in some cases */\
	PUSH(y+1, x, x, -1);		/* seed segment (popped 1st) */\
\
	while (sp>stack) {\
		/* pop segment off stack and fill a neighboring scan line */\
		POP(y, x1, x2, dy);\
		row = (UintXX*)dst->pixels + y*pitch;\
		pixel = row + x1;\
\
		/*\
		* segment of scan line y-dy for x1<=x<=x2 was previously filled,
		* now explore adjacent pixels in scan line y
		*/\
		for (x=x1; x>=SPG_clip_xmin(dst) && *pixel == oc; x--, pixel--)\
			*pixel = color;\
\
		if (x>=x1)\
			goto label;\
\
		l = x+1;\
		if (l<x1)\
			PUSH(y, l, x1-1, -dy);		/* leak on left? */\
\
		x = x1+1;\
		pixel = row + x;\
\
		do {\
			for (; x<=SPG_clip_xmax(dst) && *pixel == oc; x++, pixel++)\
				*pixel = color;\
\
			PUSH(y, l, x-1, dy);\
\
			if (x>x2+1)\
				PUSH(y, x2+1, x-1, -dy);	/* leak on right? */\
label:\
			pixel++;\
\
			for (x++; x<=x2 && *pixel != oc; x++, pixel++);\
\
			l = x;\
		} while (x<=x2);\
	}\
}

// Wrapper function
void SPG_FloodFill(SDL_Surface *dst, Sint16 x, Sint16 y, Uint32 color)
{
	if ( SDL_MUSTLOCK(dst) && _SPG_lock )
		if ( SDL_LockSurface(dst) < 0 )
		{
		    if(_spg_useerrors)
                SPG_Error("SPG_FloodFill could not lock surface");
			return;
		}

	switch (dst->format->BytesPerPixel) {
		case 1: /* Assuming 8-bpp */
			DO_FILL(Uint8, skip8)
		break;

		case 2: /* Probably 15-bpp or 16-bpp */
			DO_FILL(Uint16, skip16)
		break;

		case 3: /* Slow 24-bpp mode, usually not used */
			_FloodFillX(dst, x,y, color);
		break;

		case 4: /* Probably 32-bpp */
			DO_FILL(Uint32, skip32)
		break;
	}
	
	if ( SDL_MUSTLOCK(dst) && _SPG_lock ){
		SDL_UnlockSurface(dst);
	}
}



