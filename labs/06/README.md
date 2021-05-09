<div class="lab">

# Lab 6: File I/O

#### `external data representation; fopen(), fclose(), fread()` and `fwrite(), struct` practice

<div id="floatingCornerLeft">[![](../img/balloon0.jpg)](http://books.google.ca/books?id=RFJiAgAACAAJ&dq=%22Computer+lieben+Frauen&hl=en&sa=X&ei=H9SoUuCrBI_YoASa2oCADQ&ved=0CEcQ6AEwAA)</div>

<div id="floatingCornerRight">[![](../img/balloon1.jpg)](http://books.google.ca/books?id=RFJiAgAACAAJ&dq=%22Computer+lieben+Frauen&hl=en&sa=X&ei=H9SoUuCrBI_YoASa2oCADQ&ved=0CEcQ6AEwAA)</div>

### Goals

After this lab you will be able to

1. Explain what XDR is, and how it relates to files.
2. Open files with `fopen()` with correct usage mode, and `fclose()` them.
3. Handle error codes returned from the relevant system calls.
4. Read and write to files with `fread()` and `fwrite()` using simple arrays and structs.

## Setup

<div class="steps">

In the terminal:

1. From your local repo, create and 'git add' the new directory '6', then make '6' your working directory.
2. Fetch the header file [intarr.h](intarr.h). <mark>This is a different `intarr.h` file than the one we fetched in Lab 5.</mark> It contains all the Lab 5 tasks (which you have already done) as well as the Lab 6 tasks (which you are to do in this lab).

</div>

## External Data Representation using Files

A program's working memory of stack and heap data structures (i.e., data structures to which memory from the stack memory segment or the heap memory segment has been allocated) only exists while the program is running. To store data between runs, and to capture output, we can use the _filesystem_. The filesystem is a service provided by the operating system (OS) that provides _files_ to your programs. A file is like a named array of bytes, and once created a file will persist until deleted, even when the computer is turned off.

You are familiar with files: text files like C sourcecode; sound files like MP3s; executable files like your compiled programs. At the filesystem abstraction level, these are all the same thing: just a contiguous sequence of bytes. The interpretation of these bytes is up to your program.

Files are a common special case of the general problem of storing data outside a running program. In general this is called **External Data Representation (XDR)**. Other examples of XDR occur when using databases or networking.

Files are identified by a [_path_](http://en.wikipedia.org/wiki/Path_(computing)), which is a generalization of a [_filename_](http://en.wikipedia.org/wiki/Filename) and can be any of:

- a simple filename, e.g. "hadfield.png". This is often used when we are "manipulating" a file located in the current directory. For example, in Lab 3, we issued the command

```
$ ./test hadfield.png
```

        at the command line. We were able to do so because our executable file `test` as well as our test file `hadfield.png` were both located in our current directory.
- a _relative path_ that specifies a path (location) in the filesystem's directory structure relative to the current working directory, e.g. "students/bsimpson/reportcard.pdf". This is often used when the path to a file can be specified starting from our current directory. For example, the desired file can be located either in a "parent" directory, i.e., a directory "above" the current directory, or in a directory "below" the current directory.
- an _absolute path_ that begins with a '/' (which signifies the "root" directory) and fully specifies a location in the directory structure, e.g. "/home/vader/projects/deathstar.dxf". This is used when the path to a file (location of a file) cannot be specified using the first two ways.

The programmer's interface to the filesystem is quite basic, with most of the work done with four abstract operations:

- OPEN(path, mode): opens a file (described by "path") for reading and/or writing, possibly creating a new file if file (i.e, "path") does not exist. These options are defined by the mode. Returns an identifier that the other functions use to identify an open file. The file has a length in bytes, which is initially zero for a new file, and a _current read/write position_ which is an index into the bytes of the file at which read and write operations will do their work. After OPEN() the initial read/write position is either at the beginning or end of the file depending on the mode.

- WRITE(ID, source, length): writes length bytes from source into the file, starting from the current read/write position and overwriting anything already there. The length of the file will increase automatically if necessary. When the write has finished, the current read/write position is set to one beyond the data written.

- READ(ID, dest, length): reads length bytes from the file into dest. When the read is finished, the current read/write position is set to one beyond the data read.

- CLOSE(ID): closes the file, indicating to the OS that we have finished using it.

A less-used fifth operation, SEEK(), allows you to set the read/write position directly without reading or writing.

Almost every programming language supports a version of this interface. You may recognize it from Python. For the C programmer, this interface is provided by these four _system calls_ defined in `stdio.h`:

```C
FILE * fopen(const char * filename, 
                            const char * mode);

size_t fwrite(const void * ptr, 
                             size_t size, 
                             size_t nitems, 
                             FILE * stream);

size_t fread(void * ptr,
                            size_t size, 
                            size_t nitems, 
                            FILE * stream);

int fclose(FILE *stream);

```

These calls closely match their abstract versions, except that read and write have a convenient extension that makes it easy to work with structs (see example code above). The following links give the specifications of each of these functions according to the [Open Group standard](http://pubs.opengroup.org/onlinepubs/009695399/frontmatter/preface.html):

- [`fopen()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fopen.html)

- [`fwrite()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fwrite.html)

- [`fread()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fread.html)

- [`fclose()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fclose.html)

Documentation is also available as man pages on your local computer. The advantages of the Open Group specifications are that they are sometimes better written, cover only the functionality supported by all standard implementations and often contain examples. The man pages will contain details that are specific to your local OS.

You should get used to reading documentation in these forms.

Unless you have a good reason, stick to the standard interfaces. This will make it easier (i) to port your code to another OS; and (ii) to find another programmer who can understand it. Also, new versions of OS are more likely to implement the standard than to retain their previous quirks.

#### A note on interface design

These functions are a masterpiece of interface design. `fopen()` has the most complex functionality, but a very simple interface. `fwrite()` and `fread()` have the _same_ interface to opposite functionality. Your calls to read and write look exactly the same, which makes it easy to write them correctly.

#### Useful extras

You may find these useful:

- [`fseek()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fseek.html) : repositions the current read/write location.

- [`feof()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/feof.html) : tells you if the end-of-file is reached.

- [`ftell()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/ftell.html) : returns the current read/write location.

- [`ftruncate()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/ftruncate.html) : truncate a file to a specified length.

- [`stat()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/stat.html) : get file status

* * *

## Files by example

Here are some examples of using the file API. Background on files and links to the interface specifications are provided below.

#### Write a simple array to a file

```C
#include <stdio.h>

int main(int argc, char* argv[]) {
    const size_t len = 100;
    int arr[len];

    // put data in the array
    // ...

    // write the array into a file (error checks ommitted)
    FILE* f = fopen("myfile", "w"); 
    fwrite(arr, sizeof(int), len, f);
    fclose(f);

    return 0;
}

```

#### Read a simple array from a file

```C
#include <stdio.h>

int main(int argc, char* argv[]) {
    const size_t len = 100;
    int arr[len];

    // read the array from a file (error checks ommitted)
    FILE* f = fopen("myfile", "r"); 
    fread(arr, sizeof(int), len, f);
    fclose(f);

    // use the array
    // ...

    return 0;
}

```

#### Write an array of structs to a file, then read it back

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef    struct 
{
    int x,y,z;
} point3d_t;

int main(int argc, char* argv[]) {
    const size_t len = atoi(argv[1]);

    // array of points to write out
    point3d_t wpts[len];

    // fill with random points
    for(size_t i=0; i<len; i++)
        {
            wpts[i].x = rand() % 100;
            wpts[i].y = rand() % 100;
            wpts[i].z = rand() % 100;
        }

    // write the struct to a file (error checks ommitted)
    FILE* f1 = fopen(argv[2], "w"); 
    fwrite(wpts, sizeof(point3d_t), len, f1);
    fclose(f1);

    // array of points to read in from the same file
    point3d_t rpts[len];

    // read the array from a file (error checks ommitted)
    FILE* f2 = fopen(argv[2], "r"); 
    fread(rpts, sizeof(point3d_t), len, f2);
    fclose(f2);

 if (memcmp(wpts, rpts, len * sizeof(rpts[0])) != 0)
        puts("Arrays differ");
    else
        puts("Arrays match");

    return 0;
}

```

#### Saving and loading an image structure, with error checking

This example shows the use of a simple file format that uses a short "header" to describe the file contents, so that an object of unknown size can be loaded.

Make sure you understand this example in detail. It combines elements from the examples above into a simple but realistic implementation of a file format.

```C
/* saves an image to the filesytem using the file format:
     [ cols | rows | pixels ]
     where:
         cols is a uint32_t indicating image width
         rows is a uint32_t indicating image height
         pixels is cols * rows of uint8_ts indicating pixel grey levels
*/
int img_save(const img_t* img, const char* filename) {
    // validate the parameters 
    assert(img);
    assert(img->data);
    assert(filename);

    // open the file for writing
    FILE* f = fopen(filename, "w"); 
 if (f == NULL)
        {
            puts("Failed to open image file for writing");
            return 1;
        }

    // write the image dimensions header
    uint32_t hdr[2];
    hdr[0] = img->cols;
    hdr[1] = img->rows;

 if (fwrite(hdr, sizeof(uint32_t), 2, f) != 2)
        {
            puts("Failed to write image header");
            return 2;
        }        

    const size_t len = img->cols * img->rows;

 if (fwrite(img->data, sizeof(uint8_t), len, f) != len)
        {
            puts("Failed to write image pixels");
            return 3;
        }        

    // always close a file
    fclose(f);
    return 0;
}

/* loads an img_t from the filesystem using the same 
     format as img_save().

     Warning: any existing pixel data in img->data is not free()d.
*/
int img_load(img_t* img, const char* filename) {
    // validate the parameters
    assert(img);
    assert(filename);

    // open the file for reading
    FILE* f = fopen(filename, "r"); 
 if (f == NULL)
        {
            puts("Failed to open image file for reading");
            return 1;
        }

    // read the image dimensions header:
    uint32_t hdr[2];

 if (fread(hdr, sizeof(uint32_t), 2, f) != 2)
        {
            puts("Failed to read image header");
            return 2;
        }        

    img->cols = hdr[0];
    img->rows = hdr[1];

    // helpful debug:
    // printf("read header: %u cols %u rows\n", 
    //	    img->cols, img->rows);

    // allocate array for pixels now we know the size
    const size_t len = img->cols * img->rows; 
    img->data = malloc(len * sizeof(uint8_t));
    assert(img->data);

    // read pixel data into the pixel array
 if (fread(img->data, sizeof(uint8_t), len, f) != len) 
         { 
             puts("Failed to read image pixels"); 
             return 3;
         }        

    // always close a file
    fclose(f);
    return 0;
}

```

Usage:

```C
img_t img;
img_load(&img, "before.img");

image_frobinate(img); // manipulate the image somehow

img_save(&img, "after.img");

```

<div class="task">

## Task 1: Serialize an array of integers to a binary-format file

Extend the functionality of your integer array from Lab 5 to support saving and loading arrays from the filesystem in a binary format.

## Instructions

<div class="steps">

Use the header file `intarr.h` you have fetched for this lab. It contains these new function declarations:

</div>

```C
/* LAB 6 TASK 1 */

/*
    Save the entire array ia into a file called 'filename' in a binary
    file format that can be loaded by intarr_load_binary(). Returns
    zero on success, or a non-zero error code on failure. Arrays of
    length 0 should produce an output file containing an empty array.

    Make sure you validate the parameters before you use them.
*/
int intarr_save_binary(intarr_t* ia, const char* filename);

/*
    Load a new array from the file called 'filename', that was
    previously saved using intarr_save_binary(). Returns a pointer to a
    newly-allocated intarr_t on success, or NULL on failure.

    Make sure you validate the parameter before you use it.
*/
intarr_t* intarr_load_binary(const char* filename);

```

### Requirements

<div class="req">

1. Add and commit a single C source file called "t1.c" containing implementations of these two functions.
2. The file must include the "intarr.h" header file.
3. Your code for this task may call any other functions declared in "intarr.h" and implemented as part of Lab 5\. Your code will be linked against the grading robot's reference implementation of all the tasks of Lab 5 for testing, so make sure the file "t1.c" you submit does not contain the implementation of any of the tasks (functions) of Lab 5.
4. To test your code for this Task 1, create your own "testDriver.c" (which you do not have to submit) and use your own implementation of the tasks (functions) of Lab 5, i.e., "intarr.c".
5. _Performance hint: calls to fwrite() are relatively expensive. Try to use as few as you can._

</div>

### Submission

Commit the single file "t1.c" to your repo in the Lab 6 directory.

</div>

<div class="task">

## Task 2: Serialize an array of integers to a JSON text-format file

Extend the functionality of your integer array from Lab 5 to support saving and loading arrays from the filesystem in JSON, a common human- and machine-readable text format.

Sometimes it is useful for humans to be able to read your stored data, or to import your data into another program that does not understand your binary format. The most readable, portable XDR format is plain text. A popular syntax for text files is [JSON (JavaScript Object Notation)](http://json.org), which, as the name suggests, was originally an XDR format for web programs. It is easier to use and less verbose than the also-popular [Extensible Markup Language (XML)](http://en.wikipedia.org/wiki/XML) and more expressive than the bare-bones [Comma-Separated Values (CSV)](http://en.wikipedia.org/wiki/Comma-separated_values) formats you may have seen.

The down side of text formats is that they are:

1. inefficient in space, since e.g. a four-byte integer (int32_t) could require up to 11 bytes to represent its minimum value of -2147483648 as a decimal string;
2. inefficent in time, since parsing the text file to convert it back into a binary format is much more expensive than loading a binary file.

The standard library has two functions that can be very helpful for rendering text into files:

- [`fprintf()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fprintf.html)
- [`fscanf()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fscanf.html)

They work just like the familiar `printf()` and `scanf()` but read to and write from `FILE*` objects instead of standard input and standard output. You should probably use these to solve this task.

Notice from those man pages that another pair of functions `snprintf()` and `sscanf()` is also available to print and scan from C strings too. (`sprintf()` exists, but the lack of array length checking means this is not safe or secure to use. Always use `snprintf()`).

The header file "intarr.h" also contains these new function declarations:

```C
/* LAB 6 TASK 2 */

/*
    Save the entire array ia into a file called 'filename' in a JSON
    text file array file format that can be loaded by
    intarr_load_json(). Returns zero on success, or a non-zero error
    code on failure. Arrays of length 0 should produce an output file
    containing an empty array.

    Make sure you validate the parameters before you use them.

    The JSON output should be human-readable.

    Examples:

    The following line is a valid JSON array:
    [ 100, 200, 300 ]

    The following lines are a valid JSON array:
    [ 
     100, 
     200, 
     300 
    ]
*/
int intarr_save_json(intarr_t* ia, const char* filename);

/*
    Load a new array from the file called 'filename', that was
    previously saved using intarr_save_json(). The file may contain an array
    of length 0\. Returns a pointer to a newly-allocated intarr_t on
    success (even if that array has length 0), or NULL on failure.

    Make sure you validate the parameter before you use it.
*/
intarr_t* intarr_load_json(const char* filename);

```

### Requirements

<div class="req">

1. Add and commit a single C source file called "t2.c" containing implementations of these two functions.
2. The other requirements of Task 1 apply.
3. _Hint: you should NOT create a single huge string in memory and write it out in one call to fwrite(). The string could require a huge amount of memory when your array is large. Since you chose an inefficient text format, you're not optimizing for speed so don't worry about using many calls to fwrite()._


# Credit

Last updated 2021-05 by Alice Yue. 

Course material designed, developed, and initially taught by [Prof. Richard Vaughan](https://rtv.github.io/); this material has since been taught and adapted by Anne Lavergn, Victor Cheung, and others.
