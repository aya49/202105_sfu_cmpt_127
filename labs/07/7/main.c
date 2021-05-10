#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main( int argc, char* argv[] )
{
  // test the create function
  list_t* list = list_create();

  // check to see if the create function did everything it was supposed to
  if( list == NULL )
    {
      printf( "list_create(): create failed to malloc\n" );
      return 1;
    }

  if( list->head != NULL )
    {
      printf( "list_create(): head is not null!\n" );
      return 1;
    }

  if( list->tail != NULL )
    {
      printf( "list_create(): tail is not null!\n" );
      return 1;
    }

  // now test all the other functions (except list_print) to see if
  // they do what they are supposed to

  // you code goes here
  
  return 0; // tests pass
}

