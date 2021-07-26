#include <stdio.h>
#include <stdint.h>

/* Structure type that encapsulates our image: 2D array.
 * the rows represent the indices of the main array,
 * the cols represent the indices of the arrays pointed to by the pointers 
 * in the elements of the main array.
*/
typedef struct { 
    uint8_t** pixels;
    unsigned int rows;
    unsigned int cols;
    unsigned int reserved_rows;
    unsigned int reserved_cols;
} imgr_t;

/* A type for returning status codes */
typedef enum {
    IMGR_OK,
    IMGR_BADCOL,
    IMGR_BADROW,
    IMGR_BADALLOC,
    IMGR_EMPTY
} imgr_result_t;

/* ALL THESE FUNCTIONS REQUIRE A VALID IMGR_T POINTER AS THEIR
   FIRST PARAMETER. THEY SHOULD FAIL ON ASSERTION IF THIS POINTER IS NULL */

/* task 01 */

// Create a new imgr_t with initial size rows, cols, 
// and their reserved counterpart (initialize rows and reserved_rows 
// to be the same, and cols and reserved_cols to be the same). 
// If successful (i.e. memory allocation succeeds), returns a pointer to a
// newly-allocated imgr_t.  If unsuccessful, returns a null pointer.
imgr_t* imgr_create(unsigned int rows, unsigned int cols);

// Frees all memory allocated for im. If the pointer is null, do
// nothing. If the im->pixels is null, do not attempt to free it.
void imgr_destroy(imgr_t* im);

/* task 02 */

// Append val to the end of the 2D array pixels.
// Use preallocation if there is not enough space reserved in the 2D array
// i.e. if all reserved_rows x reserved_cols elements are filled up,
// - double the size of rows if expand_row != 0
// - double the size of cols if expand_row = 0
// both options need to be tested in your t0.c.
// return IMGR_OK if successful.
// return IMGR_BADALLOC if `realloc()` failed.
imgr_result_t imgr_append(imgr_t* im, int expand_row, int val);

/* task 03 */

// Remove the element at index (i,j) (row, col) from the 2D array pixels, 
// reducing the number of elements
// stored in the 2D array by one. The order of points in the array may change.
// Use unstable remove.
// If removing the element causes an entire row and/or column to be empty, 
// decrement the field rows and/or cols as necessary.
// If successful, return IMGR_OK, else return IMGR_BADROW if you cannot find the row i
// or IMGR_BADCOL if you could find row i but couldn't find col j. 
imgr_result_t imgr_remove(imgr_t* im, unsigned int i, unsigned int j);

/* task 04 */

// Save the 2D entire array im into a file called 'filename' in a JSON
// text file array file format that can be loaded by
// imgr_load_json(). Returns zero on success, or a non-zero error
// code on failure. Arrays of length 0 should produce an output file
// containing an empty array.
// 
// Make sure you validate the parameters before you use them.
// 
// The JSON output should be human-readable.
// 
// Examples:
// 
// The following line is a valid JSON 2D array:
// [ [ 100, 200, 300 ],
//   [  10,  20,  15 ] ]
// 
// The following lines are a valid JSON array:
// [ 
//   [ 
//     100, 
//     200, 
//     300 
//   ],
//   [  
//     10,  
//     20,  
//     15 
//   ]
// ]
int imgr_save_json(imgr_t* im, const char* filename);


// Load a new 2D array from the file called 'filename', that was
// previously saved using imgr_save_json(). The file may contain an array
// of length 0. Returns a pointer to a newly-allocated imgr_t on
// success (even if that array has length 0), or NULL on failure.
// 
// Make sure you validate the parameter before you use it.
imgr_t* imgr_load_json(const char* filename);


