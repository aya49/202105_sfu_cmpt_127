/*
 * test.cc - functions, arrays, pointers, image representation
 * Richard Vaughan 2014 - 2015
 */

#include <stdint.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h>

// image drawing functions
#include "draw.h"

// Generate a Mandelbrot Set fractal:
// See http://en.wikipedia.org/wiki/Mandelbrot_set
void MandelbrotSet( uint8_t* img, 
		    uint32_t width, 
		    uint32_t height )
{
  // for all pixels in the image
  for( uint32_t py=0; py<height; py++ ) 
    for( uint32_t px=0; px<width; px++ ) 
      {
	// scale the pixel coordinate to the interesting region
	double x0 = (px/(double)width) * 2.5 - 2.0;
	double y0 = (py/(double)height) * 2.0 - 1.0;
	
	// run the Mandlebrot process and see if this point converges
	double x = 0.0;
	double y = 0.0;
	
	uint32_t iteration = 0;
	while( x*x + y*y < 2*2  &&  iteration < 256 )
	  {
	    double xtemp = x*x - y*y + x0;
	    y = 2.0 * x * y + y0;
	    x = xtemp;
	    iteration++;
	  }
	
	// the number of iterations determines the color of the pixel
	img[ px + py*width] = 255 - iteration;
      }
}

int main( int argc, char* argv[] )
{
  const unsigned int width  = 500;
  const unsigned int height = 400; 

  // initialize the graphics system
  draw_startup( "Mandelbrot Set", width, height );
  
  // allocate and zero an array for our image
  uint8_t* img = malloc( width * height * sizeof(uint8_t) );
  memset( img, 0, width * height * sizeof(img[0] ));
  
  printf( "Generating fractal..." ); 
  fflush(stdout);
  
  MandelbrotSet( img, width, height );
  
  printf( "done\n" ); 
  
  // draw the array as a grey-scale image in the window. This function
  // waits for a to click or press a button in the window before
  // returning
  draw_image_grey( img, width, height );
  
  // finalize the graphics system, freeing its resources
  draw_shutdown();

  // every malloc() should have a matching free()
  free(img);

  return 0;
}

