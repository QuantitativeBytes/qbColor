# ***********************************************************
# makefile
	
# The make file for the qbColor demo code.
	
# This code corresponds specifically to the two-part series
# on colour space conversion on the QuantitativeBytes
# YouTube channel, which can be found here:
	
# (Episode 1 - HSV to RGB)
# https://youtu.be/hW4gZ4tGwds
	
# (Episode 2 - RGB TO HSV)
# https://youtu.be/I8i0W8ve-JI
	
# The QuantitativeBytes YouTube channel can be found here:
# www.youtube.com/c/QuantitativeBytes
	
# MIT License

# Copyright (c) 2021 Michael Bennett

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
	
# **********************************************************

# Define the link target.
linkTarget = main

# Define libraries that we need,
LIBS = -lSDL2

# Define flags.
# CFLAGS = -std=c++17 -pg
CFLAGS = -std=c++17

# Define the object files that we need to use.
objects = main.o \
					CApp.o \
					qbColor.o
					
# Define the rebuildables.
rebuildables = $(objects) $(linkTarget)

# Rule to actually perform the build.
$(linkTarget): $(objects)
	@echo "Rule 1..."
	g++ -g -o $(linkTarget) $(objects) $(LIBS) $(CFLAGS)
	
# Rule to create the .o files.
%.o: %.cpp
	@echo "Rule 2..."
	g++ -o $@ -c $< $(CFLAGS)

.PHONEY:
clean:
	rm $(rebuildables)
