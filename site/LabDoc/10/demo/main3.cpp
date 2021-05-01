#include <stdint.h> // for uint8_t
#include <cstdio>   // for NULL
#include <string.h>
#include "image3.hpp"

int main( int argc, char* argv[] )
{
  uint8_t colour;
  
  /* Constructs an image of 0x0 pixels. TESTING Constructor Image( ) */
  Image photo;   
  
  
  photo.resize( 10, 5, 33 );
  photo.get_pixel( 2, 2, &colour );
  printf("Colour at (%d, %d) is %d\n", 2, 2, colour );

  photo.save( "test1.file" );
  photo.load( "test1.file" ); 
  
  photo.set_pixel( 0, 0, 255 );
  photo.get_pixel( 0, 0, &colour );
  printf("Colour at (%d, %d) is %d\n", 0, 0, colour );
  
  photo.get_pixel( 2, 2, &colour );
  printf("Colour at (%d, %d) is %d\n", 2, 2, colour );

  photo.resize( 6, 6, 111 );
  
  photo.save( "test2.file" );
  photo.load( "test2.file" );
  
  /* Frees all memory allocated for img. TESTING Destructor ~Image( ) */

}




