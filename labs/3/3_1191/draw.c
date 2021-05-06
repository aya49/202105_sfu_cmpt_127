/*
 * draw.c 
 *
 * minimal graphics code to render a uint8_t array in an X11 window
 * and wait for a button or key press
 * 
 * Richard Vaughan, 2014
 */

#include <stdio.h>
#include <stdlib.h>		/* getenv(), etc. */
#include <unistd.h>		/* sleep(), etc.  */
#include <stdint.h>             /* uint8_t */
#include <math.h>               /* for floor() and ceil() */
#include <X11/Xlib.h>
#include <assert.h>
#include <unistd.h>

// these file-scope variables are used by the graphics system

static Display* display = NULL; // pointer to X Display structure.           
static GC gc = NULL; // graphics context used for drawing in our window.		  
static Window win = 0; // handle of our window

// return the X11 pixel value that corresponds to our grey value (g)
unsigned int pixel_grey_uint8( uint8_t grey )
{
  int screen_range = (1 << ( DefaultDepth(display, DefaultScreen(display) ) / 3));
    
  double scale = (double)screen_range / 256.0;
  
  unsigned int col = (unsigned int)(grey*scale);

  return (unsigned int)( col * screen_range * screen_range + 
			 col * screen_range +
			 col );
}

void image_grey( uint8_t pixels[], 
		 unsigned int image_width,
		 unsigned int image_height )
{
  /* this variable will contain the attributes of the window. */
  XWindowAttributes win_attr;
  
  /* query the window's attributes. */
  Status rc = XGetWindowAttributes(display, win, &win_attr);
  assert(rc != 0 );

  const double px = win_attr.width / (double)image_width;
  const double py = win_attr.height / (double)image_height;
  
  Pixmap pixmap;
  
  /* this variable will contain the ID of the root window of the screen */
  /* for which we want the pixmap to be created.                        */
  Window root_win = DefaultRootWindow(display);
  
  /* this variable will contain the color depth of the pixmap to create. */
  /* this 'depth' specifies the number of bits used to represent a color */
  /* index in the color map. the number of colors is 2 to the power of   */
  /* this depth.                                                         */
  int depth = DefaultDepth(display, DefaultScreen(display));

  /* create a new pixmap, with a width of 30 pixels, and height of 40 pixels. */
  pixmap = XCreatePixmap(display, root_win, win_attr.width, win_attr.height, depth);

  for( unsigned int x=0; x < image_width; x++ )
    for( unsigned int y=0; y < image_height; y++ )
      {
	XSetForeground(display, gc, 
		       pixel_grey_uint8( pixels[y*image_width+x] ) );
	
	XFillRectangle(display, pixmap, gc, 
		       floor(x*px), floor(y*py), ceil(px), ceil(py+0.5) );
      }		    
  
  // copy the pixmap into the window
  XCopyArea( display, pixmap, win, gc,
	     0, 0,
	     win_attr.width, win_attr.height,
	     0, 0);

  XFreePixmap(display, pixmap);
}      


void draw_image_grey( uint8_t pixels[], 
		      unsigned int cols,
		      unsigned int rows )
{
  // draw the image
  image_grey( pixels, cols, rows );	  
  
  //return;

  XEvent an_event;
  int thing_pressed = 0;
  
  XSelectInput(display, win, ExposureMask | ButtonPressMask | KeyPressMask );
  
  printf( "(click on the image to continue)\n");

  /* wait for events, keep drawing the image in response window
     changes until a key or button is pressed */
  while( ! thing_pressed ) 
    {
      XNextEvent(display, &an_event);

      switch( an_event.type ) 
	{
	case Expose:	  
	  if( an_event.xexpose.count == 0 ) // last outstanding event
	    image_grey( pixels, cols, rows );	  
	  break;
	         
	case ButtonPress:
	case KeyPress:
	  puts( "(button/key pressed)");
	  thing_pressed = 1; // we'll exit the loop when a button is pressed
	  break;
	  
	default: // unknown event type - ignore it.
	  break;
	}
    }
  
  // flush all pending requests to the X server.
  XFlush(display);
} 


void draw_startup( char title[], unsigned int width, unsigned int height )
{
  // open connection with the X server on the default display
  const char *display_name = getenv("DISPLAY");   
  
  display = XOpenDisplay(display_name);
  if (display == NULL) {
    fprintf(stderr, "%s: cannot connect to X server '%s'\n",
            title, display_name);
    exit(1);
  }

  // get the geometry of the default screen for our display. 
  const int screen_num = DefaultScreen(display);
  
  win = XCreateSimpleWindow(display, 
			    RootWindow(display, DefaultScreen(display)),
			    0, 0, width, height, 2,
			    BlackPixel(display, screen_num),
			    WhitePixel(display, screen_num));
  assert( win );

  XSetWindowAttributes win_attr;
  win_attr.backing_store = 1;
  XChangeWindowAttributes( display, win, CWBackingStore, &win_attr );

  XMapWindow(display, win);

  unsigned long valuemask = 0;		  
  XGCValues values;			
  
  if( (gc = XCreateGC(display, win, valuemask, &values)) < 0 )
    fprintf(stderr, "XCreateGC: \n");
  
  XSetForeground(display, gc, BlackPixel(display, screen_num));
  XSetBackground(display, gc, WhitePixel(display, screen_num));

  /* flush all pending requests to the X server. */
  XFlush(display);
}

void draw_shutdown()
{
  /* close the connection to the X server. */
  XCloseDisplay(display);
}

