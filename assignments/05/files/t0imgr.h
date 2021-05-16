#include <stdio.h>

/* Structure type that encapsulates our image: 2D array.
 * the rows represent the indices of the main array,
 * the cols represent the indices of the arrays pointed to by the pointers 
 * in the elements of the main array.
*/
typedef struct { 
    uint8_t* pixels;
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
} img_result_t;

/* ALL THESE FUNCTIONS REQUIRE A VALID IMGR_T POINTER AS THEIR
   FIRST PARAMETER. THEY SHOULD FAIL ON ASSERTION IF THIS POINTER IS NULL */

/* task 01 */

// Create a new imgr_t with initial size rows, cols, 
// and their reserved counterpart (initialize rows and reserved_rows 
// to be the same, and cols and reserved_cols to be the same). 
// If successful (i.e. memory allocation succeeds), returns a pointer to a
// newly-allocated imgr_t.  If unsuccessful, returns a null pointer.
imgr_t* img_create(unsigned int rows, unsigned int cols);

// Frees all memory allocated for im. If the pointer is null, do
// nothing. If the im->pixels is null, do not attempt to free it.
void imgr_destroy(img_t* im);

/* task 02 */

// Append val to the end the 2D array pixels. If successful, return 0, else return 1.
// Use preallocation where if there is not enough space reserved in the 2D array
// i.e. if all reserved_rows x reserved_cols elements are filled up,
// - double the size of rows if expand_row != 0
// - double the size of cols if expand_row = 0
// both options need to be tested in your t0.c.
// return IMGR_OK if successful.
// return IMGR_BADALLOC if `realloc()` failed.
img_result_t imgr_append(imgr_t* im, int expand_row = 0, int val);

/* task 03 */

// Remove the point at index (i,j) (row, col) from the 2D array pixels, 
// reducing the number of elements
// stored in the 2D array by one. The order of points in the array may change.
// Use unstable remove.
// If successful, return IMGR_OK, else return IMGR_BADROW if you cannot find the row i
// or IMGR_BADCOL if you could find row i but couldn't find col j. 
img_result_t imgr_remove(imgr_t* im, unsigned int i, unsigned int j);


