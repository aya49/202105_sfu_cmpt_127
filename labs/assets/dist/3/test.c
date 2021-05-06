/*
 * test.cc - functions, arrays, pointers, image representation
 * Richard Vaughan 2014
 */

#include <stdlib.h> // for random()
#include <stdint.h> // for explicit integer types, eg. uint8_t
#include <string.h> // for memset()
#include <assert.h>
#include <stdio.h>
#include <time.h>

// include our own drawing functions
// #include "draw.h"
#include "imgops.h"
#include "imgops_reference.h"

uint8_t* black_img( unsigned int w, unsigned int h )
{
  uint8_t* img = malloc( w * h * sizeof(uint8_t) );
  assert(img);
  memset( img, 0, w * h * sizeof(img[0] ));
  return img;
}

uint8_t* white_img( unsigned int w, unsigned int h )
{
  uint8_t* img = malloc( w * h * sizeof(uint8_t) );
  assert(img);
  memset( img, 255, w * h * sizeof(img[0] ));
  return img;
}

void grid( uint8_t* img, int w, int h )
{
  for( unsigned int i=0; i<w; i++ )
    for( unsigned int j=0; j<h; j++ )
      img[i + j*w] = (i+j)%2 ? 100 : 200;
}

uint8_t* grid_img( unsigned int w, unsigned int h )
{
  uint8_t* img = malloc( w * h * sizeof(uint8_t) );
  assert(img);
  grid( img, w, h );
  return img;
}

uint8_t* random_img( unsigned int w, unsigned int h )
{
  uint8_t* img = malloc( w * h * sizeof(uint8_t) );
  assert(img);
  
  for( int i=0; i<w*h; i++ )
    img[i] = rand() % 256;

  return img;
}

// compare two images of the same dimensions
int compare( uint8_t* img1, uint8_t* img2, int w, int h )
{
  assert( img1 );
  assert( img2 );

  for( unsigned int i=0; i<w*h; i++ )
    {
      if( img1[i] < img2[i] ) return 1;
      if( img1[i] > img2[i] ) return 1;
    }

  return 0; // same
}


// compare the images, then free them, then return the comparison result
int cmpfree( uint8_t* img1, uint8_t* img2, int w, int h )
{
  assert( img1 );
  assert( img2 );

  int res = compare( img1, img2, w, h );
  
  //draw_image_grey( img1, w, h );
  //draw_image_grey( img2, w, h );

  free( img1 );
  free( img2 );

  return res;
}

int TestMin(  unsigned int w, unsigned int h )
{
  uint8_t* img1 = random_img( w, h );

  uint8_t res1 =   min( img1, w, h );
  uint8_t res2 = r_min( img1, w, h );

  return res1 != res2;
}

int TestMax(  unsigned int w, unsigned int h )
{
  uint8_t* img1 = random_img( w, h );

  uint8_t res1 =   max( img1, w, h );
  uint8_t res2 = r_max( img1, w, h );

  return res1 != res2;
}

int TestReplaceColor( unsigned int w, unsigned int h )
{
  uint8_t* img1 = random_img( w, h );
  r_set_pixel( img1, w,h, 0,0, 128 );
  r_set_pixel( img1, w,h, 0,1, 128 );

  uint8_t* img2 = r_copy( img1, w, h );
  
    replace_color( img1, w, h, 128, 127 );
  r_replace_color( img2, w, h, 128, 127 );
  
  return cmpfree( img1, img2, w, h );
}




int TestLife( unsigned int w, unsigned int h )
{
  uint8_t* img1 = black_img( w, h );  

  // random speckles
  //  for( int i=0; i<w*h; i++ )
  //img1[i] = rand() % 10 == 0 ? 255 : 0;
  
  //int glider[][2] = { {1,0}, {2,1}, {0,2}, {1,2}, {2,2} };   
  //for( int i=0; i<5; i++ )
  // r_set_pixel( img1, w, h, glider[i][0], glider[i][1], 255 );

  int acorn[][2] = { {2,0}, {4,1}, {1,2}, {2,2}, {5,2},{6,2},{7,2} }; 
  for( int i=0; i<7; i++ )
   r_set_pixel( img1, w, h, w/2 + acorn[i][0], h/2 + acorn[i][1], 255 );

  uint8_t* img2 = r_copy( img1, w, h );
  
  // run a few rounds of Life
  const int rounds = 200;
  
  for( int i=0; i<rounds; i++ )
    { 
        life( img1, w, h );      
      r_life( img2, w, h );
      
      //draw_image_grey( img1, w, h );
      //draw_image_grey( img2, w, h );      
    }  

  return cmpfree( img1, img2, w, h );
}
  

int TestFlipHorizontal( unsigned int w, unsigned int h )
{
  uint8_t* img1 = random_img( w, h );
  uint8_t* img2 = r_copy( img1, w, h );
  
  flip_horizontal( img1, w, h );
  r_flip_horizontal( img2, w, h );
  
  return cmpfree( img1, img2, w, h );
}

int TestFlipVertical( unsigned int w, unsigned int h )
{
  uint8_t* img1 = random_img( w, h );
  uint8_t* img2 = r_copy( img1, w, h );
  
  flip_vertical( img1, w, h );
  r_flip_vertical( img2, w, h );
  
  return cmpfree( img1, img2, w, h );
}

int TestInvert( unsigned int w, unsigned int h )
{
  uint8_t* img1 = random_img( w, h );
  uint8_t* img2 = r_copy( img1, w, h );
  
  invert( img1, w, h );
  r_invert( img2, w, h );
  
  return cmpfree( img1, img2, w, h );
}


int TestHalf( unsigned int w, unsigned int h )
{
  uint8_t* img = random_img( w, h );
  
  uint8_t* hf1 = half( img, w, h );
  uint8_t* hf2 = r_half( img, w, h );

  free( img );
  
  return cmpfree( hf1, hf2, w/2, h/2 );
}

int rtest( uint8_t* img1, uint8_t* img2, unsigned int w, unsigned int h, int x, int y, int cw, int ch, uint8_t col )
{
  draw_rectangle( img1, w, h, x, y, cw, ch, col );
  r_draw_rectangle( img2, w, h, x, y, cw, ch, col );
  
  if( compare( img1, img2, w, h ) == 0 )
    {
      printf( "Pass on draw_rectangle( img, %u, %u, %d, %d, %d, %d, %d )\n",
	      w,h,x,y,cw,ch,(int)col );
      return 0;
    }

  printf( "Failed on draw_rectangle( img, %u, %u, %d, %d, %d, %d, %d )\n",
	  w,h,x,y,cw,ch,(int)col );
  return 1;
}


int TestRectangle( unsigned int w, unsigned int h )
{
  printf( "Rectangle...\n" );

  uint8_t* img1 = black_img( w, h );
  uint8_t* img2 = r_copy( img1, w, h );
  
  int cx = 10;
  int cy = 10;
  int cw = 0;
  int ch = 0;
  int col = 255;

  rtest( img1, img2, w, h, cx, cy, cw, ch, col );
  
  cw = 5;
  
  rtest( img1, img2, w, h, cx, cy, cw, ch, col );
  
  ch = -5;
  
  rtest( img1, img2, w, h, cx, cy, cw, ch, col );
  
  for( int i=0; i<100; i++ )
    {
      cx = (rand() % (2*w)) -w/2;
      cy = (rand() % (2*h)) -h/2;
      cw = (rand() % (2*w)) -w;
      ch = (rand() % (2*h)) -h;
      col = rand() % 255;

      if( rtest( img1, img2, w, h, cx, cy, cw, ch, col ) )
	break;
    }
    puts( "rectangle tests done" );
  return cmpfree( img1, img2, w, h );
}   

void swapint( int *a, int *b )
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int TestRegionSet( unsigned int w, unsigned int h )
{
 uint8_t* img1 = random_img( w, h );
 uint8_t* img2 = r_copy( img1, w, h );
 
 for( int i=0; i<100; i++ )
   {
     int x = rand() % w;
     int y = rand() % h;
     int x1 = rand() % w;
     int y1 = rand() % h;
     int col = rand() % 255;
     
     if( x1 < x )
       swapint( &x1, &x );

     if( y1 < y )
       swapint( &y1, &y );

     region_set( img1, w, h, x,y, x1, y1, col );
     r_region_set( img2, w, h, x,y, x1, y1, col );
   }
 
 return cmpfree( img1, img2, w, h );
}

int TestRegionCopy( unsigned int w, unsigned int h )
{
  uint8_t* img1 = random_img( w, h );
  
  int res = 0;

  for( int i=0; i<100000; i++ )
    {
      int x = rand() % w;
      int y = rand() % h;
      int x1 = rand() % w;
      int y1 = rand() % h;
      
      if( x1 < x )
	swapint( &x1, &x );
      
      if( y1 < y )
	swapint( &y1, &y );
      
      uint8_t* cp1 =   region_copy( img1, w, h, x,y, x1, y1 );
      uint8_t* cp2 = r_region_copy( img1, w, h, x,y, x1, y1 );
      
      int emptyregion = ( x1-x == 0 || y1-y == 0 );
      
      if( emptyregion )
	{
	  if( cp1 == 0 )
	    continue;
	  
	  printf("region_copy(): did not return null for empty region");
	  return 1;
	}
      else if( cp1 == 0 )
	{
	  printf("region_copy(): returned null for non-empty region" );
	  return 1;
	}
      
      assert( cp1 );
      assert( cp2 );

      unsigned int rw = x1-x;
      unsigned int rh = y1-y;

      res = compare( cp1, cp2, rw, rh );

      //printf( "res %d\n", res );
      //draw_image_grey( cp1, rw, rh );
      //draw_image_grey( cp2, rw, rh ); 

      free( cp1 ); 
      free( cp2 );
      
      if( res != 0 )
	break;
    }
  
  free( img1 ); 
  return res;
}

int TestRegionIntegrate( unsigned int w, unsigned int h )
{
  uint8_t* img1 = random_img( w, h );
  
  int res = 0;

  for( int i=0; i<1000; i++ )
    {
      int x = rand() % w;
      int y = rand() % h;
      int x1 = rand() % w;
      int y1 = rand() % h;
      
      if( x1 < x )
	swapint( &x1, &x );
      
      if( y1 < y )
	swapint( &y1, &y );
      
      unsigned long sum1 =   region_integrate( img1, w, h, x,y, x1, y1 );
      unsigned long sum2 = r_region_integrate( img1, w, h, x,y, x1, y1 );


      res = sum1 == sum2 ? 0 : 1;

      if( res != 0 )
	break;
    }
  
  free( img1 ); 
  return res;
}



int TestCircle( unsigned int w, unsigned int h )
{
  uint8_t* img1 = black_img( w, h );
  uint8_t* img2 = r_copy( img1, w, h );
    
  for( int i=0; i<100; i++ )
    {
      int cx = (rand() % (2*w)) -w/2;
      int cy = (rand() % (2*h)) -h/2;
      int r = rand() % w/3;
      int col = rand() % 255;
      
      draw_circle( img1, w, h, cx, cy, r, col ); 
      r_draw_circle( img2, w, h, cx, cy, r, col ); 
    }
  
  for( int i=10; i>0; i-- )
    {
      draw_circle( img1, w, h, w/2, h/2, i, 255/i ); 
      r_draw_circle( img2, w, h, w/2, h/2, i, 255/i ); 
    }

  // r=0 
   draw_circle( img1, w, h, w/2, h/2, 0, 0 );  
   r_draw_circle( img2, w, h, w/2, h/2, 0, 0 );  


  return cmpfree( img1, img2, w, h );
}  

  

int TestLocateColor( unsigned int w, unsigned int h )
{
  uint8_t* img1 = random_img( w, h );

  for( int i=0; i<20; i++ )
    {
      unsigned int v1=0, x1=0, y1=0;
      unsigned int v2=0, x2=0, y2=0;
      

      // choose a color at random
      uint8_t c = rand() % 256;

      v1 =  locate_color( img1, w, h, c,  &x1, &y1 );
      v2 =  r_locate_color( img1, w, h, c,  &x2, &y2 );
      
      if( v1 != v2 ||
	  x1 != x2 ||
	  y1 != y2 ) 
	{
	  free(img1);
	  return 1;
	}
    }
 
  free(img1);
  return 0; // OK!
}

typedef int (*testf_t)(unsigned int, unsigned int);

int Test( const char* name, testf_t f, unsigned int w, unsigned int h )
{
  printf( "%s ", name ); 
  fflush(stdout);

  int res = (*f)( w, h );

  printf( "\t%s\n", res == 0 ? "pass" : "fail <--" );
  
  return res;
}

int main( int argc, char* argv[] )
{
  srand( time(0) );

  unsigned int iw  = 100;
  unsigned int ih = 100; 

  // unsigned int ww  = iw;
  // unsigned int wh = iw; 
 
  int test = -1; // run all tests


  if( argc >= 3)
    {
      iw  = atoi( argv[1] );
      ih = atoi( argv[2] );
    }
  
  /* if( argc >= 5 ) */
  /*   { */
  /*     ww  = atoi( argv[3] ); */
  /*     wh = atoi( argv[4] ); */
  /*   } */

  

  // choose a specific test
  if( argc >= 4 )
    {
      test = atoi( argv[3] );
    }

  // initialize the graphics system
  //draw_startup( (char*)"Grey Array", ww, wh );
  
  // printf( "iw %u ih %u\n", iw, ih );


  int fail = 0;

  switch( test )
    {
    case 1:
      fail += Test( "min", TestMin, iw, ih );
      fail += Test( "max", TestMax, iw, ih );
      fail += Test( "replace_color", TestReplaceColor, iw, ih );
      break;
    case 2:
      fail += Test( "flip_horizontal", TestFlipHorizontal, iw, ih );
      fail += Test( "flip_vertical", TestFlipVertical, iw, ih );
      break;
    case 3:
      fail += Test( "locate_color", TestLocateColor, iw, ih );
      break;
    case 4:
      fail += Test( "invert", TestInvert, iw, ih );
      break;
    case 5:
      fail += Test( "half", TestHalf, iw, ih );
      break;
    case 6:
      puts( "Task 6 was missing - no task" );
      break;
    case 7:
      fail += Test( "region_set", TestRegionSet, iw, ih );
      break;
    case 8:
      fail += Test( "region_integrate", TestRegionIntegrate, iw, ih );
      break;
    case 9:
      fail += Test( "region_copy", TestRegionCopy, iw, ih );
      break;
    case 10:
      fail += Test( "draw_rectangle", TestRectangle, iw, ih );
      break;
    case 11:
      fail += Test( "draw_circle", TestCircle, iw, ih );
      break;
    case 12:
      fail += Test( "life", TestLife, iw, ih );
      break;
    default:
      puts( "Shouldn't reach here" );
    }

  if( fail > 0 )
    printf( "--\n%d functions failed their tests.\n", fail );
  else
    printf( "--\nAll tests passed.\n" );

  
  // finalize the graphics system, freeing its resources
  //draw_shutdown();

  return fail;
}

