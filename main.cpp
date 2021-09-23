/* ***********************************************************
main.cpp
	
The main entry point for the qbColor class demo code.
	
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
#include <iostream>

int main(int argc, char* argv[])
{
	CApp theApp;
	
	return theApp.Execute();
}
