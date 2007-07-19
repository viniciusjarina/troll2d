

#include "troll/defs.h"
#include "troll/color.h"

using namespace Troll;

Color::Color():
m_red(0),
m_green(0),
m_blue(0),
m_alpha(alphaOpaque)
{
}

Color::Color(ColorComponent red,ColorComponent green,ColorComponent blue,ColorComponent alpha /*= alphaOpaque*/):
m_red(red),
m_green(green),
m_blue(blue),
m_alpha(alpha)
{
}

Color::Color(const Color& color):
m_red(color.m_red),
m_green(color.m_green),
m_blue(color.m_blue),
m_alpha(color.m_alpha)
{
}

Color::~Color()
{

}

Color& Color::operator = (const Color & color)
{
	m_red   = color.m_red;
	m_green = color.m_green;
	m_blue  = color.m_blue;
	m_alpha = color.m_alpha;
	return *this;
}

Color Color::operator - (const Color & color) const
{
	Color result;
    int r = m_red   - color.m_red;
    int g = m_green - color.m_green;
    int b = m_blue  - color.m_blue;
    
    result.m_red   = (r < 0 ? 0 : r);
    result.m_green = (g < 0 ? 0 : g);
    result.m_blue  = (b < 0 ? 0 : b);

	return result;
}

Color Color::operator + (const Color & color) const
{
	Color result;

    int r = m_red   + color.m_red;
    int g = m_green + color.m_green;
    int b = m_blue  + color.m_blue;
    
    result.m_red   = (r > 255 ? 255 : r);
    result.m_green = (g > 255 ? 255 : g);
    result.m_blue  = (b > 255 ? 255 : b);
	result.m_alpha = 255;

	return result;
}

Color Color::operator * (int i) const
{
	Color result;

    int r = m_red   * i;
    int g = m_green * i;
    int b = m_blue  * i;
    
    result.m_red   = (r > 255 ? 255 : ( r < 0 ? 0 : r));
    result.m_green = (g > 255 ? 255 : ( g < 0 ? 0 : g));
    result.m_blue  = (b > 255 ? 255 : ( b < 0 ? 0 : b));
	result.m_alpha = 255;

	return result;
}

Color Color::operator / (int i) const
{
	Color result;

    int r = m_red   / i;
    int g = m_green / i;
    int b = m_blue  / i;
    
    result.m_red   = (r > 255 ? 255 : ( r < 0 ? 0 : r));
    result.m_green = (g > 255 ? 255 : ( g < 0 ? 0 : g));
    result.m_blue  = (b > 255 ? 255 : ( b < 0 ? 0 : b));
	result.m_alpha = 255;

	return result;
}

void Color::SetColor(ColorComponent red,ColorComponent green,ColorComponent blue,ColorComponent alpha /*= alphaOpaque*/)
{
	m_red   = red;
	m_green = green;
	m_blue  = blue;
	m_alpha = alpha;
}
	
void Color::GetHLS(ColorComponent & hue,ColorComponent & luminance,ColorComponent & saturation) const
{	// TODO : Implement GetHLS using only integers
    ColorComponent minval = min(m_red, min(m_green, m_blue));
    ColorComponent maxval = max(m_red, max(m_green, m_blue));
	
    float mdiff  = float(maxval) - float(minval);
    float msum   = float(maxval) + float(minval);
	
    luminance = (ColorComponent)(msum / 2.f);
	
    if (maxval == minval) 
    {
		saturation = 0;
		hue		   = 0; 
    }   
    else 
    { 
		float fSaturation = (luminance <= 128) ? ((mdiff) / msum) : ((mdiff)/ (510.0f - msum));
		saturation = (ColorComponent)(fSaturation * 255.f);

		float fHue;		
		float rnorm = (maxval - m_red  ) / mdiff;      
		float gnorm = (maxval - m_green) / mdiff;
		float bnorm = (maxval - m_blue ) / mdiff;   
		
		
		if (m_red == maxval) 
			fHue = 60.0f * (6.0f + bnorm - gnorm);
		
		if (m_green == maxval) 
			fHue = 60.0f * (2.0f + rnorm - bnorm);
		
		if (m_blue  == maxval) 
			fHue = 60.0f * (4.0f + gnorm - rnorm);
		
		if (fHue > 360.0f)
			fHue = fHue - 360.0f;

		hue = (ColorComponent)((fHue*255.f)/360.f);
    }
}

ColorComponent Color::HueToRGB(float rm1, float rm2, float rh)
{
	if(rh > 360.0f)
		rh -= 360.0f;	
	else if(rh <   0.0f)
		rh += 360.0f;

	if(rh <  60.0f)
		rm1 = rm1 + (rm2 - rm1) * rh / 60.0f;	
	else if (rh < 180.0f)
		rm1 = rm2;	
	else if (rh < 240.0f)
		rm1 = rm1 + (rm2 - rm1) * (240.0f - rh) / 60.0f;
	
	return (ColorComponent)(rm1 * 255);
}

void Color::SetHLS(ColorComponent hue,ColorComponent luminance,ColorComponent saturation)
{	// TODO: Implement using only integer...
	if (saturation == 0)
	{
		m_red = m_green = m_blue = luminance;
    }
    else
	{
		float fLuminance  = luminance /255.f;
		float fSaturation = saturation/255.f;
		float fHue		  = (hue*360.f)/255.f;
		float rm1, rm2;
		if (fLuminance <= 0.5f) 
			rm2 = fLuminance + fLuminance * fSaturation;  
		else
			rm2 = fLuminance + fSaturation - fLuminance * fSaturation;
		
		rm1 = 2.0f * fLuminance - rm2;   
		
		m_red   = HueToRGB(rm1, rm2, fHue + 120.0f);   
		m_green = HueToRGB(rm1, rm2, fHue);
		m_blue  = HueToRGB(rm1, rm2, fHue - 120.0f);		
    }
}

ColorComponent Color::GetHue() const
{
	ColorComponent h,l,s;
	GetHLS(h,l,s);
	return h;
}

ColorComponent Color::GetLuminance() const
{
	ColorComponent h,l,s;
	GetHLS(h,l,s);
	return l;
}

ColorComponent Color::GetSaturation() const
{
	ColorComponent h,l,s;
	GetHLS(h,l,s);
	return s;
}

void Color::RotateHue(char rRot)
{
	ColorComponent h,l,s;
	GetHLS(h,l,s);
	int iHue = h;
	iHue += rRot;

	if(iHue < 0)
		h = iHue + 255;
	else if( iHue > 255)
		h = iHue - 255;
	else
		h = iHue;

	SetHLS(h,l,s);
}

void Color::IncraseSaturation(char fInc)
{
	ColorComponent h,l,s;
	GetHLS(h,l,s);

	int iSaturation = s;
	iSaturation += fInc;

	if(iSaturation < 0)
		s = 0;
	else if( iSaturation > 255)
		s = 255;
	else
		s = (ColorComponent)iSaturation;

	SetHLS(h,l,s);
}

void Color::DecraseSaturation(char cDec)
{
	ColorComponent h,l,s;
	GetHLS(h,l,s);

	int iSaturation = s;
	iSaturation -= cDec;

	if(iSaturation < 0)
		s = 0;
	else if( iSaturation > 255)
		s = 255;
	else
		s = (ColorComponent)iSaturation;
	SetHLS(h,l,s);
}

void Color::IncraseLuminance(char  cInc)
{
	ColorComponent h,l,s;
	GetHLS(h,l,s);

	int iLuminance = l;
	iLuminance += cInc;

	if(iLuminance < 0)
		l = 0;
	else if( iLuminance > 255)
		l = 255;
	else
		l = (ColorComponent)iLuminance;

	SetHLS(h,l,s);
}

void Color::DecraseLuminance(char fDec)
{
	ColorComponent h,l,s;
	GetHLS(h,l,s);
	int iLuminance = l;
	iLuminance -= fDec;

	if(iLuminance < 0)
		l = 0;
	else if( iLuminance > 255)
		l = 255;
	else
		l = (ColorComponent)iLuminance;

	SetHLS(h,l,s);
}

Color const Color::WHITE	= Color(255,255,255,255);
Color const Color::BLACK	= Color (0,0,0,255);
Color const Color::DARKGRAY = Color(88,88,88,255);
Color const Color::GRAY		= Color(128,128,128,255);
Color const Color::DARKRED	= Color(128,0,0,255);
Color const Color::RED		= Color(255,0,0,255);
Color const Color::DARKBLUE = Color(0,0,128,255);
Color const Color::BLUE		= Color(0,0,255,255);
Color const Color::DARKGREEN = Color(0,128,0,255);
Color const Color::GREEN	= Color(0,255,0,255);
Color const Color::DARKYELLOW = Color(128,128,0,255);
Color const Color::YELLOW	= Color(255,255,0,255);
Color const Color::DARKTEAL = Color(0,128,128,255);
Color const Color::TEAL		= Color(0,255,255,255);
Color const Color::DARKPINK	= Color(128,0,128,255);
Color const Color::PINK		= Color(255,0,255,255);
Color const Color::DARKORANGE = Color(192,88,0,255);
Color const Color::ORANGE	= Color(255,128,0,255);
Color const Color::INVISIBLE = Color(255,0,255,0);
