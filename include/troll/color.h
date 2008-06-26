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

#ifndef __TROLL_COLOR_H__
#define __TROLL_COLOR_H__

namespace Troll
{

typedef unsigned char ColorComponent;

enum ColorDepth
{
	depth1bpp = 1,
	depth2bpp = 2,	
	depth3bpp = 3,
	depth4bpp = 4,
	depthAuto = -1
};

class Color
{
public:
	enum { alphaTranparent = 0,alpha75 = 192,alphaOpaque = 255} ;

	Color();
	Color(ColorComponent r,ColorComponent g,ColorComponent b,ColorComponent a = alphaOpaque);
	Color(const Color& color);
	~Color();

	Color& operator = (const Color & color);

	inline bool operator == (const Color & color) const { return m_red == color.m_red && m_green == color.m_green && m_blue == color.m_blue && m_alpha == color.m_alpha; }
	inline bool operator != (const Color & color) const { return m_red != color.m_red || m_green != color.m_green || m_blue != color.m_blue || m_alpha != color.m_alpha; }

	Color operator - (const Color & color) const;
	Color operator + (const Color & color) const;

	Color operator * (int i) const;
	Color operator / (int i) const;

	inline ColorComponent GetRed() const	{ return m_red;	  }
	inline ColorComponent GetGreen() const { return m_green; }
	inline ColorComponent GetBlue() const	{ return m_blue;  }
	inline ColorComponent GetAlpha() const { return m_alpha;  }

	inline void SetRed(ColorComponent red)		{ m_red   = red;   }
	inline void SetGreen(ColorComponent green) { m_green = green; }
	inline void SetBlue(ColorComponent blue)	{ m_blue  = blue;  }
	inline void SetAlpha(ColorComponent alpha)	{ m_alpha = alpha; }

	inline void IncraseAlpha(char cIncrase = 32) { m_alpha += cIncrase; }
	inline void DecraseAlpha(char cIncrase = 32) { m_alpha -= cIncrase; }

	void SetColor(ColorComponent r,ColorComponent g,ColorComponent b,ColorComponent a = alphaOpaque);
	
	void GetHLS(ColorComponent & hue,ColorComponent & luminance,ColorComponent & saturation) const;
	void SetHLS(ColorComponent hue,ColorComponent luminance,ColorComponent saturation);
private:
	static ColorComponent HueToRGB(float rm1, float rm2, float rh);
	
public:
	ColorComponent GetSaturation() const;
	ColorComponent GetHue() const;
	ColorComponent GetLuminance() const;

	void RotateHue(char cInc = 32);

	void IncraseSaturation(char fInc);
	void DecraseSaturation(char fDec);

	void IncraseLuminance(char fInc = 32);
	void DecraseLuminance(char fDec = 32);

private:
	ColorComponent m_red;
	ColorComponent m_green;
	ColorComponent m_blue;
	ColorComponent m_alpha;

public:

	static const Color WHITE;
	static const Color BLACK;
	static const Color DARKGRAY;
	static const Color GRAY;
	static const Color DARKRED;
	static const Color RED;
	static const Color DARKBLUE;
	static const Color BLUE;
	static const Color DARKGREEN;
	static const Color GREEN;
	static const Color DARKYELLOW;
	static const Color YELLOW;
	static const Color DARKTEAL;
	static const Color TEAL;
	static const Color DARKPINK;
	static const Color PINK;
	static const Color DARKORANGE;
	static const Color ORANGE;
	static const Color INVISIBLE;
};

}

#endif //__TROLL2D_COLOR_H__