# qbColor
## Color space converstion - RGB to HSV and HSV to RGB.

The qbColor class, defined in qbColor.h and qbColor.cpp
provides a simple demonstration of how to implement the
conversion from RGB to HSV and back to RGB.

The code in CApp.h and CApp.cpp provides a demonstration
of the use of this class and is written to use the SDL2
library to display results in a window. Note that the SDL2
library is not included here, so you will have to download
and install that yourself for your particular platform if
you don't already have it.

The demonstration creates a spectrum display in the window,
with hue varying across the horizontal axis and value across
the vertical axis. The value is then animated repeatedly 
from 1.0 to 0.0 over 100 frames. The frame-rate will 
depend on your system.

A makefile has been provided to support building the code
using GMake.

This code corresponds specifically to the two-part series
on colour space conversion on the QuantitativeBytes
YouTube channel, which can be found here:
	
(Episode 1 - HSV to RGB)
https://youtu.be/hW4gZ4tGwds
	
(Episode 2 - RGB TO HSV)
https://youtu.be/I8i0W8ve-JI
	
The QuantitativeBytes YouTube channel can be found here:
www.youtube.com/c/QuantitativeBytes

As the code corresponds to specific videos, pull requests 
will not be accepted.
