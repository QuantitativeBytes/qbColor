/* ***********************************************************
CApp.cpp
	
The application class implementation.
	
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

#include "CApp.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>

// The constructor (default)
CApp::CApp()
{
	m_isRunning = true;
	m_window = nullptr;
	m_renderer = nullptr;	
	
	m_frameCount = 0;
	m_numFrames = 100;
}

bool CApp::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}
	
	m_window = SDL_CreateWindow("Color space conversion", SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	
	if (m_window != nullptr)
	{
		m_renderer = SDL_CreateRenderer(m_window, -1, 0);
	}
	else
	{
		return false;
	}
	
	// Store the window dimensions.
	SDL_GetRendererOutputSize(m_renderer, &m_xSize, &m_ySize);
	
	/* Demonstrate converstion from RGB to HSV by setting
		up an array of colors, defined as RGB and then
		producing a simple table in the terminal showing
		the computed HSV values. */
		
	// Setup an array of colours for testing.
	std::vector<qbColor> testColors;
	
	// Define a set of colours for testing (as RGB).
	// Black
	testColors.push_back(qbColor(0.0, 0.0, 0.0));
	// White
	testColors.push_back(qbColor(1.0, 1.0, 1.0));
	// Red
	testColors.push_back(qbColor(1.0, 0.0, 0.0));
	// Green
	testColors.push_back(qbColor(0.0, 1.0, 0.0));
	// Blue
	testColors.push_back(qbColor(0.0, 0.0, 1.0));
	// Yellow
	testColors.push_back(qbColor(1.0, 1.0, 0.0));
	// Cyan
	testColors.push_back(qbColor(0.0, 1.0, 1.0));
	// Magenta
	testColors.push_back(qbColor(1.0, 0.0, 1.0));
	// Dark red
	testColors.push_back(qbColor(0.5, 0.0, 0.0));
	// Olive
	testColors.push_back(qbColor(0.5, 0.5, 0.0));
	// Dark green
	testColors.push_back(qbColor(0.0, 0.5, 0.0));
	// Purple
	testColors.push_back(qbColor(0.5, 0.0, 0.5));
	// Teal
	testColors.push_back(qbColor(0.0, 0.5, 0.5));
	// Dark blue
	testColors.push_back(qbColor(0.0, 0.0, 0.5));
	// Mid-gray
	testColors.push_back(qbColor(0.5, 0.5, 0.5));
	// Dark-gray
	testColors.push_back(qbColor(0.25, 0.25, 0.25));
	
	// Produce a nice table of output.
	int cW = 4;
	std::cout << std::setw(cW) << "R" << ", "
		<< std::setw(cW) << "G" << ", "
		<< std::setw(cW) << "B" << " : "
		<< std::setw(cW) << "H" << ", "
		<< std::setw(cW) << "S" << ", "
		<< std::setw(cW) << "V" << std::endl;
	
	for (qbColor currentColor : testColors)
	{
		std::cout << std::setw(cW) << currentColor.GetRedf() << ", "
			<< std::setw(cW) << currentColor.GetGreenf() << ", "
			<< std::setw(cW) << currentColor.GetBluef() << " : "
			<< std::setw(cW) << currentColor.GetHuef() << ", " 
			<< std::setw(cW) << currentColor.GetSaturationf() << ", "
			<< std::setw(cW) << currentColor.GetValuef() << std::endl;
	}
	
	return true;
}

int CApp::Execute()
{
	// Define a variable for handling events.
	SDL_Event event;
	
	// Call the Initialize function to set everything up.
	if (Initialize() == false)
	{
		return -1;
	}
	
	/* Begin the main loop, which loops until isRunning is false. */
	int count = 0;
	while (m_isRunning)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
				case SDL_QUIT:
					m_isRunning = false;
					break;
			}
		}
		
		/* Call Tick to update everything each time through
			the main loop. */
		Tick();

	}
	
	/* The code for exiting the application, which runs after
		we drop out of the main loop. */
	
	// Destroy the window and call SDL_Quit().
	SDL_DestroyWindow(m_window);
	m_window = NULL;
	SDL_Quit();
	
	return 0;
}

void CApp::Tick()
{
	// Set the background colour to black.
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
	
	/* Demonstrate conversion from HSV to RGB by creating
		a spectrum image with hue on the horizontal axis
		and saturation on the vertical axis. Animates over
		100 frames of the value ranging from 1.0 to 0.0 and
		then repeats. */
	
  // Draw the spectrum.
  for (int y=0; y<m_ySize; ++y)
  {
	  for (int x=0; x<m_xSize; ++x)
		{
	  	double hue = (static_cast<double>(x) / static_cast<double>(m_xSize)) * 360.0;
    	double sat = 1.0 - (static_cast<double>(y) / static_cast<double>(m_ySize));
    	double val = 1.0 - (static_cast<double>(m_frameCount % m_numFrames) / static_cast<double>(m_numFrames));
    	//double val = 1.0;
    	m_pixelColor.SetHSV(hue, sat, val);
                        
    	int red = static_cast<int>(m_pixelColor.GetRed());
    	int green = static_cast<int>(m_pixelColor.GetGreen());
    	int blue = static_cast<int>(m_pixelColor.GetBlue());
    	SDL_SetRenderDrawColor(m_renderer, red, green, blue, 255);
    	SDL_RenderDrawPoint(m_renderer, x, y);
		}
	}
	
	// Update the display.
	SDL_RenderPresent(m_renderer);
	
	// Increment the frame counter.
	m_frameCount++;
}
