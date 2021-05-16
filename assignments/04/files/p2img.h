#include <stdio.h>
#include <stdint.h>

/* Structure type that encapsulates our image: 2D array.
 * the rows represent the indices of the main array,
 * the cols represent the indices of the arrays pointed to by the pointers 
 * in the elements of the main array.
*/
typedef struct { 
    uint8_t* pixels;
    unsigned int rows;
    unsigned int cols;
} img_t;


/* task 02 */

/*
  Save the 2D entire array im into a file called 'filename' in a JSON
  text file array file format that can be loaded by
  img_load_json(). Returns zero on success, or a non-zero error
  code on failure. Arrays of length 0 should produce an output file
  containing an empty array.

  Make sure you validate the parameters before you use them.
  
  The JSON output should be human-readable.

  Examples:

  The following line is a valid JSON 2D array:
  [ [ 100, 200, 300 ],
    [  10,  20,  15 ] ]
  
  The following lines are a valid JSON array:
  [ 
    [ 
      100, 
      200, 
      300 
    ],
    [  
      10,  
      20,  
      15 
    ]
  ]
*/
int img_save_json(img_t* im, const char* filename);


/*
  Load a new 2D array from the file called 'filename', that was
  previously saved using img_save_json(). The file may contain an array
  of length 0. Returns a pointer to a newly-allocated img_t on
  success (even if that array has length 0), or NULL on failure.

  Make sure you validate the parameter before you use it.
*/
img_t* img_load_json(const char* filename);