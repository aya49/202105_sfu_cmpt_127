#include <stdlib.h>


typedef struct point {
  double x, y, z;
} point_t;

typedef struct {
  // number of points in the array
  size_t len;
  
  // pointer to an array of point_t structs
  // There is space for 'reserved' point_t structs, 
  // but 'len' point_t structs have been used so far.
  point_t* points;
  
  // to be discussed in class - see Demo
  size_t reserved; 
  
} point_array_t;


/* ALL THESE FUNCTIONS REQUIRE A VALID POINT_ARRAY_T POINTER AS THEIR
   FIRST PARAMETER. THEY SHOULD FAIL ON ASSERTION IF THIS POINTER IS NULL */

/* practice 01 */

// Safely initalize an empty array structure.
void point_array_init(point_array_t* pa);

/* practice 02 */

// Resets the array to be empty, freeing any memory allocated if necessary.
void point_array_reset(point_array_t* pa);

/* practice 03 */

// Append a point to the end of an array. If successful, return 0, else return 1.
int point_array_append(point_array_t* pa, point_t* p);

/* practice 04 */

// Remove the point at index i from the array, reducing the number of elements
// stored in the array by one. The order of points in the array may change.
// If successful, return 0, else return 1. 
int point_array_remove(point_array_t* pa, unsigned int i);


