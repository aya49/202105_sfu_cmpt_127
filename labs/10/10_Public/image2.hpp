/* image2.hpp */

#include <stdint.h> // for uint8_t

class Image {
  
public:
  // I declared these "public" so I can peek at them in the test driver while testing.
  // Once my code works, I transform these data members into "private" and test my code one more time.
  // If I want to peek at them when they are declared "private",
  // I can implement "getters". Check out what getters and setters are!
  unsigned int cols;
  unsigned int rows;
  uint8_t* pixels;
  
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

  /* Load the an image from the file caled "filename", replacing the current
     image size and data. The file is in a format that was saved by save(). 
	 Returns 0 success, else a non-zero error code . */
  int load( const char* filename );
};

