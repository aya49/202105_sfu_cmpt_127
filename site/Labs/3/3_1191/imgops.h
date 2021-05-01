/*
 * imageops.h - Simple operations on images header
 *
 * C laboratory exercises.
 * Richard Vaughan, 2014.
 */

/* get the value in the array at coordinate (x,y)
 */
uint8_t get_pixel( const uint8_t array[], 
		   unsigned int cols, 
		   unsigned int rows,
		   unsigned int x,
		   unsigned int y );

/* set the pixel at coordinate {x,y} to the specified color
 */
void set_pixel( uint8_t array[], 
		unsigned int cols, 
		unsigned int rows,
		unsigned int x,
		unsigned int y,
		uint8_t color );

/* Set every pixel to 0 (black) 
 */
void zero( uint8_t array[],
	   unsigned int cols,
	   unsigned int rows );

/*
  Returns a pointer to a freshly allocated array that contains the
  same values as the original array, or a null pointer if the
  allocation fails. The caller is responsible for freeing the array
  later.
*/
uint8_t* copy( const uint8_t array[], 
	       unsigned int cols, 
	       unsigned int rows );

/* Return the darkest color that appears in the array; i.e. the
   smallest value
*/
uint8_t min( const uint8_t array[], 
	     unsigned int cols, 
	     unsigned int rows );

/* Return the lightest color that appears in the array; i.e. the
   largest value
*/
uint8_t max( const uint8_t array[], 
	     unsigned int cols, 
	     unsigned int rows );

/* Replace every instance of pre_color with post_color.
 */
void replace_color(  uint8_t array[], 
		     unsigned int cols, 
		     unsigned int rows,
		     uint8_t pre_color,
		     uint8_t post_color );

/* flip the image, left-to-right, like in a mirror.
 */
void flip_horizontal( uint8_t array[], 
		      unsigned int cols, 
		      unsigned int rows );

// flip the image top-to-bottom.
void flip_vertical( uint8_t array[], 
		    unsigned int cols, 
		    unsigned int rows );

/* Find the first coordinate of the first pixel with a value that
   equals color. Search from left-to-right, top-to-bottom. If it is
   found, store the coordinates in *x and *y and return 1. If it is
   not found, return 0.
*/
int locate_color(  const uint8_t array[], 
		   unsigned int cols, 
		   unsigned int rows,
		   uint8_t color,
		   unsigned int *x,
		   unsigned int *y );

/* Invert the image intensities, so that black becomes white and vice
   versa, and light shades of grey become the corresponding dark
   shade.
*/
void invert( uint8_t array[], 
	     unsigned int cols, 
	     unsigned int rows );

/* Multiply every pixel by scale_factor, in order to brighten or
   darken the image.  Resulting values are rounded to the nearest
   integer (0.5 rounded up) and any value over 255 is thresholded to
   255.
*/
void scale_brightness( uint8_t array[],
		       unsigned int cols,
		       unsigned int rows,
		       double scale_factor );

/* Normalize the dynamic range of the image, i.e. Shift and scale the
   pixel colors so that that darkest pixel is 0 and the lightest pixel
   is 255. 
*/
void normalize( uint8_t array[],
		unsigned int cols,
		unsigned int rows );

/* Return a new image of size rows/2 by cols/2. If the original image
   has an odd number of columns, ignore its rightmost column. If the
   original image has an odd number of rows, ignore its bottom row.
   The value of a pixel at (p,q) in the new image is the arithmentic
   mean of the 2x2 square of pixels starting from (2*p,2*q) in the
   original image.
*/
uint8_t* half( const uint8_t array[], 
	       unsigned int cols, 
	       unsigned int rows );


/* -------------------------------------------------
   OPERATIONS ON IMAGE SUB-REGIONS

  These functions operate only on a rectangular region of the array
  defined by a (left,top) corner (i.e. closer to the image origin) and
  (right,bottom) corner (i.e. further from the image origin).
  
  The rectangle edges of a rectangular region are aligned with the x,y axes. 

  The region includes all the columns from [left, right-1] inclusive,
  and all the rows from [top, bottom-1] inclusive.
  
  In every case, you may assume that left <= right and top <= bottom:
  do not need to test for this.

  The area of the region is right-left * bottom-top pixels, which
  implies that if left == right or top == bottom, the region has no
  area and is defined as "empty". Each function notes how to handle
  empty regions.
*/

/* Set every pixel in the region to color. If the region is empty, the
   image must be unchanged.
*/
void region_set( uint8_t array[], 
		 unsigned int cols, 
		 unsigned int rows,
		 unsigned int left,
		 unsigned int top,
		 unsigned int right,
		 unsigned int bottom,
		 uint8_t color );

/* Return the sum of all the pixels in the region. Notice the large
   return type to handle potentially large numbers. Empty regions
   return the sum 0.
*/
unsigned long int region_integrate( const uint8_t array[], 
				    unsigned int cols, 
				    unsigned int rows,
				    unsigned int left,
				    unsigned int top,
				    unsigned int right,
				    unsigned int bottom );

/* Get a new image which is a copy of the region. Empty regions return
   a null pointer. If memory allocation fails, return a null
   pointer. The caller is responsible for freeing the returned array.
*/
uint8_t* region_copy( const uint8_t array[], 
		      unsigned int cols, 
		      unsigned int rows,
		      unsigned int left,
		      unsigned int top,
		      unsigned int right,
		      unsigned int bottom );
