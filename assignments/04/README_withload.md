# Assignment 04: file I/O

Due: 2021-07-19 11:59pm.

Download the files for this assignment [here](./files.zip) (or from the [CMPT 127 D100/D200/D300 Canvas page](https://canvas.sfu.ca/courses/62984) > Assignments).

**REMEMBER**:
- Reference [lab 05](../../labs/05) for help!
- DO THE PRACTICE problems! They **directly** help you do the assignment tasks!
- Assignments are to be done individually.
- You may submit/resubmit the assignment as many times as you need before the designated due date (please don't do it too often though).
- The internet is your friend :) Search for documentation online and make sure to understand why things work the way they do!

**CONTENTS**: for this assignment, you will complete the following tasks.
- [Task 01](#task-01)
- [Task 02](#task-02)
- [Task 03](#task-03)

Your assignment will be graded according to this [**marking rubric**](#marking-rubric).

## Task 01

You will extend the functionality of your integer array from the previous assignment, task 01-05 to support saving and loading of 2D arrays from the filesystem in a binary format. 

**REQUIREMENT**:
- you will create a C source file called "t1img.c" containing implementations of the two functions declared in `t1img.h`.
- you will create your own `t1.c` to test your functions.

Your code may call any other functions declared and implemented as part of the previous assignment, task 01-05 by copying these files over to `t1img.c` and `t1img.h` (DO NOT re-implement these).

**HINT**: calls to `fwrite()` are relatively expensive. Try to use as few as you can.

Declarations in `t1img.h`:

```C
int img_save_binary(img_t* im, const char* filename);
```
- INPUT: the pointer of a `img_t` variable `im`, a filename (recall: C strings are arrays of character elements + a terminator `\0` element).
- OUTPUT: returns `0` on success, or a non-`0` error code on failure.
- BEHAVIOUR: saves `im`'s 2D array into a file `filename` in a binary file format that can be loaded by `img_load_binary()`.

```C
img_t* img_load_binary(const char* filename);
```
- INPUT: a filename.
- OUTPUT: returns a pointer to a newly-allocated `img_t` on success, or `NULL` on failure.
- BEHAVIOUR: loads a new array from the file called 'filename', that was previously saved using `img_save_binary()`. Make sure you validate the parameter before you use it.

**TESTING**: you can test your program by running:
```
$ make t1 # OR gcc -Werror -Wfatal-errors -g -o t1 t1.c t1img.c (see Makefile)
$ ./t1
```
(see? Makefiles saves your `gcc` command so you don't have to type this long thing over and over again, convenient huh :D)

## Task 02

In task 01, we exported our array into a binary format. However, binary formats are not human read-able nor are they export-able to other programs that does not understand your finary format.

The most readable, portable XDR format is plain text. A popular syntax for text files is [JSON (JavaScript Object Notation)](http://json.org), which, as the name suggests, was originally an XDR format for web programs make with the programming language, JavaScript. It is easier to use, less verbose than the also-popular [Extensible Markup Language (XML)](http://en.wikipedia.org/wiki/XML), and more expressive than the bare-bones [Comma-Separated Values (CSV)](http://en.wikipedia.org/wiki/Comma-separated_values) formats you may have seen. JSON's popularity can also be attributed to the fact that it is readable for humans and can be imported into another program that does not understand your binary format.

The down side of text formats is that they are:
1. inefficient in space, since e.g. a four-byte integer (`int32_t`) could require up to 11 bytes to represent its minimum value of -2147483648 as a decimal string;
2. inefficent in time, since parsing the text file to convert it back into a binary format is much more expensive than loading a binary file.

The C standard library has two functions that can be very helpful for rendering text into files. They work just like the familiar `printf()` and `scanf()` but read to and write from `FILE*` objects instead of standard input and standard output. You should probably use these to solve this task.
- [`fprintf()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fprintf.html)
- [`fscanf()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fscanf.html)

Notice from those manual pages that functions `snprintf()` and `sscanf()` can also print and scan from C strings. (`sprintf()` exists, but the lack of array length checking means this is not safe or secure to use. Always use `snprintf()`).

You will extend the functionality of your integer array from the previous assignment, task 01-05, to support saving and loading arrays from the filesystem in JSON. You know how to do it for 1D arrays, now can you do it for 2D arrays?

HINT: for 1D arrays you saved each element as `[ ... ]`; for 2D arrays, it is just `[[...] [...] [...]]`

**REQUIREMENT**: 
- you will create a C source file called `t2img.c` containing implementations of the two functions declared in `t2img.h`.
- you will create your own `t2.c` to test your functions.

Your code may call any other functions declared in "t2img.h" and implemented as part of the previous assignment, task 01-05 by copying these files over and changing their names to `t2img.c` and `t2img.h` and importing them, if you haven't already for task 01 (DON'T re-implement these).

You should NOT create a single huge string in memory and write it out in one call to `fwrite()`. The string could require a huge amount of memory when your array is large. Since you chose an inefficient text format, you're not optimizing for speed so don't worry about using many calls to `fwrite()`.

The header file `t2img.h` contains these new function declarations:

```C
int img_save_json(img_t* im, const char* filename);
```
- INPUT: the pointer of a `img_t` variable `im` and a filename.
- OUTPUT: returns `0` on success, or a non-`0` error code on failure.
- BEHAVIOUR: saves the `im` array into a file `filename` in a JSON file format that can be loaded by `img_load_json()`.
    - Arrays of length 0 should produce an output file containing an empty array.
    - Make sure you validate the parameters before you use them.
    - The JSON output should be human-readable.

```C
img_t* img_load_json(const char* filename);
```
- INPUT: a filename.
- OUTPUT: returns a pointer to a newly-allocated `img_t` on success (even if that array has length 0), or `NULL` on failure.
- BEHAVIOUR: loads a new array from the file called 'filename', that was previously saved using `img_save_json()`. 
    - Make sure you validate the parameter before you use it.

**TESTING**: you can test your program by running:
```
$ make t2 # OR gcc -Werror -Wfatal-errors -g -o t2 t2.c t2img.c (see Makefile)
$ ./t2
```
(see? Makefiles saves your `gcc` command so you don't have to type this long thing over and over again, convenient huh :D)

## Task 03

Since our data type `img_t` stores an image, let's save it as an image!

In this task, we will save out pixels as a .ppm file; this is a text file format that can be opened using image viewer applications. 

Currently, we have one value in each cell of our 2D matrix. This means that our image is greyscale. Image formats usually save their images in colour format. This means that in each cell, their 2D matrix would have three values: red, green, blue. 

Fortunately, it is simple to convert between our single value and the regular triple value RGB format. For each cell, we just have to replicate our value three times and ensure that our value is less than or equal to 225.

**REQUIREMENT**: 
- you will finish the function code started for you in file `t3img.c` containing the implementation of a function declared in `t3img.h`.
- you will create your own `t3.c` to test your functions.

The header file `p3img.h` contains this new function declaration:

```C
int img_save_ppm(img_t* im, const char* filename);
```
- INPUT: the pointer of a `img_t` variable `im` and a filename.
- OUTPUT: returns `0` on success, or a non-`0` error code on failure.
- BEHAVIOUR: saves the `im` array into a file `filename` in a .ppm file format.
    - Arrays of length 0 should produce an output file containing an empty array.
    - Make sure you validate the parameters before you use them.
    - The .ppm output should be a text file that can also be viewed as an image in an image viewer.

**TESTING**: you can test your program by running:
```
$ make t3 # OR gcc -Werror -Wfatal-errors -g -o t3 t3.c t3img.c (see Makefile)
$ ./t3
```
(see? Makefiles saves your `gcc` command so you don't have to type this long thing over and over again, convenient huh :D)


# Submission

First, make sure your code is readable, see instructions [here](../../readability.md).

Make sure you have the following files ready for submission and that they are named appropriately, otherwise they won't be graded.
- Task 01: `t1img.c`, `t1.c`
- Task 02: `t2img.c`, `t2.c`
- Task 03: `t3img.c`, `t3.c`

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
| 01   | `t1.c` tests are created for each of the 2 functions x 0.5; each test either works appropriately (0.5) or they don't (0). | 1 |
|      | `img_save_binary` works as intended.          | 1      |
|      | `img_load_binary` works as intended.          | 1      |
| 02   | `t2.c` tests are created for each of the 2 functions x 0.5; each test either works appropriately (0.5) or they don't (0). | 1 |
|      | `img_save_json` works as intended.            | 1.5    |
|      | `img_load_json` works as intended.            | 1      |
| 03   | `t3.c` tests are created for each of the function in `t3img.c`; each test either works appropriately (0.5) or they don't (0). | 0.5 |
|      | `img_save_ppm` works as intended.             | 1.5    |
| Total|                                               | 10     |
