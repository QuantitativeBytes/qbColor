/* ***********************************************************
qbColor.cpp
	
The qbColor class implementation.
	
This code corresponds specifically to the two-part series
on colour space conversion on the QuantitativeBytes
YouTube channel, which can be found here:
	
(Episode 1 - HSV to RGB)
https://youtu.be/hW4gZ4tGwds
	
(Episode 2 - RGB TO HSV)
https://youtu.be/I8i0W8ve-JI
	
The QuantitativeBytes YouTube channel can be found here:
www.youtube.com/c/QuantitativeBytes
	
MIT License

Copyright (c) 2021 Michael Bennett

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
	
**********************************************************/

#include "qbColor.h"
#include <math.h>
#include <iostream>

// The default constructor.
qbColor::qbColor()
{
	m_red = 0.0;
	m_green = 0.0;
	m_blue = 0.0;
	m_hue = 0.0;
	m_saturation = 0.0;
	m_value = 0.0;
}

// The specific constructor.
qbColor::qbColor(double r, double g, double b)
{
	m_red = r;
	m_green = g;
	m_blue = b;
	ComputeHSV();
}

// Methods to set the color.
void qbColor::SetRGB(const unsigned char r, const unsigned char g, const unsigned char b)
{
	m_red = static_cast<double>(r) / 255.0;
	m_green = static_cast<double>(g) / 255.0;
	m_blue = static_cast<double>(b) / 255.0;
	ComputeHSV();
}

void qbColor::SetHSV(const unsigned char h, const unsigned char s, const unsigned char v)
{
	m_hue = (static_cast<double>(h) / 255.0) * 360.0;
	m_saturation = static_cast<double>(s) / 255.0;
	m_value = static_cast<double>(v) / 255.0;
	ComputeRGB();
}

void qbColor::SetRGB(double r, double g, double b)
{
	m_red = r;
	m_green = g;
	m_blue = b;
	ComputeHSV();
}

void qbColor::SetHSV(double h, double s, double v)
{
	m_hue = h;
	m_saturation = s;
	m_value = v;
	ComputeRGB();
}

// Methods to retrieve the color.
unsigned char qbColor::GetRed()
{
	return static_cast<unsigned char>(m_red * 255.0);
}
unsigned char qbColor::GetGreen()
{
	return static_cast<unsigned char>(m_green * 255.0);
}
unsigned char qbColor::GetBlue()
{
	return static_cast<unsigned char>(m_blue * 255.0);
}
unsigned char qbColor::GetHue()
{
	return static_cast<unsigned char>((m_hue / 360.0) * 255.0);
}
unsigned char qbColor::GetSaturation()
{
	return static_cast<unsigned char>(m_saturation * 255.0);
}
unsigned char qbColor::GetValue()
{
	return static_cast<unsigned char>(m_value * 255.0);
}

double qbColor::GetRedf()
{
	return m_red;
}
double qbColor::GetGreenf()
{
	return m_green;
}
double qbColor::GetBluef()
{
	return m_blue;
}
double qbColor::GetHuef()
{
	return m_hue;
}
double qbColor::GetSaturationf()
{
	return m_saturation;
}
double qbColor::GetValuef()
{
	return m_value;
}

// Methods to convert between colour spaces.

void qbColor::ComputeHSV()
{
	/* Convert from RGB to HSV.
	
		First, determine the maximum and minimum values
		and which colours (red, green or blue) that they
		correspond to.
	*/
	double minValue, maxValue;
	unsigned char maxIndex;
	if ((m_red == m_green) && (m_red == m_blue))
	{
		maxIndex = 0;
		maxValue = m_red;
		minValue = m_red;
	}
	else if ((m_red >= m_green) && (m_red >= m_blue))
	{
		maxIndex = 1;
		maxValue = m_red;
		minValue = (m_green < m_blue) ? m_green : m_blue;
	}
	else if ((m_green >= m_red) && (m_green >= m_blue))
	{
		maxIndex = 2;
		maxValue = m_green;
		minValue = (m_red < m_blue) ? m_red : m_blue;
	}
	else
	{
		maxIndex = 3;
		maxValue = m_blue;
		minValue = (m_red < m_green) ? m_red : m_green;
	}
	
	// Now we can compute the value of h.
	double h;
	switch(maxIndex)
	{
		case 0:	h = 0.0;
						break;
		case 1: h = 60.0 * ((m_green - m_blue) / (maxValue - minValue));
						break;
		case 2: h = 60.0 * (2 + ((m_blue - m_red) / (maxValue - minValue)));
						break;
		case 3: h = 60.0 * (4 + ((m_red - m_green) / (maxValue - minValue)));
						break;
	}
	if (h < 0.0)
		h += 360.0;
		
	// Compute the saturation.
	double s;
	s = (maxIndex == 0) ? 0.0 : ((maxValue - minValue) / maxValue);
	
	// Compute the value.
	double v = maxValue;
	
	// And store the result.
	m_hue = h;
	m_saturation = s;
	m_value = v;						
}

void qbColor::ComputeRGB()
{
	// Convert HSV values to RGB.
	double rgbRange = m_value * m_saturation;
	double maxRGB = m_value;
	double minRGB = m_value - rgbRange;
	double hPrime = m_hue / 60.0;
	double x1 = fmod(hPrime, 1.0);
	double x2 = 1.0 - fmod(hPrime, 1.0);
	
	if ((hPrime >= 0) && (hPrime < 1))
	{
		m_red = maxRGB;
		m_green = (x1 * rgbRange) + minRGB;
		m_blue = minRGB;
	}
	else if ((hPrime >= 1) && (hPrime < 2))
	{
		m_red = (x2 * rgbRange) + minRGB;
		m_green = maxRGB;
		m_blue = minRGB;
	}
	else if ((hPrime >= 2) && (hPrime < 3))
	{
		m_red = minRGB;
		m_green = maxRGB;
		m_blue = (x1 * rgbRange) + minRGB;
	}
	else if ((hPrime >= 3) && (hPrime < 4))
	{
		m_red = minRGB;
		m_green = (x2 * rgbRange) + minRGB;
		m_blue = maxRGB;
	}
	else if ((hPrime >= 4) && (hPrime < 5))
	{	
		m_red = (x1 * rgbRange) + minRGB;
		m_green = minRGB;
		m_blue = maxRGB;
	}
	else if ((hPrime >= 5) && (hPrime < 6))
	{
		m_red = maxRGB;
		m_green = minRGB;
		m_blue = (x2 * rgbRange) + minRGB;
	}
	else
	{
		m_red = 0.0;
		m_green = 0.0;
		m_blue = 0.0;
	}
	
}
