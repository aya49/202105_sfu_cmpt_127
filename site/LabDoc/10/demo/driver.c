#include <stdio.h>

#include "image.h"

int main() 
{
  img_t img;
  img_init( &img );
  img_resize( &img, 100, 100, 0 );
  
  // draw a diagonal line
  for( int x=0; x<100; x++ ) 
    img_set_pixel( &img, x,x, 0 );
  
  puts( "done." );
  return 0;
}


