# Assignment 05: memory allocation

Due: 2021-07-26 11:59pm.

Download the files for this assignment [here](./files.zip) (or from the [CMPT 127 D100/D200/D300 Canvas page](https://canvas.sfu.ca/courses/62984) > Assignments).

Read this file for how to create test cases: [test_case_02.c](./test_case_02.c)

**REMEMBER**:
- Reference [lab 06](../../labs/06) for help!
- DO THE PRACTICE problems! They **directly** help you do the assignment tasks!
- Assignments are to be done individually.
- You may submit/resubmit the assignment as many times as you need before the designated due date (please don't do it too often though).
- The internet is your friend :) Search for documentation online and make sure to understand why things work the way they do!

**CONTENTS**: for this assignment, you will complete the following tasks.
- [Task 00](#task-00-03)
- [Task 01.1](#task-011)
- [Task 01.2](#task-012)
- [Task 02](#task-02)
- [Task 03](#task-03)
- [Task 04](#task-04)

Your assignment will be graded according to this [**marking rubric**](#marking-rubric).

## Task 00-04

In this assignment, we will implement **preallocation**.

You may copy over, modify, and use the functions you created in the previous two assignments. You may also create however many new functions to assist you with this assignment.

**REQUIREMENT**: you will write your program to two files: `t0imgr.c`, `t0.c`.
- In `t0imgr.c`, implement the integer array functions declared and specified in the supplied header file `t0imgr.h`.
- Create a test driver program in file `t0.c` with a main function from which each of the functions in `t0imgr.c` are called (tested). Compile and execute your `t0imgr.c` (with stubs) and your test driver.

**IMPORTANT NOTES**:
- You may assign the value `0` to the elements in your array to initialize the elements --- whether you are creating the array or appending to the array. `0` will indicate an "empty" element.
- Recall, in pre-allocation, we allocate more space in memory than what is requested by the user.
    - `rows` and `cols` are the number of rows and columns the user has requested for in their 2D matrix. For example, if `rows` is 10 and `cols` is 10, and the user appends a value such that the number of rows increase by one, then you increase `rows` to 11.
    - `reserved_rows` and `reserved_cols` are the number of rows and columns that are reserved for the user i.e. this is the capacity of your 2D array. For example, currently, the `rows` and `reserved_rows` are 10 and `cols` and `reserved_cols` are 10. If the user appends a value such that the number of rows should increase, then you increase `rows` to 11 and double the size of `reserved_rows` to 20 along with the number of rows allocated in memory for your 2D array. Review preallocation for more details.

These functions would work around the following user defined data structures (see `t0imgr.h`):

```C
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
```

**HINTS**
- Don't forget to keep adding appropriate function calls to your test driver as you go along.
- `reserved_rows` should always represent the amount of memory allocated to all the row arrays in `imgr_t`. This means that if you doubled the length of one row, you need to do the same for all other rows.
- `reserved_cols` should always represent the amount of memory allocated to the main col array. This means that if you double your original array, you also need to double the amount of rows you have in `imgr_t`.

**TESTING**: you can test your program by running:
```
$ make t0 # OR gcc -Werror -Wfatal-errors -g -o t0 t0.c t0imgr.c (see Makefile)
$ ./t0
```
(see? Makefiles saves your `gcc` command so you don't have to type this long thing over and over again, convenient huh :D)

The following is a breakdown of the tasks.

**REMINDER**:
- write comments!! Test and debug your code!
- Prompt the user for what they should enter by printing messages with `printf`, e.g. `"Enter an integer: "`, and let the user know what the output is by printing a message, e.g. `"Here is the result: "`.

### Task 01.1

**REQUIREMENT**: write a function in `t0imgr.c` with the following declaration:
```C
imgr_t* imgr_create(unsigned int rows, unsigned int cols);
```
- INPUT: the number of `rows` and `cols` of the desired array.
- OUTPUT: `imgr_create()` returns the POINTER to a new instance of data structure `imgr_t`.
- BEHAVIOUR: if `malloc()` fails (i.e. returns `NULL`), `imgr_create()` returns `NULL`.
  - The `reserved_rows` and `reserved_cols` should be initialized to be the same as `rows` and `cols` respectively. These fields represent the **capacity** or the available space in your 2D array. In the front end, the user should not have to deal with this. You use them in your functions to perform preallocation.

### Task 01.2

**REQUIREMENT**: write a function in `t0imgr.c` with the following declaration:
```C
void imgr_destroy(imgr_t* im);
```
- INPUT: the pointer of a `imgr_t` variable `im`.
- BEHAVIOUR: `imgr_destroy()` should `free()` the memory allocated to `im`.

### Task 02

Lab 06 practice problem 03 may help you with this task.

**REQUIREMENT**: write a function in `t0img.c` with the following declaration:
```C
imgr_result_t imgr_append(imgr_t* im, int expand_row, int val);
```
- INPUT: the pointer of a `imgr_t` variable `im`, a boolean `expand_row`, and an integer `val`.
- OUTPUT: 
    - Return `IMGR_OK` if successful.
    - Return `IMGR_BADALLOC` if `realloc()` failed.
- BEHAVIOUR: use preallocation!
    - Append `val` to the end of the 2D array `pixels` in `im` to the index with the smallest row index, and then the smallest col index e.g. if both indices `[3][15]` and `[5][1]` are empty, we append the value to `[3][15]`, since it has the smaller `row` index. A very simple search will allow you get this behaviour e.g. search for the smallest row index associated with the row that has an empty element, and then in that row, find the first element that is empty, and that would be your column index.
    - If there is no more room left and if
        - `expand_row != 0`, double the size of the rows.
        - `expand_row = 0`, double the size of the cols.
    - Both of the above cases should be tested in `t0.c`

### Task 03

**REQUIREMENT**: write a function in `t0img.c` with the following declaration:
```C
imgr_result_t imgr_remove(imgr_t* im, unsigned int i, unsigned int j);
```
- INPUT: the pointer of a `imgr_t` variable `im` and index `i`, `j`.
- OUTPUT: 
    - If you were able to remove the element at `[i][j]`, replace it with the last element in row `i` (this is called unstable remove), and remove that last element from the end by setting it to null, return `IMGR_OK`.
    - If removing the element causes an entire last row and/or column to be empty, decrement the field rows and/or cols as necessary.
    - If unsuccessful, return `IMGR_BADROW` if you couldn't find row `i`, otherwise return `IMGR_BADCOL` if you couldn't find row `j`.
    - if you went to index `[i][j]` but there was nothing there, return `IMGR_EMPTY`.

### Task 04

```C
int imgr_save_json(imgr_t* im, const char* filename);
```
- INPUT: the pointer of a `imgr_t` variable `im` and a filename.
- OUTPUT: returns `0` on success, or a non-`0` error code on failure.
- BEHAVIOUR: saves the `im` array into a file `filename` in a JSON file format that can be loaded by `imgr_load_json()`.
    - Arrays with 0 rows and cols should produce an output file containing an empty array e.g. `[]`.
    - Make sure you validate the parameters before you use them.
    - The JSON output should be human-readable.
    - Only write to file, the elements within columns `cols` and rows `rows`, NOT `reserved_rows` and `reserved_cols`.
    - See the header file for an example of an output JSON file for a 2D array (recall, we implemented the same function in a previous assignment, feel free to adapt that here!).

```C
imgr_t* imgr_load_json(const char* filename);
```
- INPUT: a filename.
- OUTPUT: returns a pointer to a newly-allocated `imgr_t` on success (even if that array has rows and cols of 0), or `NULL` on failure.
- BEHAVIOUR: loads a new array from the file called 'filename', that was previously saved using `imgr_save_json()`. 
    - Make sure you validate the parameter before you use it.
    - Since you are newly initializing an `imgr_t`, you may set your `cols` and `rows` to be the same as `reserved_rows` and `reserved_cols` respectively.
    - If you need help, see lab 06 practice problem 03 for how to implement this ;).
- On top of testing the outputs for this function, add an additional test case to ensure that the JSON file is saved properly. To do this, load the JSON file and validate that the values in the fields (including the values inside of the array) of the structure you saved and loaded are the same.

# Submission

First, make sure your code is readable, see instructions [here](../../readability.md).

Make sure you have the following files ready for submission and that they are named appropriately, otherwise they won't be graded.
- Task 00-03: `t0imgr.c`, `t0.c`

Compress these files into a zip file called `a.zip`; you can do this by using the following command from console:
```
$ make submit
```

i.e. you should have ONE file called `a.zip` containing the files listed above (you can open your `a.zip` file to verify you have the correct files in it).

Upload `a.zip` onto to the appropriate assignment submission page on the [CMPT 127 D100/D200/D300 Canvas page](https://canvas.sfu.ca/courses/62984) > Assignments.


# Marking rubric


| Task | Criteria                                      | Points |
|------|-----------------------------------------------|--------|
| All  | The assigment is submitted in the appropriate format (i.e. the submitted files are named as specified and they are compressed into .zip format and uploaded onto canvas). | 1 |
|      | Source code is readable (i.e. student name and program description at the top of program files, variable names are self-descriptive and consistent, comments describing what code does is available where appropriate, indentatations are consistent), see instructions [here](../../readability.md). | 0.5 |
| 00   | `t0.c` tests are created for each of the 4 functions (`imgr_append`, `imgr_remove`, `imgr_save_json`, `imgr_load_json`) x 0.5 (+0.5 because `expand_row` has two test cases, when `expand_row = 0` and `expand_row != 0`); each test either works appropriately (0.5) or they don't (0). | 2.5 |
| 01   | `imgr_create` works as intended.               | 0.5    |
|      | `imgr_destroy` works as intended.              | 0.5    |
| 02   | `imgr_append` works as intended when preallocation does not need to occur. | 1 |
| 02   | `imgr_append` works as intended when `expand_row = 0`. | 1 |
|      | `imgr_append` works as intended when `expand_row !=0`. | 1 |
| 03   | `imgr_remove` works as intended (i.e. the value at the designated index is replaced with the last element of the array in the designated row and the space where the end element used to be is now null). | 1 |
| 04   | `imgr_save_json` works as intended (i.e. output JSON file is in the format specified in the comments of the header file). | 0.5 |
|      | `imgr_load_json` works as intended.           | 0.5    |
| Total|                                               | 10     |
