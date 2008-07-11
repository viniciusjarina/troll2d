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


#ifndef __TROLL_SURFACE_H__
#define __TROLL_SURFACE_H__

#include "troll/size.h"
#include "troll/point.h"
#include "troll/rect.h"
#include "troll/color.h"


namespace Troll
{
	class SurfaceImpl;

	class Surface
	{
		friend class GraphicsFactory;

		SurfaceImpl * m_impl; // Interface of implementation

	protected:

		Surface(SurfaceImpl * impl); // Protected ctor (user internally)

	public:
		Surface(); // Default ctor
		Surface(int width,int height,ColorDepth depth = depthAuto);

		virtual ~Surface();
		
	public:
		// Creates a surface with given width and heigh
		bool Create(int width,int height,ColorDepth depth = depthAuto); 
		
		int GetHeight() const; // Get the Height of surface
		int GetWidth() const;  // Get the Width of surface

		inline Size GetSize() const { return Size(GetWidth(), GetHeight()); }
		
		void SetClip(const Rect & rect); // Set clip rect of surface
		Rect GetClip();					 // Get current clipping rect
		void ResetClip();				 // Reset the clip rect
		
		void Clear(const Color & color = Color::BLACK); // Clean surface with color

		// Blits from the Surface (src) the rect (rSource) into postion (ptDest) of surface
		void Blit(const Surface & src,const Point& ptDest = Point(0,0),const Rect& rSource = Rect(0,0,-1,-1));
		// Draw the entire surface (sprite) at position ptDest with alpha-value (alpha)
		void DrawAlpha(const Surface & sprite,const Point& ptDest = Point(0,0),unsigned char alpha = 128);
	};
	
}
#endif // __TROLL_SURFACE_H__
