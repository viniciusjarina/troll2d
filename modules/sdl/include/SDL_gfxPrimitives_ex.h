#ifndef _SDL_gfxPrimitives_ex_h
#define _SDL_gfxPrimitives_ex_h

#ifdef __cplusplus
extern "C" {
#endif

int arcColorEx(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 r, Sint16 start, Sint16 end, Uint32 color);
int arcRGBAEx(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad, Sint16 start, Sint16 end, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

int filledArcColorEx(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad, Sint16 start, Sint16 end, Uint32 color);
int filledArcRGBAEx(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad, Sint16 start, Sint16 end, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

int filledRoundRectRGBA(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 w, Sint16 h, Sint16 end, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
int roundRectRGBA(SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 w, Sint16 h, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);


/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* _SDL_gfxPrimitives_h */
