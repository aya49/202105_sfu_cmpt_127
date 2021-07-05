#include <stdio.h> // for printf()
#include "t1funcs.h"

int main(void) {
  int num1 = 6;
  int num2 = 2;

  printf( "The sum of our numbers is %d.\n", sum(num1, num2));
  printf( "The quotient of our numbers is %d.\n", qtt(num1, num2));
  
  return 0;
}

