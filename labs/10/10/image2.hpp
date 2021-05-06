/* image2.hpp */

#include <stdint.h> // for uint8_t

class Image {
  
private:
  unsigned int cols;
  unsigned int rows;
  uint8_t* pixels;

public:  
  /* Constructs an image of 0x0 pixels. */
  Image();
  
  /* Frees all memory allocated for this Image object. */
  ~Image();
 
  /* Changes the size of an image, allocating memory as necessary, and
     setting all pixels to "fillcolour". Returns 0 on success, or a non-zero error code.*/ 
  int resize( unsigned int width, unsigned int height, uint8_t fillcolour );
  
  /* Sets the colour of the pixel at (x,y) to "colour". Returns 0 on success, else a non-zero 
     error code. If (x,y) is not a valid pixel, the call fails and the image does not change.*/
  int set_pixel( unsigned int x, unsigned int y, uint8_t colour );
  
  /* Gets the colour of the pixel at (x,y) and stores it at the address pointed to 
     by "colourp". Returns 0 on success, else a non-zero error code. */
  int get_pixel( unsigned int x, unsigned int y, uint8_t* colourp );
  
  /* Saves the image in the file called "filename" using a format that can be
     loaded by load(). Returns 0 on success, else a non-zero error code. */
  int save( const char* filename );

  /* Load the image from the file called "filename", replacing the current
     image size and data. The file is in a format that was saved by save(). 
	 Returns 0 success, else a non-zero error code. */
  int load( const char* filename );
};

