<div class="lab">

# Lab 8: Memory allocation performance

#### Speed testing; `struct` practice; high-performance malloc() strategy

<div id="floatingCornerLeft">[![](../img/balloon0.jpg)](http://books.google.ca/books?id=RFJiAgAACAAJ&dq=%22Computer+lieben+Frauen&hl=en&sa=X&ei=H9SoUuCrBI_YoASa2oCADQ&ved=0CEcQ6AEwAA)</div>

<div id="floatingCornerRight">[![](../img/balloon1.jpg)](http://books.google.ca/books?id=RFJiAgAACAAJ&dq=%22Computer+lieben+Frauen&hl=en&sa=X&ei=H9SoUuCrBI_YoASa2oCADQ&ved=0CEcQ6AEwAA)</div>

### Goals

After this lab you will be able to

1. Use an explicit memory allocation strategy for high performance.
2. Measure runtime performance with `gettimeofday()`.

### Setup

<div class="steps">

In the terminal:

1. Move into your local repo (making it your "working directory").
2. Download the [new material](8.zip) for Lab 8.
3. Expand it into your working directory. This will create the directory '8' containing the files you need.
4. Add the new directory to your Git repo with

    ```
$ git add 8
```

</div>

<div class="task">

## Task 1: Resizing arrays with `realloc()`

The supplied header file `point_array.h` defines the following structures to represent points in 3D space, and an array to contain them, similar to examples you have seen before:

```C
typedef struct point
{
  double x, y, z;    // location in 3D space
} point_t;

typedef struct 
{
  size_t len;        // number of points in the array
  point_t* points;   // an array of 'len' point_t structs
} point_array_t;

```

It also declares four functions for manipulating `point_array_t` arrays. Each takes a pointer to an array structure as their first argument. Notice the `init` and `reset` functions: these do a similar job to the `create` and `destroy` functions we have seen before, but with a slightly different interface. This style allows us to use structs allocated on the stack, which can be useful. <mark>Therefore, `init` must not call `malloc(...)` nor must it call `realloc(...)` since the memory for the struct has already been allocated (automatically, on the stack) and the memory allocation call to obtain the memory for the array is done in `append(...)`</mark>.

```C
// Safely initalize an empty array structure.
void point_array_init(point_array_t* pa);

// Resets the array to be empty, freeing any 
// memory allocated if necessary.
void point_array_reset(point_array_t* pa);

// Append a point to the end of an array. 
// If successful, return 0, else return 1.
int point_array_append(point_array_t* pa, point_t* p);

// Remove the point at index i from the array, 
// reducing the number of elements stored in the array 
// by one. The order of points in the array may change.
// If successful, return 0, else return 1\. 
int point_array_remove(point_array_t* pa, unsigned int i);


```

Example of use:

```C
point_array_t A;
point_array_init(&A);

point_t p;
p.x = 0.0;
p.y = 1.0;
p.z = 2.0;

point_array_append(&A, &p);

// do some work with the array
// ...

// clean up
point_array_reset(&A);


```

In graphics-heavy programs like games, we often have arrays of 3D points that are very large, perhaps with hundreds of thousands or millions of points. For decent performance we need to be able to add points to the array very quickly. Notice that the array interface does not have a resize function: just an append for adding one point at a time. If we use the array resize method we have seen before - copying the old array into a new array that is one slot bigger - this will be very slow.

The only memory allocation standard library call we have seen so far is [`malloc()`](http://pubs.opengroup.org/onlinepubs/009695399/functions/malloc.html), which takes a single argument specifying how much memory it should allocate. Now we introduce the [`realloc()`](http://pubs.opengroup.org/onlinepubs/009695399/functions/realloc.html) standard library call, which allows us to resize our chunk of already allocated memory. Note that we have already been "unofficially" introduced to `realloc()` as it was one of the hints we were given for our Lab 5, where we were told that `realloc()` was a good choice of memory allocation function to use in the implementation of the `intarr_resize(...)` function. In Lab 8, we get to learn why!

We pass `realloc()` the pointer we obtained from an earlier `malloc()` or `realloc()` and a _new_ size, and it will _reallocate_ a chunk of memory of the new size. If the memory allocation system can find enough space at the existing address, `realloc()` returns the original pointer. If the memory allocation system could only find enough space starting at another address, it will:

1. allocate the new chunk
2. copy the content of the old chunk into the new chunk
3. free the old chunk
4. return a pointer to the new chunk

The description from the POSIX standard says:

> `void *realloc(void *ptr, size_t size);`
> 
> The realloc() function shall change the size of the memory object pointed to by `ptr` to the size specified by `size`. The contents of the object shall remain unchanged up to the lesser of the new and old sizes. If the new size of the memory object would require movement of the object, the space for the previous instantiation of the object is freed. If the new size is larger, the contents of the newly allocated portion of the object are unspecified. If `size` is 0 and `ptr` is not a null pointer, the object pointed to is freed. If the space cannot be allocated, the object shall remain unchanged.
> 
> If `ptr` is a null pointer, `realloc()` shall be equivalent to `malloc()` for the specified size.
> 
> Upon successful completion with a size not equal to 0, `realloc()` shall return a pointer to the (possibly moved) allocated space. If `size` is 0, either a null pointer or a unique pointer that can be successfully passed to free() shall be returned. If there is not enough available memory, `realloc()` shall return a null pointer.

This is exactly what we need for resizing arrays efficiently. `realloc()` will only copy the existing array contents to a new chunk of memory when it is forced to.

Notice that reallocation is still O(n) in the size of the array, since it may have to copy the array at any or every use. In practice it does a very good job of copying only occasionally, and often appears to be nearly amortized constant time.

### Unstable remove

If you do not need to preserve the order of array elements, you can remove elements from arbitrary array indices in constant time. Operations that may reorder an array or list are called **unstable** operations. The fast, unstable array remove algorithm is:

1. Copy the element at the end of the array over the element you wish to remove.
2. Decrement the array length by 1.

This needs to be refined to handle empty arrays and other corner cases.

### Requirements

<div class="req">

1. Add and commit the single file `t1.c` that contains implementations of the four functions declared in `point_array.h`. It may contain other functions too, but remember you are aiming for high performance so you should probably keep things simple.
2. Use `realloc()` instead of `malloc()` for high performance.
3. Use a constant time unstable remove.

</div>

</div>

<div class="task">

## Task 2: Preallocation: approaching constant time

Reallocation improved things a lot, but we can do quite a lot better with a **preallocation** strategy. The basic idea is to allocate more memory than we need right now, to avoid having to allocate so often in future.

Remember in Lab 5, the field called `unsigned int len` of the struct `intarr_t` (found in `intarr.h`), was used to signify the size of the array `data` (i.e., the size of the allocated memory to this array) as well as the number of elements of type `int` stored in this array. The implication of this association was that the array `data` was always full.

In this Lab 8, we shall decouple the size of the allocated memory from the number of elements currently stored in it. To do so:

1. In the array structure, we shall keep track of the amount of memory allocated in one field (`reserved`), and the number of elements (points) currently stored in the array, in another field (`len`).
2. To append an element:
    1. If the new array is full, we <mark>double the allocated space</mark> (an O(n) operation) to it.
    2. Then, we copy in the new element to the end of the array and increment the array length (i.e., the number of elements) where both copy and increment are O(1) operations.

### An example of amortized constant time

Expanding the array by a constant proportion - in this case two - means that inserting n elements takes O(n) time overall (one O(n) operation to do the expansion, plus n * O(1) operations to insert elements into the space). To put it another way, while a single append operation remains O(n) in the worst case (i.e. when a reallocation occurs), this happens only once every n appends. Thus as the number of appends approaches infinity, the cost per append approaches a constant. This is called _amortized constant time._ A detailed discussion is beyond the scope of this class: see CMPT225: _Data Structures and Algorithms_ for details). But growing memory buffers geometrically is so useful, you should know about it now.

### Trade-off

The cost of this speed is that up to twice the memory is required, and 1.5 times on average. This is often a reasonable trade off. It is trivial to trim the extra space off if you know you are done appending - just `realloc()` the size you need.

Most real-world resizeable-array implementations use this strategy, though they vary on the constant factor chosen. For example Python's lists grow by 9/8 at a time. Java's ArrayList uses 3/2\. The value chosen determines the trade-off between wasted space and the amortized cost of each append.

Your task is to create another version of the point array functions that use this amortized constant time preallocation strategy. The `point_array.h` header file already has the extra field in the array structure (we deliberately ommitted this above):

```C
typedef struct 
{
  size_t len;        // number of points in the array
  size_t reserved;   // amount of memory allocated
  point_t* points;   // an array of 'len' point_t structs
} point_array_t;

```

Reimplement all the array functions to use the `reserved` field as described above. Test your code using the methods described in the lab to show that you have improved performance.

### Requirements

<div class="req">

1. Add and commit the single file `t2.c` that contains implementations of the four functions declared in `point_array.h`.
2. Use the geometric preallocation strategy to get amortized constant time performance.
3. Use a constant time unstable remove.

</div>

* * *

### Note: Measuring time

See the supplied file `demo.c` for examples of the use of the [`gettimeofday()`](http://pubs.opengroup.org/onlinepubs/009695399/functions/gettimeofday.html) library call, which gives you access to the real-time clock on your computer.

</div>

* * *

<div class="labends">Lab 8 complete. [Back to the course web page](../../).</div>

</div>