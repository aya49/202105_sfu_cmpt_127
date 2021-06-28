# Lab 04: structures, composite data types

Download lab files [here](./files.zip).

Review [value vs pointer in memory](https://docs.google.com/presentation/d/1YXf_4yQZ0Oitj0SCFYaMHdNA1utjGWvsfJY54k0sZPM/edit?usp=sharing).

Review "Guide"s and accompanying slides (we will go over these during the lab lecture).
- [Guide 01](#guide) ([slides](https://docs.google.com/presentation/d/1LWARzaCfCVkOSEEjEIEdZeLQ_alEE5w0hUSKfTr7qu4/edit?usp=sharing)): composite data type `struct`, how to use it with `typedef` and `malloc()`, and deep copy-ing `struct`s.

Try "Practice" problems; these will NOT be graded. Note that the solutions given for Practices is just one of many possible solutions, better ones may exist.
- [Practice 01-05](#practice-01-05)

## Guide

### `struct`: a variable that is a group of other variables

It is often useful to collect multiple data items together into a single logical entity: a **composite data type**. C provides the `struct` keyword for this purpose; see syntax for creating one:

```C
struct {
    /*variable declarations*/;
} /*struct_name*/;
```

Before we start, let's talk about black and white raster images. In a computer, this image is simply a matrix where each of its cell ("pixel") contains an integer from 0-255, 0 means black, 255 means white. We use an array whose elements are arrays to other arrays. Each element in our main array represent the rows, the arrays they point to represent the values in each row

![black and white raster image as an array](./img/imagecoord.png)

Overall, an image can be described by a width, a height, and an array (whose elements are also arrays containing pixel values i.e. a 2D array). All three items are required to interpret the encoded image. Let's put these together to make a composite data for an image:

```C
struct { 
    uint8_t* pixels;
    unsigned int cols;
    unsigned int rows;
} img;
```

IMPORTANT: in this lab, we are going to implement  `pixels` as a 1D array, you will implement it as a 2D array in your assignment.

This declaration creates a new variable called `img`, that contains the variables we need for one image. These variables the `image` holdes is called **fields** or **members** of the structure. Each field can be accessed using the "dot" syntax.

So we can initialize our image like so:

```C
img.cols = 640;
img.rows = 480;
img.pixels = malloc(img.rows * img.cols * sizeof(uint8_t*));
```

The structure is implemented as a chunk of memory with space for all its fields. The "dot" syntax is interpreted at compile time as a number of bytes offset from the structure's base address, so these things are true:

```C
// 8-byte pointer (assuming a 64bit OS) + 2 * 4-byte unsigned integers
sizeof(img) == sizeof(uint8_t*) + sizeof(unsigned int) + sizeof(unsigned int)
&img.pixels == (void*)&img + 0 // `(void*)` signifies "pointer of unspecified type"
&img.cols == (void*)&img + sizeof(uint8_t*)
&img.rows == (void*)&img + sizeof(uint8_t*) + sizeof(unsigned int)
```

Let this sink for a minute... better yet, draw out the memory!

This means that C structures have almost no overhead on CPU or memory use at run-time.... BUT sometimes, the compiler may add some empty space called **padding** between fields so that each field starts at the CPU's favoured memory alignment boundary. Most modern CPUs are fastest when accessing memory at 4- or 8-byte boundaries. Inserting padding wastes a little bit of memory. Unless memory is very tight we usually ignore these details (our example structure contains 16 bytes, so it contains no padding.)

Let that sink again, draw out the memory!

More information on memory alignment, including padding [can be found here](http://en.wikipedia.org/wiki/Data_structure_alignment). See [this article](http://www.catb.org/esr/structure-packing/) to understand padding and strategies for avoiding it.

### `typedef`, a user defined data type for structures

The `struct` keyword creates just one instance of a variable. Since we may want to create lots of images, or pass pointers to them into functions, we can create a new type based on our structure definition using the `typedef` keyword.

A type is like the primitive version of the template class you are learning about in CMPT 125, noticed the similarities and differences?

```C
typedef struct { 
    uint8_t* pixels;
    unsigned int cols;
    unsigned int rows;
} img_t;
```

With the `typedef` prefix, instead of declaring a variable, we have declared a new **type** called `img_t` --- it is conventional to use `_t` as a suffix on defined types. Having defined a type, we can create instances of it on the stack as shown below, creating two variables of type `img_t`, and a pointer-to-`img_t`. As the example shows, once `typedef`'d we can use our new type just like we use `int`, `char`, etc.

```C
img_t img1;
img_t img2;
img_t* imgptr = &img1; // imgptr is a pointer that points to the values of img1
```

### `malloc()` for structs

`malloc()` and `sizeof()` works the same for structures as they do for other data types.

This means that the bug we mentioned in lab 03 can also happen to structures:

```C
    // inside some function ...
    img_t img;
    return &img; // OOPS!
}
```

The solutions to the bug also apply:

```C
    // inside some function ...
    img_t* imgptr = malloc(sizeof(img_t));
    if (imgptr == NULL) {
        printf("Warning: failed to allocate memory for an image structure\n"); 
    }

    return imgptr; // safe to return a pointer provided by malloc()
}
```

### Pointer indirection for structs

There is one more bit of syntax to learn: how to access the fields of a structure through a pointer. Given a pointer `imgptr`, we have two exactly equivalent choices:

1. `*`: we can "look inside" and get the value at where the pointer is point to using the normal '*' syntax (also known as 'dereferencing' a pointer), followed by the dot syntax to access the field (note: the breackets are necessary, since the `.` operator has precedence over the `*` operator --- meaning C evaluates `.`s before `*`s, kind of like in math where multiplication is evaluated before additions):

```C
Unsigned int width = (*imgptr).cols;
```

2. `->`: we can use the **indirection arrow** syntax to "look through" the pointer (arguably neater and is preferred):

```C
Unsigned int width = imgptr->cols;
```



### User-defined types as function arguments

Like arrays, a structure is passed to functions via it's pointer:

```C
void draw_image(img_t* img) { ... }

    // call the function above
    draw_image(&img1);
```

We could also pass a structure itself as an argument but this is a BAD IDEA:

```C
void draw_image(img_t img) {...}

// call the function above - BAD!!!
draw_image(img1);
```

Since arguments are passed by value in C, the C function `draw_image` would then receive a copy of the actual value of the argument `img1`. If this structure is large, it will take time and memory space to copy it.

### Shallow-copying structs

When a structure variable is assigned, as on `img_t duplicate = original;`, `original` is copied byte-for-byte into `duplicate`. 

```C
img_t original;
original.cols = 32;
original.rows = 32;
unsigned int numbytes = original.cols * original.rows * sizeof(uint8_t)
original.pixels = malloc(numbytes);

img_t duplicate = original;

assert(duplicate.rows == original.rows); // two copies of the int value
assert(duplicate.cols == original.cols); // two copies of the int value
assert(duplicate.pixels == original.pixels); // two copies of the pointer pointing to the same values
```

This is called **shallow-copying** because for the pointer fields (e.g. `duplicate.pixels` and `original.pixels`), the original values the pointer points to is NOT copied. This means that if you modify the values of `duplicate.pixels`, you would have also modified the values associated with `original.pixels`, because they point to the same array!

![](./img/shallow.png)

BEWARE OF BUGS: **pointer aliasing** is when you have more than one copy of a pointer. This is a notorious source of bugs; if you `free(original.pixels)` any subsequent use of the `duplicate.pixels` pointer is a bug. If possible, avoid having more than one copy of a pointer.


### Deep copying structs

In order to duplicate the whole image including pixel data, not just the pointer to it, we need to 
- `malloc()` more space on the heap
- and use `memcpy()` to copy the original pixel data into it and assign to our new `duplicate.pixels`, a pointer that points to our new copy of the pixel values.

This is called **Deep copy**.

```C
img_t original;
original.cols = 32;
original.rows = 32;
unsigned int numbytes = original.cols * original.rows * sizeof(uint8_t)
original.pixels = malloc(numbytes); // malloc some space on heap

img_t duplicate = original; // start with a shallow copy

// allocate a new pixel array to perform a deep copy
duplicate.pixels = malloc(numbytes);

// and copy numbytes from the original array to the new array
// memory copy (see man memcpy for usage)
memcpy(duplicate.pixels, original.pixels, numbytes);
```

After this code runs, `original` and `duplicate` have the same values in their `cols` and `rows` fields, but different pointer values, i.e., different memory addresses, in their `pixels` field, as illustrated:

![](./img/deep.png)

### Arrays of structs

Arrays of typedef'd structs work in the same way as any other type:

```C
// small array on the stack
img_t imgarr[100];
imgarr[43].cols = 640;
unsigned int width = imgarr[43].cols;

// large array on the heap
img_t* thousand_images = malloc(1000 * sizeof(img_t));
```

### When to use `typedef struct`

Deciding when to create a new structured type is an important part of program design. Your type choices can have effects throughout your code. Some rules of thumb of when you should:
- use a `struct` 
    - when a set of variables must always appear together, and/or 
    - when a set of variables are jointly responsible for something, e.g. interpreting an encoding in our image.
- use `typedef`
    - when you need to declare more than one instance of a structure, and 
    - when using a structure for function arguments, since the resulting code is easier to read.
- use template classes whenever you can get access to C++ ( \*u\*)b


## Practice 00-05

Note: structures can be defined in header files.

**REQUIREMENT**: you will write your program to two files: `p0intarr.c` `p0.c`.
- n `p0intarr.c`, implement the integer array functions declared and specified in the supplied header file `p0intarr.h`.
- Create a test driver program in file `p0.c` with a main function from which each of the functions in `p0intarr.c` are called (tested). Compile and execute your `p0intarr.c` (with stubs) and your test driver.

These functions would work around the following two user defined data structures (see `p0intarr.h`):

```C
/* Structure type that encapsulates our safe int array. */
typedef struct {
  int* data;
  unsigned int len;
} intarr_t;

/* A type for returning status codes */
typedef enum {
  INTARR_OK,
  INTARR_BADARRAY,
  INTARR_BADINDEX,
  INTARR_BADALLOC,
  INTARR_NOTFOUND
} intarr_result_t;
```

**HINTS**
- Don't forget to keep adding appropriate function calls to your test driver as you go along.
- An example of **stubing** is to replace the body with `return 0` if your function is supposed to return an `int`. This way, your program compiles even if your function body is incomplete.
    - If your code compiles, then implement the two functions of practice 01.1.
    - Compile and execute your test driver. Note that this time, your test driver is testing the functions you have implemented for practice 01.1. Are these functions working as expected?.
    - Repeat the above two steps until all functions have been designed, implemented and tested.

**TESTING**: you can test your program by running:
```
$ make p0
$ ./p0
```

The following is a breakdown of the practice problems.

Try it yourself first; then verify your solutions [here](./files/solution/p0intarr.c).

### Practice 01.1

**REQUIREMENT**: write a function in `p0intarr.c` with the following declaration:
```C
intarr_t* intarr_create(unsigned int len);
```
- INPUT: the `len` of the desired array.
- OUTPUT: `intarr_create()` returns the POINTER to a new instance of data structure `intarr_t`.
- BEHAVIOUR: if `malloc()` fails (i.e. returns `NULL`), `intarr_create()` returns `NULL`.

### Practice 01.2

**REQUIREMENT**: write a function in `p0intarr.c` with the following declaration:
```C
void intarr_destroy(intarr_t* ia);
```
- INPUT: the pointer of a `intarr_t` variable `ia`.
- BEHAVIOUR: `intarr_destroy()` should `free()` the memory allocated to `ia`.

### Practice 02.1

**REQUIREMENT**: write a function in `p0intarr.c` with the following declaration:
```C
intarr_result_t intarr_set(intarr_t* ia, unsigned int index, int val);
```
- INPUT: the pointer of a `intarr_t` variable `ia`, an index, and a value.
- OUTPUT:
    - If `ia` is `NULL`, return `INTARR_BADARRAY`.
    - If the `index` is valid (exists in the data array of `ia`), set the value at `ia->data[index]` to `val` and return `INTARR_OK`. 
    - Otherwise, leave the array unmodified and return `INTARR_BADINDEX`.

### Practice 02.2

**REQUIREMENT**: write a function in `p0intarr.c` with the following declaration:
```C
intarr_result_t intarr_get(const intarr_t* ia, unsigned int index, int* val);
```
- INPUT: the pointer of a `intarr_t` variable `ia` (`const` means that you cannot modify `ia`), an index, and the pointer to a value.
- OUTPUT:
    - If `index` is valid and `val` is non-`NULL`, set `*val` to `ia->data[index]` and return `INTARR_OK`. 
    - Otherwise do not modify `*val` and return `INTARR_BADINDEX`. 
    - If `ia` is `NULL`, return `INTARR_BADARRAY`.

### Practice 03

**REQUIREMENT**: write a function in `p0intarr.c` with the following declaration:
```C
intarr_t* intarr_copy(const intarr_t* ia);
```
- INPUT: the pointer of a `intarr_t` variable `ia`.
- OUTPUT: 
    - Return a duplicate of `ia`, allocating new storage for the duplicate data (we call this a "deep copy"). 
    - If unsuccessful (i.e. memory allocation for the copy fails, or `ia` is `NULL`), return a null pointer.

### Practice 04

**REQUIREMENT**: write a function in `p0intarr.c` with the following declaration:
```C
intarr_result_t intarr_find(intarr_t* ia, int target, int* i);
```
- INPUT: the pointer of a `intarr_t` variable `ia`, a `target` value, and a pointer to an integer `i`.
- OUTPUT:
    - If `ia` is `NULL`, return `INTARR_BADARRAY`.
    - if the `target` value is found in the array in `ia` and `i` is non-`NULL`, set `*i` to the index where `target` first occured and return `INTARR_OK`.
    - If `target` does not occur in the array, leave `*i` unmodified and return `INTARR_NOTFOUND`.

### Practice 05

**REQUIREMENT**: write a function in `p0intarr.c` with the following declaration:
```C
intarr_t* intarr_copy_subarray(intarr_t* ia, unsigned int first, unsigned int last);
```
- INPUT: the pointer of a `intarr_t` variable `ia`, an index `first`, and an index `last`.
- OUTPUT:
    - Return a deep copy of a portion of ia from index 'first' to index 'last' inclusive. If successful, return a pointer to a newly-allocated `intarr_t` containing a copy of the specified section. 
    - If an error occurs, i.e. ia is `NULL`, 'first' or 'last' are out of bounds, 'last' < 'first', or memory allocation fails, return a null pointer.

# Bonus material: C vs C++

Recall that C is a subset of C++; all C functions/keywords/code will work with a C++ compiler. In this section, we go over some functions/keywords that are analagous to each other in C and C++.

Let's compare and contrast structures in C, classes in C++, and template classes in C++.

C `typedef struct`: structures are a collection of type-defined variables.
```C
    Function/keyword    typedef struct
          Definition    typedef struct {...} /*type_name*/;
     Fields in {...}    // public by default
                        type var;
 Instantiation/Usage    type_name example_var;
```

C++ `class`: classes are a collection of type-defined variables and **class specific functions**.
```C++
    Function/keyword    class
          Definition    class /*class_name*/ {...};
     Fields in {...}    // private by default
                        type var;
                        type /*function_name*/(type arg);
                        public:
                            type var;
                            type /*function_name*/(type arg);
 Fields out of {...}    type class_name::function_name(type arg) {...}
 Instantiation/Usage    class_name example_class;
```

C++ `template class`: template classes are a collections of **non-type-defined** variables and class specific functions.
```C++
    Function/keyword    template <class /*type_name*/>
          Definition    template <class /*type_name*/> class /*class_name*/ {...};
     Fields in {...}    // private by default
                        type_name var;
                        type_name /*function_name*/(type_name arg);
                        public:
                            type_name var;
                            type_name /*function_name*/(type_name arg);
 Fields out of {...}    template <class type_name> type_name class_name<type_name>::function_name(type_name arg) {...}
 Instantiation/Usage    class_name <type> example_class;
```

Comments: template classes are the most flexible; always use classes and template classes in C++.

# Credit

Last updated 2021-05 by Alice Yue. 

Course material designed, developed, and initially taught by [Prof. Richard Vaughan](https://rtv.github.io/); this material has since been taught and adapted by Anne Lavergn, Victor Cheung, and others.

(This lab was previously lab 05)
