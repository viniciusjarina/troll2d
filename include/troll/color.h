#ifndef __TROLL2D_COLOR_H__
#define __TROLL2D_COLOR_H__

namespace Troll
{

typedef unsigned char ColorComponent;

class Color
{
public:
	enum { alphaTranparent = 0,alpha75 = 192,alphaOpaque = 255} ;

	Color();
	Color(ColorComponent r,ColorComponent g,ColorComponent b,ColorComponent a = alphaOpaque);
	Color(const Color& color);
	~Color();

	Color& operator = (const Color & color);

	bool operator == (const Color & color) const { return m_red == color.m_red && m_green == color.m_green && m_blue == color.m_blue && m_alpha == color.m_alpha; }
	bool operator != (const Color & color) const { return m_red != color.m_red || m_green != color.m_green || m_blue != color.m_blue || m_alpha != color.m_alpha; }

	Color operator - (const Color & color) const;
	Color operator + (const Color & color) const;

	Color operator * (int i) const;
	Color operator / (int i) const;

	ColorComponent GetRed() const	{ return m_red;	  }
	ColorComponent GetGreen() const { return m_green; }
	ColorComponent GetBlue() const	{ return m_blue;  }
	ColorComponent GetAlpha() const { return m_blue;  }

	void SetRed(ColorComponent red)		{ m_red   = red;   }
	void SetGreen(ColorComponent green) { m_green = green; }
	void SetBlue(ColorComponent blue)	{ m_blue  = blue;  }
	void SetAlpha(ColorComponent alpha)	{ m_alpha = alpha; }

	void IncraseAlpha(char cIncrase = 32) { m_alpha += cIncrase; }
	void DecraseAlpha(char cIncrase = 32) { m_alpha -= cIncrase; }

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
	static const Color NOCOLOR;
	static const Color INVISIBLE;
};

}

#endif //__TROLL2D_COLOR_H__