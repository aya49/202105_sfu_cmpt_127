#include <assert.h>
#include <math.h>

#include "imgops.h"

double distance( double x1, double y1, double x2, double y2 )
{
  return( hypot( y2-y1, x2-x1 ));
}

void draw_circle( uint8_t array[], 
		  unsigned int cols, 
		  unsigned int rows, 
		  int x,
		  int y,
		  int r,
		  uint8_t color )
{
  assert( r >= 0 );
  if( r == 0 ) return;
  
  // for every pixel that is inside the image AND inside a square that
  // contains the circle exactly (for small circles this is much
  // faster than scanning the whole image)
  for( double xx = fmax(0,x-r); xx < fmin(x+r+1,cols); xx++ )
    for( double yy = fmax(0,y-r); yy< fmin(y+r+1,rows); yy++ )
      {
	// if any of the pixel's corners are within radius r of the
	// circle centre
	if( distance( xx, yy, x+0.5, y+0.5 ) < r ||
	    distance( xx+1, yy, x+0.5, y+0.5 ) < r ||
	    distance( xx+1, yy+1, x+0.5, y+0.5 ) < r ||
	    distance( xx, yy+1, x+0.5, y+0.5 ) < r 
	    ) 
	  set_pixel( array, cols, rows, xx, yy, color ); // draw the pixel
      }
}
