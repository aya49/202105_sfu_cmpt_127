# Lab 05: file I/O (input/output)

Download lab files [here](./files.zip).

Review "Guide"s and accompanying slides (we will go over these during the lab lecture).
- [Guide 01](#guide) ([slides]()): external data representation (XDR) using files in C

Try "Practice" problems; these will NOT be graded. Note that the solutions given for Practices is just one of many possible solutions, better ones may exist.
- [Practice 01](#practice-01)
- [Practice 02](#practice-02)


## Guide

Today we're going to talk about external data representation with `fopen()`, `fclose()`, `fread()` and `fwrite()`, plus we'll do some more `struct` practice!

Recall: we talked about stream redirection, where we redirected text on the standard output from and to files using `<` and `>` respectively. While the standard output is technically a file, today, we leave the standard output and learn how to read/write to other files on our operating system.


### External data representation (XDR) using files

**Memory**: data structures stored on a programs' working memory of stack and heap are temporary; they only exists while the program is running. To store data between runs, we use the **filesystem**. The filesystem is a service provided by the operating system (OS) that provides **files** to your programs. A file is like a named array of bytes which, once created, will exist until deleted, even when the computer is turned off.

**External Data Representation (XDR)**: XDR is the general problem of storing data outside a running program.

**Files** are a common special case of XDR. Other examples of XDR occur when using databases or networking. You are familiar with files: text files like C source code; sound files like MP3s; executable files like your compiled programs. 
- At the **filesystem abstraction** level, these files are all the same thing: just a contiguous sequence of bytes. 
- The **interpretation** of these bytes is up to your program.

Files are identified by a [**path**](http://en.wikipedia.org/wiki/Path_(computing)), which is a generalization of a [**filename**](http://en.wikipedia.org/wiki/Filename) and can be any of:
- a **filename**, e.g. `p1.c`. This is often used when we are manipulating a file located in the **current directory**, e.g. compiling `$ gcc p1.c -o p1.o`, executing `$ ./p1.o`.
- a **relative path** that specifies the path (location) to a file starting from or **relative to the current working directory**, e.g. `./students/bsimpson/reportcard.pdf`. This is commonly used when, for example, the desired file is in a "parent" directory, e.g., `../reportcard.pdf`, or in a "child" directory, e.g. `./students/bsimpson/reportcard.pdf`.
- an **absolute path** begins with a '/' (the "root" directory) and fully specifies a location in the directory structure, e.g. `/home/vader/projects/deathstar.dxf`. This is used when the path to a file (location of a file) cannot be specified using the first two ways.

The programmer's interface to the filesystem is quite basic. We can do most of our work on files with four abstract operations:
- OPEN(path, mode): opens a file in "path" in one of the "mode" reading and/or writing. If the file doesn't exist, we could possibly use OPEN to create a new file in the path.
    - File size: the file has a length in bytes, which is initially zero for a new file
    - Current read/write position: an index into the bytes of the file at which read and write operations will do their work. After OPEN() the initial read/write position is either at the beginning or end of the file depending on the mode and program specifications.
- WRITE(ID, source, length): writes length bytes from source into the file, starting from the current read/write position and overwrites anything already there. The length of the file will increase automatically if necessary. When the write has finished, the current read/write position is set to one byte beyond the data written.
- READ(ID, dest, length): reads length bytes from the file into dest-ination. When the read is finished, the current read/write position is set to one beyond the data read.
- CLOSE(ID): closes the file, indicating to the OS that we have finished using it.
- SEEK(): a less-used fifth operation, that allows you to set the read/write position directly without reading or writing.

Almost every programming language supports a version of this interface. You may recognize it from Python.

This process can also be called: serialization (converting from program memory) to a binary-format file

#### XDR in C

In C, this interface is provided by these four **system calls** defined in `stdio.h`. The following links give the specifications of each of these functions according to the [Open Group standard](http://pubs.opengroup.org/onlinepubs/009695399/frontmatter/preface.html):

- [`fopen()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fopen.html): this most complex functionality, but a very simple interface.
```C
FILE * fopen(const char * filename,  const char * mode);
```
- [`fwrite()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fwrite.html)
```C
size_t fwrite(const void * ptr, size_t size, size_t nitems, FILE * stream);
```
- [`fread()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fread.html)
```C
size_t fread(void * ptr, size_t size, size_t nitems, FILE * stream);
```
- [`fclose()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fclose.html)
```C
int fclose(FILE *stream);
```
```C
// int fseek(FILE *stream, long int offset, int whence);
```

Note: `fread` and `fwrite` have the same interface to opposite functionality; they also have a convenient extension that makes it easy to work with structs.

Below are some examples of using the file API.

#### XDR in C: write a simple array to a file

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

#### XDR in C: read a simple array from a file

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

#### XDR in C: write an array of structs to a file + read it back

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x,y,z;
} point3d_t;

int main(int argc, char* argv[]) {
    const size_t len = atoi(argv[1]);

    // array of points to write out
    point3d_t wpts[len];

    // fill with random points
    for (size_t i=0; i<len; i++) {
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

    if (memcmp(wpts, rpts, len * sizeof(rpts[0])) != 0) {
        puts("Arrays differ");
    } else {
        puts("Arrays match");
    }
    
    return 0;
}

```

#### XDR in C: saving and loading an image structure, with error checking

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
    if (f == NULL) {
        puts("Failed to open image file for writing");
        return 1;
    }

    // write the image dimensions header
    uint32_t hdr[2];
    hdr[0] = img->cols;
    hdr[1] = img->rows;

    if (fwrite(hdr, sizeof(uint32_t), 2, f) != 2) {
        puts("Failed to write image header");
        return 2;
    }

    const size_t len = img->cols * img->rows;

    if (fwrite(img->data, sizeof(uint8_t), len, f) != len) {
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
    if (f == NULL) {
        puts("Failed to open image file for reading");
        return 1;
    }

    // read the image dimensions header:
    uint32_t hdr[2];

    if (fread(hdr, sizeof(uint32_t), 2, f) != 2) {
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
    if (fread(img->data, sizeof(uint8_t), len, f) != len) { 
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


## Practice 01

you will extend the functionality of your integer array from the previous lab, practice 01-05 to support saving and loading arrays from the filesystem in a binary format.

**REQUIREMENT**:
- you will create a C source file called "p1intarr.c" containing implementations of the two functions declared in `p1intarr.h`.
- you will also create your own `p1.c` to test your functions.

Your code may call any other functions declared and implemented as part of the previous lab, practice 01-05 by copying these files over to `p1intarr.c` and `p1intarr.h` (DO NOT re-implement these).

**HINT**: calls to `fwrite()` are relatively expensive. Try to use as few as you can.

Declarations in `p1intarr.h`:

```C
int intarr_save_binary(intarr_t* ia, const char* filename);
```
- INPUT: the pointer of a `intarr_t` variable `ia`, a filename (recall: C strings are arrays of character elements + a terminator `\0` element).
- OUTPUT: returns `0` on success, or a non-`0` error code on failure.
- BEHAVIOUR: saves the `ia` array into a file `filename` in a binary file format that can be loaded by `intarr_load_binary()`.

```C
intarr_t* intarr_load_binary(const char* filename);
```
- INPUT: a filename.
- OUTPUT: returns a pointer to a newly-allocated `intarr_t` on success, or `NULL` on failure.
- BEHAVIOUR: loads a new array from the file called 'filename', that was previously saved using `intarr_save_binary()`. Make sure you validate the parameter before you use it.

**TESTING**: you can test your program by running:
```
$ make p1
$ ./p1
```

Try it yourself first; then verify your solutions [here](./files/solution/p1intarr.c).

## Practice 02

In practice 01, we exported our array into a binary format. However, binary formats are not human read-able nor are they export-able to other programs that does not understand your finary format.

The most readable, portable XDR format is plain text. A popular syntax for text files is [JSON (JavaScript Object Notation)](http://json.org), which, as the name suggests, was originally an XDR format for web programs make with the programming language, JavaScript. It is easier to use, less verbose than the also-popular [Extensible Markup Language (XML)](http://en.wikipedia.org/wiki/XML), and more expressive than the bare-bones [Comma-Separated Values (CSV)](http://en.wikipedia.org/wiki/Comma-separated_values) formats you may have seen. JSON's popularity can also be attributed to the fact that it is readable for humans and can be imported into another program that does not understand your binary format.

The down side of text formats is that they are:
1. inefficient in space, since e.g. a four-byte integer (`int32_t`) could require up to 11 bytes to represent its minimum value of -2147483648 as a decimal string;
2. inefficent in time, since parsing the text file to convert it back into a binary format is much more expensive than loading a binary file.

The C standard library has two functions that can be very helpful for rendering text into files. They work just like the familiar `printf()` and `scanf()` but read to and write from `FILE*` objects instead of standard input and standard output. You should probably use these to solve this practice problem.
- [`fprintf()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fprintf.html)
- [`fscanf()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fscanf.html)

Notice from those manual pages that functions `snprintf()` and `sscanf()` can also print and scan from C strings. (`sprintf()` exists, but the lack of array length checking means this is not safe or secure to use. Always use `snprintf()`).

You will extend the functionality of your integer array from the previous lab, practice 01-05, to support saving and loading arrays from the filesystem in JSON.

**REQUIREMENT**:  
- you will create a C source file called `p2intarr.c` containing implementations of the two functions declared in `p2intarr.h`.
- you will create your own `p2.c` to test your functions.

Your code may call any other functions declared in "p2intarr.h" and implemented as part of the previous lab, practice 01-05 by copying these files over and changing their names to `p2intarr.c` and `p2intarr.h` and importing them, if you haven't already for practice 01 (DON'T re-implement these).

You should NOT create a single huge string in memory and write it out in one call to `fwrite()`. The string could require a huge amount of memory when your array is large. Since you chose an inefficient text format, you're not optimizing for speed so don't worry about using many calls to `fwrite()`.

The header file `p2intarr.h` contains these new function declarations:

```C
int intarr_save_json(intarr_t* ia, const char* filename);
```
- INPUT: the pointer of a `intarr_t` variable `ia` and a filename.
- OUTPUT: returns `0` on success, or a non-`0` error code on failure.
- BEHAVIOUR: saves the `ia` array into a file `filename` in a JSON file format that can be loaded by `intarr_load_json()`.
    - Arrays of length 0 should produce an output file containing an empty array.
    - Make sure you validate the parameters before you use them.
    - The JSON output should be human-readable.

```C
intarr_t* intarr_load_json(const char* filename);
```
- INPUT: a filename.
- OUTPUT: returns a pointer to a newly-allocated `intarr_t` on success (even if that array has length 0), or `NULL` on failure.
- BEHAVIOUR: loads a new array from the file called 'filename', that was previously saved using `intarr_save_json()`. 
    - Make sure you validate the parameter before you use it.

**TESTING**: you can test your program by running:
```
$ make p2
$ ./p2
```

Try it yourself first; then verify your solutions [here](./files/solution/p2intarr.c).

# Bonus material

You may find these useful:
- [`fseek()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fseek.html) : repositions the current read/write location.
- [`feof()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/feof.html) : tells you if the end-of-file is reached.
- [`ftell()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/ftell.html) : returns the current read/write location.
- [`ftruncate()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/ftruncate.html) : truncate a file to a specified length.
- [`stat()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/stat.html) : get file status


# Credit

Last updated 2021-05 by Alice Yue. 

Course material designed, developed, and initially taught by [Prof. Richard Vaughan](https://rtv.github.io/); this material has since been taught and adapted by Anne Lavergn, Victor Cheung, and others.

(This lab was previously lab 06)
