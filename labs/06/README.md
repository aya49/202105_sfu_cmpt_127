# Lab 06: testing memory allocation performance

Download lab files [here](./files.zip).

Today we are going to look at different strategies for resizing arrays (e.g. inserting elements, deleting elements). Recall: amortized analysis Θ() (average performance) and big O analysis O() (worst case performance).

Review "Guide"s and accompanying slides (we will go over these during the lab lecture).
- [Guide 01](#guide) ([slides]()): reallocation (inserting elements into arrays in O(n)) and unstable remove (removing elements from arrays in O(1))
- [Guide 02](#guide-1) ([slides]()): preallocation (inserting elements into arrays in Θ(1))

Try "Practice" problems; these will NOT be graded. Note that the solutions given for Practices is just one of many possible solutions, better ones may exist.
- [Practice 01](#practice-01)
- [Practice 02](#practice-02)


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

**Big O analysis**: insertion takes O(n); reallocation is in the size of the array, since it may have to copy the array. 

**Amortized analysis**: insertion takes Θ(1); In practice, it does a very good job of copying only occasionally, and often appears to be nearly amortized constant time.

### Unstable remove

If you do not need to preserve the order of array elements, you can remove elements from arbitrary array indices in constant time O(1). This is an example of an **unstable operation**, one that may reorder an array or list of elements. The fast, unstable array remove algorithm is:
1. Copy the element at the end of the array over the element you wish to remove.
2. Decrement the array length by 1.

This needs to be refined to handle empty arrays and other corner cases.

**Big O and amortized analysis**: deletion takes O(1).

If we want to remove an element in a stable manner without changing the order of the array, then we would remove the element at index `i` and shift all the elements after it forward by one. The process of shifting would cause this method of removing an element to cost O(n).

## Practice 01

**REQUIREMENT**: you will write to file `p1point.c`, implementations of the four functions declared in `p1point.h`. It may contain other functions too, but remember you are aiming for high performance so you should probably keep things simple.
- Use `realloc()` instead of `malloc()` for high performance.
- Use a constant time O(1) unstable remove.

`p0.c` includes examples of the use of the [`gettimeofday()`](http://pubs.opengroup.org/onlinepubs/009695399/functions/gettimeofday.html) library call, which gives you access to the real-time clock on your computer so that you can time how long your functions take to run.

**HINT**: in functions where there is no return `void`, but you still want to verify variables, you can use `assert()` from `#import <assert.h>`. It allows you to throw error messages if you find something off, look it up!

**TESTING**: use `p1.c` to test the performance of your functions by running:
```
$ make p1
$ ./p1
```

Try it yourself first; then verify your solutions [here](./files/solution/p1point.c).

# Preallocation (Θ(1))

## Guide

`realloc()` improved things a lot, but we can do better with preallocation.

**Preallocation**: The basic idea is to allocate more memory than we need right now, to avoid having to allocate often in future.

In this lab, we decouple the size of the allocated memory from the number of elements currently stored in it. To do so:
1. In the array structure, we shall keep track of:
    - the amount of memory allocated in one field (`reserved`), and 
    - the number of elements (points) currently stored in the array, in another field (`len`).
2. To append an element:
    - If the new array is full, we **double the allocated space** (an O(n) operation) to it and ensure `reserved` reflects this.
    - Then, we copy in the new element to the end of the array and increment the array length `len` (i.e., the number of elements) where both copy and increment are O(1) operations.

**Big O analysis**: insertion takes O(n); inserting n elements takes O(n) time overall (O(n) to do the expansion + (n * O(1)) operations to insert elements). 

**Amortized analysis**: Θ(1); while a single append operation remains O(n) in the worst case (i.e. when a reallocation occurs), this happens only once every n appends. As the number of appends approaches infinity, the cost per append approaches a constant. This is called **amortized constant time**. A detailed discussion is beyond the scope of this class: see CMPT225: _Data Structures and Algorithms_ for details). But growing memory buffers geometrically is so useful, you should know about it now.

The cost of this speed is that up to twice the memory is required, and 1.5 times on average. 

This is often a reasonable trade off. It is trivial to trim the extra space off if you know you are done appending - just `realloc()` the size you need. Most real-world resizeable-array implementations use this strategy, though they vary on the constant factor chosen. For example Python's lists grow by 9/8 at a time. Java's ArrayList uses 3/2. The value chosen determines the trade-off between wasted space and the amortized cost of each append.

The `std::vector` in C++ is the same as an array except it can automatically change in size i.e. it has implemented preallocation Θ(1) for you so you don't have to (see [push-back](https://www.cplusplus.com/vector::push_back)).

## Practice 02

**REQUIREMENT**: you will create another version of the point array functions that use this amortized constant time preallocation strategy. Reimplement all the array functions to use the `reserved` field in `point_array_t` as described above to file `p2point.c`. The `p2point.h` header file already has the extra field `reserved` in the array structure.
- Use the preallocation strategy to get amortized constant time performance.
- Use a constant time O(1) unstable remove.

**TESTING**: use `p2.c` to test the performance of your functions by running:
```
$ make p2
$ ./p2
```

Try it yourself first; then verify your solutions [here](./files/solution/p2point.c).


# Bonus material: why is preallocation amortized constant time?

## Big O analaysis

Let's start by calculating how many operations preallocation requires for our big O analaysis.
- `n = 2`: let's say you start with a size `1` array `[ ]`.
- `m = 2`: for preallocation, whenever we increase the size of the array, we double the size of array i.e. we increase the array size by a factor of `m = 2`.
- `log(n,m)` = number of preallocations: we conduct preallocation when our array is filled up at size `n = 2,4,8,16,...` i.e. `n^i` where `i` is the `i`th preallocation. Thinking backwards, when we reach `n=16`, we would have conducted preallocation `4 = log(16,2) = log(n,m)` times (where the second argument to `log` is the log base).
- O(n) = the sum of the number of operations in each preallocation: 
    - the number of operations in preallocation can be upper bounded by `1 + 2 + 4 + ... + 2^i` i.e. in the first, second, and third preallocations, we create 1, 2, and 4 empty array elements respectively, and so on. Such series is called geometric series: `1 + 2 + 4 + ... + 2^i = (2^i - 1)`. Using this property, let's summarize the number of operations using `2^i` or `m^i`.
    - Since `i` is the number of preallocations, we can replace it too: `m^log(n,m)`. 
    - Finally, since your exponent and log base uses the same factor `m`, they cancel out to give `m^log(n,m) = n`.

## Amortized analysis

Amortized analysis asks for the average number of operations. Let's start by looking the same example except this time, we do each insertion operation one by one:

```
insertions:
1: [1]
2: [1][2] (i=1, first preallocation!)
3: [1][2][3][ ] (i=2)
4: [1][2][3][4]
5: [1][2][3][4][5][ ][ ][ ] (o=3)
6: [1][2][3][4][5][6][ ][ ]
...
```
Amortized observations:
- Not all insertions are O(n), insertion operation 3, 5, 6, ... are O(1) operations.
- To be exact, for each of the `n` insertions, we have this many operations: `(1+(1+1)+(1+2)+1+(1+4)+1+...) / n`.
- If we split up the constant operations from those with preallocations, it would be: `((1+1+1+...) + (1+2+4+...)) / n`.
- We know that the second preallocation term occurs is roughly O(n) and the first term is also roughly O(n); so `2 n / n` is roughly Θ(1).

## Big O vs amortized analysis

The main difference between our big O analysis and our amortized analysis is the first term. 
- In big O analysis, we assume the worst case where every insertion requires a doubling in array size. 
- Whereas in amortized analysis, we realize that this is not the case and that most of the time, insertion will be constant time.


# Bonus material: C vs C++

C is a subset of C++; all C functions/keywords/code will work with a C++ compiler. In this section, we go over some functions/keywords that are analagous to each other in C and C++.

Let's look at the difference between C functions (`malloc()`, `realloc()`, `free()`) and C++ operators (`new`, `delete`).

|            | `new` / `delete`  | `malloc()` / `free()`  |
|------------|-------------------|--------------|
| It is a... | operator          | function     |
| Returns    | `type *` (it's type-safe!) | `void *` |
| On failure | throws error      | returns NULL |
| It also... | calls the constructor / destructor | |

- In C++, instead of using `realloc()` you can use `std::string` or `std::vector` they support change in size.
- The C++ version is type safe
- ALWAYS use `malloc()` and `free()` together, and `new` and `delete` together. If you initialized an object using a constructor, you need to remove it using its destructor

As a rule of thumb, unless you must use C, alays use `new` and `delete`.

Below are examples of using these functions and operators to create and remove 1D and 2D arrays.

C:
```C
int* A = malloc(16 * sizeof(int)); // 1D array

free(A);


int** B = malloc(4 * sizeof(int*)); // 2D array
for (int i=0; i<4; i++) {
    B[i] = malloc(4 * sizeof(int));
}

for (int i=0; i<N; i++) {
    int* e = B[i];
    free(e);
}
```

C++:
```C++
int* A = new int[16]; // 1D array

delete[] A;


int** B = new int*[4]; // 2D array
for (int i=0; i<4; i++) {
    B[i] = new int[4];
}

for(int i=0; i<5; ++i) {
    delete[] B[i];   
}
delete[] B;
```


# Credit

Last updated 2021-05 by Alice Yue. 

Course material designed, developed, and initially taught by [Prof. Richard Vaughan](https://rtv.github.io/); this material has since been taught and adapted by Anne Lavergn, Victor Cheung, and others.

(This lab was reviously lab 08)
