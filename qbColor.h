/* ***********************************************************
qbColor.h
	
The qbColor class definition.
	
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

#ifndef QBCOLOR_H
#define QBCOLOR_H

class qbColor
{

public:
	// The default constructor.
	qbColor();
	
	// A specific constructor.
	qbColor(double r, double g, double b);
	
	// Methods for setting the color.
	void SetRGB(const unsigned char r, const unsigned char g, const unsigned char b);
	void SetHSV(const unsigned char h, const unsigned char s, const unsigned char v);
	
	void SetRGB(double r, double g, double b);
	void SetHSV(double h, double s, double v);
	
	// Methods for retrieving the color.
	unsigned char GetRed();
	unsigned char GetGreen();
	unsigned char GetBlue();
	
	unsigned char GetHue();
	unsigned char GetSaturation();
	unsigned char GetValue();
	
	double GetRedf();
	double GetGreenf();
	double GetBluef();
	
	double GetHuef();
	double GetSaturationf();
	double GetValuef();

private:
	double m_red;
	double m_green;
	double m_blue;
	
	double m_hue;
	double m_saturation;
	double m_value;
	
	void ComputeHSV();
	void ComputeRGB();

};


#endif // QBCOLOR_H
