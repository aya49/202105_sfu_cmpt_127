# Lab 06: Testing memory allocation performance

Today we are going to look at different strategies for resizing arrays (e.g. inserting elements, deleting elements).

Recall: amortized analysis $\Omega$ (average performance) and big O analysis $O$ (worst case performance).

# Reallocation `realloc()` (resizing arrays in O(n)) and unstable remove

## Guide

The supplied header file `point_array.h` defines the following structures to represent points in 3D space, and an array to contain them, similar to examples you have seen before:

```C
typedef struct point {
  double x, y, z;    // a point location in 3D space
} point_t;

typedef struct {
  size_t len;        // number of points in the array
  point_t* points;   // an array of 'len' points (point_t structs)
} point_array_t;
```

It also declares four functions for manipulating `point_array_t` arrays. Each takes a pointer to an array structure as their first argument. Notice that the `init` and `reset` functions do a similar job to the `create` and `destroy` functions we have seen before, but with a slightly different interface. This style allows us to use structs allocated on the stack, which can be useful. 

Therefore, `init` must NOT call `malloc()` nor must it call `realloc()` since the memory for the struct has already been allocated (automatically, on the stack) and the memory allocation call to obtain the memory for the array is done in `append()`.

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

In graphics-heavy programs like games, we often have arrays of 3D points that are very large, perhaps with hundreds of thousands or millions of points. For decent performance we need to be able to add points to the array very quickly. 

Notice that the array interface does not have a resize function: just an append for adding one point at a time. 

The only memory allocation standard library call we have seen so far is [`malloc()`](http://pubs.opengroup.org/onlinepubs/009695399/functions/malloc.html), which takes a single argument specifying how much memory it should allocate. 

Now we introduce the [`realloc()`](http://pubs.opengroup.org/onlinepubs/009695399/functions/realloc.html) standard library call, which allows us to resize our chunk of already allocated memory.

- INPUT: We pass `realloc()` the pointer we obtained from an earlier `malloc()` or `realloc()` and a **new** size.
- OUTPUT: `realloc()` will **reallocate** a chunk of memory of the new size.
    - If the memory allocation system can find enough space at the existing address (e.g. when the new size is smaller than the original size or there is enough room to expand the array), `realloc()` will:
        1. extend the allocated memory, and
        2. return the original pointer.
    - If the memory allocation system could only find enough space starting at another address, it will:
        1. allocate the new chunk of memory,
        2. copy the content of the old chunk into the new chunk,
        3. free the old chunk, and
        4. return a pointer to the new chunk.

**Big O analysis**: insertion takes $O(n)$; reallocation is in the size of the array, since it may have to copy the array. 

**Amortized analysis**: insertion takes $\Omega(1)$; In practice, it does a very good job of copying only occasionally, and often appears to be nearly amortized constant time.

### Unstable remove

If you do not need to preserve the order of array elements, you can remove elements from arbitrary array indices in constant time $O(1)$. This is an example of an **unstable operation**, one that may reorder an array or list of elements. The fast, unstable array remove algorithm is:
1. Copy the element at the end of the array over the element you wish to remove.
2. Decrement the array length by 1.

This needs to be refined to handle empty arrays and other corner cases.

**Big O and amortized analysis**: deletion takes O(1).

## Practice 01

**REQUIREMENT**: create a file `p1.c` that implementations the four functions declared in `p1.h`. It may contain other functions too, but remember you are aiming for high performance so you should probably keep things simple.
- Use `realloc()` instead of `malloc()` for high performance.
- Use a constant time $O(1)$ unstable remove.

# Preallocation (approaching O(1))

## Guide

`realloc()` improved things a lot, but we can do better with preallocation.

**Preallocation**: The basic idea is to allocate more memory than we need right now, to avoid having to allocate often in future.

In this lab, we decouple the size of the allocated memory from the number of elements currently stored in it. To do so:
1. In the array structure, we shall keep track of:
    - the amount of memory allocated in one field (`reserved`), and 
    - the number of elements (points) currently stored in the array, in another field (`len`).
2. To append an element:
    - If the new array is full, we **double the allocated space** (an $O(n)$ operation) to it and ensure `reserved` reflects this.
    - Then, we copy in the new element to the end of the array and increment the array length `len` (i.e., the number of elements) where both copy and increment are $O(1)$ operations.

**Big O analysis**: insertion takes $O(n)$; inserting n elements takes $O(n)$ time overall ($O(n)$ to do the expansion + ($n \dot O(1)$) operations to insert elements). 

**Amortized analysis**: $\Omega(1)$; while a single append operation remains $O(n)$ in the worst case (i.e. when a reallocation occurs), this happens only once every $n$ appends. As the number of appends approaches infinity, the cost per append approaches a constant. This is called **amortized constant time**. A detailed discussion is beyond the scope of this class: see CMPT225: _Data Structures and Algorithms_ for details). But growing memory buffers geometrically is so useful, you should know about it now.

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

# Credit

Last updated 2021-05 by Alice Yue. 

Course material designed, developed, and initially taught by [Prof. Richard Vaughan](https://rtv.github.io/); this material has since been taught and adapted by Anne Lavergn, Victor Cheung, and others.

(This lab was reviously lab 08)