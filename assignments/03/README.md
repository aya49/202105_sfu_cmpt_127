# Assignment 03: 2D arrays, dynamic memory allocation, and structures

Download the files for this assignment [here](./files.zip) (or from the [CMPT 127 D100/D200/D300 Canvas page](https://canvas.sfu.ca/courses/62984) > Assignments > 01).

**Remember**:
- Reference [lab 03](../../labs/03) (on 2D arrays) and [lab 04](../../labs/04) for help!
- DO THE PRACTICE problems! They **directly** help you do the assignment tasks!
- Assignments are to be done individually.
- You may submit/resubmit the assignment on repl.it as many times as you want before the designated due date.
- The internet is your friend :) Search for documentation online and make sure to understand why things work the way they do!

**Contents**: for this assignment, you will complete the following tasks.
- [Task 01](#task-01)
- [Task 02](#task-02)
- [Task 03](#task-03)
- [Task 04](#task-04)

Your assignment will be graded according to this [**marking rubric**](#marking-rubric).

## Task 01-05

**REQUIREMENT**: you will write your program to two files: `t0img.c` `t0.c`.
- In `t0img.c`, implement the integer array functions declared and specified in the supplied header file `t0img.h`.
- Create a test driver program in file `t0.c` with a main function from which each of the functions in `t0img.c` are called (tested). Compile and execute your `t0img.c` (with stubs) and your test driver.

These functions would work around the following two user defined data structures (see `t0img.h`):

```C
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
    IMG_BADINDEX,
    IMG_BADALLOC,
    IMG_NOTFOUND
} img_result_t;
```

**HINTS**
- Don't forget to keep adding appropriate function calls to your test driver as you go along.
- An example of **stubing** is to replace the body with `return 0` if your function is supposed to return an `int`. This way, your program compiles even if your function body is incomplete.
    - If your code compiles, then implement the two functions of task 1.
    - Compile and execute your test driver. Note that this time, your test driver is testing the functions you have implemented for task 01.1. Are these functions working as expected?.
    - Repeat the above two steps until all functions have been designed, implemented and tested.

**TESTING**: you can test your program by running:
```
$ make p0
$ ./p0
```

The following is a breakdown of the tasks.

### Task 01.1

**REQUIREMENT**: write a function in `t0img.c` with the following declaration:
```C
img_t* img_create(unsigned int rows, unsigned int cols);
```
- INPUT: the numer of `rows` and `cols` of the desired array.
- OUTPUT: `img_create()` returns the POINTER to a new instance of data structure `img_t`.
- BEHAVIOUR: if `malloc()` fails (i.e. returns `NULL`), `img_create()` returns `NULL`.

### Task 01.2

**REQUIREMENT**: write a function in `t0img.c` with the following declaration:
```C
void img_destroy(img_t* im);
```
- INPUT: the pointer of a `img_t` variable `im`.
- BEHAVIOUR: `img_destroy()` should `free()` the memory allocated to `im`.

### Task 02.1

**REQUIREMENT**: write a function in `t0img.c` with the following declaration:
```C
img_result_t img_set(img_t* im, unsigned int row, unsigned int col, int val);
```
- INPUT: the pointer of a `img_t` variable `im`, a `row`, a `col`, and a value.
- OUTPUT:
    - If `im` is `NULL`, return `IMG_BADARRAY`.
    - If the `row` and `col` index is valid (index exists in the `pixels` 2D array of `im`), set the value at `im->data[row][col]` to `val` and return `IMG_OK`. 
    - If the `row` doesn't exist in the 2D array, leave the array unmodified and return `IMG_BADROW`.
    - If the `row` exists but the `col` doesn't exist in the 2D array, leave the array unmodified and return `IMG_BADCOL`.

### Task 02.2

**REQUIREMENT**: write a function in `t0img.c` with the following declaration:
```C
img_result_t img_get(const img_t* im, unsigned int row, unsigned int col, int* val);
```
- INPUT: the pointer of a `img_t` variable `im` (`const` means that you cannot modify `im`), a `row` and `col` index, and the pointer to a value.
- OUTPUT:
    - If the `row` and `col index is valid and `val` is non-`NULL`, set `*val` to `im->data[row][col]` and return `IMG_OK`. 
    - Otherwise do not modify `*val` and return `IMG_BADROW` if `row` doesn't exist, otherwise `IMG_BADCOL` if `col` doesn't exist. 
    - If `im` is `NULL`, return `IMG_BADARRAY`.

### Task 03

**REQUIREMENT**: write a function in `t0img.c` with the following declaration:
```C
img_t* img_copy(const img_t* im);
```
- INPUT: the pointer of a `img_t` variable `im`.
- OUTPUT: 
    - Return a duplicate of `im`, allocating new storage for the duplicate data (we call this a "deep copy"). 
    - If unsuccessful (i.e. memory allocation for the copy fails, or `im` is `NULL`), return a null pointer.

### Task 04

**REQUIREMENT**: write a function in `t0img.c` with the following declaration:
```C
img_result_t img_find(img_t* im, int target, int* i, int* j);
```
- INPUT: the pointer of a `img_t` variable `im`, a `target` value, and a pointer to an integer `i`.
- OUTPUT:
    - If `im` is `NULL`, return `IMG_BADARRAY`.
    - if the `target` value is found in the array in `im` and `i` is non-`NULL`, set `*i` and `*j` to the `row` and `col` index respectively, of where `target` first occured and return `IMG_OK`. The order of search is done left to right, top to bottom i.e. search the entire first row in order, then search the second row.
    - If `target` does not occur in the array, leave `*i` unmodified and return `IMG_NOTFOUND`.

### Task 05

**REQUIREMENT**: write a function in `t0img.c` with the following declaration:
```C
img_t* img_copy_subarray(img_t* im, unsigned int first_row, unsigned int last_row, 
                                    unsigned int first_col, unsigned int last_col);
```
- INPUT: the pointer of a `img_t` variable `im`, index `row_first`, `row_last`, `col_first`, and `col_last`.
- OUTPUT:
    - Return a deep copy of a portion of `im` from index `first_row` and `first_col to index `last_row` and `last_col` inclusive. If successful, return a pointer to a newly-allocated `img_t` containing a copy of the specified section.  For example, if `first_row` = 3, `last_row` = 6, `first_col` = 2, `last_col` = 3, the resulting 2D array would be 4 rows and two cols in size.
    - If an error occurs, i.e. `im` is `NULL`, the row/col indices are out of bounds, 'last' < 'first', or memory allocation fails, return a null pointer.

# Submission

Make sure you have the following files ready for submission and that they are named appropriately, otherwise they won't be graded.
- Task 01-05: `t0img.c`, `t0.c`

Compress these files into a zip file called `a.zip`; you can do this by using the following command from console:
```
$ make submit
```

Upload `a.zip` onto to the appropriate assignment submission page on the [CMPT 127 D100/D200/D300 Canvas page](https://canvas.sfu.ca/courses/62984) > Assignments.

# Marking rubric


| Task | Criteria                                      | Points |
|------|-----------------------------------------------|--------|
| All  | The assigment is submitted in the appropriate format (i.e. the submitted files are named as specified and they are compressed into .zip format and uploaded onto canvas). | 1 |
|`t0.c`| Tests are created for each of the 7 functions x 0.5; each test either works appropriately (0.5) or they don't (0). | 3.5 |
| 01   | `img_create` works as intended.               | 0.5    |
|      | `img_destroy` works as intended.              | 0.5    |
| 02   | `img_set` works as intended.                  | 0.5    |
|      | `img_get` works as intended.                  | 0.5    |
| 03   | `img_copy` works as intended.                 | 1      |
| 04   | `img_find` works as intended.                 | 1      |
| 05   | `img_copy_subarray` works as intended.        | 1      |
| All  | All tests in `t0.c` works and all functions implemented works as intended. | 0.5 |
| Total|                                               | 10     |