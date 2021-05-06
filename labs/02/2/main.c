#include <stdio.h> // for printf()

int main( void )
{
  int num1 = 11;
  int num2 = 12;
  printf( "The max of our numbers is %d.\n", max( num1, num2 ));
  printf( "The min of our numbers is %d.\n", min( num1, num2 ));
  return 0;
}
