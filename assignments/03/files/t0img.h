#include <stdio.h>

/* Structure type that encapsulates our image: 2D array.
 * the rows represent the indices of the main array,
 * the cols represent the indices of the arrays pointed to by the pointers 
 * in the elements of the main array.
*/
struct { 
    uint8_t* pixels;
    unsigned int rows;
    unsigned int cols;
} img_t;

/* A type for returning status codes */
typedef enum {
    IMG_OK,
    IMG_BADARRAY,
    IMG_BADCOL,
    IMG_BADROW,
    IMG_BADALLOC,
    IMG_NOTFOUND
} img_result_t;
```


/* task 01 */

// Create a new img_t with initial size rows and cols. If successful
// (i.e. memory allocation succeeds), returns a pointer to a
// newly-allocated img_t.  If unsuccessful, returns a null pointer.
img_t* img_create(unsigned int rows, unsigned int cols);

// Frees all memory allocated for im. If the pointer is null, do
// nothing. If the im->pixels is null, do not attempt to free it.
void img_destroy(img_t* im);


/* task 02 */

// If row or col is valid, set the value at im->pixels[row][col] to val and return
// IMG_OK. Otherwise, leave the array unmodified and return
// return IMG_BADROW if the row is invalid, otherwise, return IMG_BADCOL if the col is invalid. 
// If im is null, return IMG_BADARRAY.
img_result_t img_set(img_t* im, unsigned int row, unsigned int col, int val);

// If row and col is valid and val is non-null, set *val to im->pixels[row][col] and return
// IMG_OK. Otherwise do not modify *val and return
// IMG_BADCOL if the col is invalid and return IMG_BADROW if the row is invalid. 
// If im is null, return IMG_BADARRAY.
img_result_t img_get(const img_t* im, unsigned int row, unsigned int col, int* val);


/* task 03 */

// Return a duplicate of im, allocating new storage for the duplicate
// pixels (we call this a "deep copy"). If unsuccessful (i.e. memory
// allocation for the copy fails, or im is null), return a null pointer. 
img_t* img_copy(const img_t* im);


/* task 04 */

// Find the first occurrence of the target in the array, searching from
// left to right, top to bottom (e.g. search the entire first row, 
// then seach the entire second row, etc.). 
// If the target is found and i is non-null, set *i to the
// location row and set *j to the location col
// and return IMG_OK. If target does not occur in
// the array, leave *i and *j unmodified and return IMG_NOTFOUND. If im is
// null, return IMG_BADARRAY.
img_result_t img_find(img_t* im, int target, int* i, int* j);


/* task 05 */

// Get a deep copy of a portion of im from first_row to last_row, and first_col to last_col
// inclusive e.g. if first_row = 3, last_row = 6, first_col = 2, last_col = 3, 
// the resulting 2D array would be 4 rows and two cols in size. 
// If successful, return a pointer to a newly-allocated
// img_t containing a copy of the specified section. If an error
// occurs, i.e. im is null, 'first' or 'last' are out of bounds, 
// 'last' < 'first', or memory allocation fails, return a null pointer.
img_t* img_copy_subarray(img_t* im, unsigned int first_row, unsigned int last_row, 
                                    unsigned int first_col, unsigned int last_col);