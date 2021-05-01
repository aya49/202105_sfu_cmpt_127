#include <stdio.h>

#include "image.hpp"

int main() 
{
  Image img;
  
  img.resize( 100, 100, 0 );

  // draw a diagonal line
  for( int x=0; x<100; x++ ) 
    img.set_pixel( x, x, 255 );

  puts( "done." );
  return 0;
} 


