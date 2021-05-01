


/* Initialize the drawing system and create a window of the specified
   size and title */
void draw_startup( char title[], unsigned int width, unsigned int height );

/* Shutdown the drawing system. Closes the window and frees all
   resources */
void draw_shutdown();

void draw_image_grey( uint8_t pixels[], 
		      unsigned int rows,
		      unsigned int cols );

