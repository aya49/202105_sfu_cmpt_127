/* png.h - load a PNG image from a file into an array. 
   Richard Vaughan 2015.
 */

/* Load a PNG image file from disk into memory. 

   @name        filename
   @outWidth    reports the image width in pixels
   @outHeight   reports the image height in pixels
   @outDepth    reports the image depth in bytes
   @outHasAlpha if non-zero, the image has an alpha channel 
   @outData     pointer to the newly-allocated raw image data. 

   Caller is responsible for freeing outData.
*/
int LoadPngImage(char *name, 
		 uint32_t *outWidth, 
		 uint32_t *outHeight, 
		 uint32_t *outDepth, 
		 int *outHasAlpha, 
		 uint8_t **outData);
