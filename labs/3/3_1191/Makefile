# Makefile for RASTER lab by RTV. 

# Makefiles help manage the compilation process.  To use this
# Makefile, run 'make' in the directory containing this file.

# compiler options
CFLAGS = -std=c99 -g -Wall -O3
LDFLAGS = -lm -lpng

# find X11 libraries on most platforms, including Linux in CSIL
LDFLAGS += `pkg-config --libs x11` 
CFLAGS  += `pkg-config --cflags x11`

# find X11 library on other platforms, e.g. OS X with XQuartz installed.
# CFLAGS  += -I/usr/X11/include 
# LDFLAGS += -L/usr/X11/lib -lX11 


SRC1 = test.c imgops.c draw.c png.c
test: $(SRC1) draw.h
	gcc $(CFLAGS) -o test $(SRC1) $(LDFLAGS)

SRC2 = fractal.c draw.c
fractal: $(SRC2) draw.h
	gcc $(CFLAGS) -o fractal $(SRC2) $(LDFLAGS)

clean:
	rm -f test fractal *.o
