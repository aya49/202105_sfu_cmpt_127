# Lab 03: Dynamic memory allocation

Open lab 03 on [repl.it](https://replit.com/team/202105cmpt127) > Team Projects > 03_lab

(if repl.it doesn't work, download files [here](./files)))

Review "Guide"s and accompanying slides (we will go over these during the lab lecture).
- [Guide 01](#guide) ([slides]()): 
- [Guide 02](#guide-1) ([slides]()): 
- [Guide 03](#guide-2) ([slides]()): 
- [Guide 04](#guide-3) ([slides]()): 

Try "Practice" problems on repl.it; these will NOT be graded. Note that the SOLUTION given for Practices is just one of many possible SOLUTIONs, better ones may exist ;)

## Guide

### Reminder/primer: Computer architecture memory layout

The memory layout for a process varies a bit by CPU architecture and OS, but the scheme used by Linux on X86 is pretty typical, and shown below. The program's text (compiled code) and static data exist in low memory, the function call stack in high memory, growing downwards, and the "heap" storage space in between. Ignore the "memory mapping segment" for now.

![](./img/linuxmemory.png)

Credit: this image is taken from an [excellent online description](http://duartes.org/gustavo/blog/post/anatomy-of-a-program-in-memory) of the memory layout of Linux by Gustavo Duarte.





### Storing "automatic" variables AND THE BUG!

We have touched on "scope", let's look at it in more detail.

**Automatic variables** or local variables are varaibles used inside the body of a code block; this code block is almost always a function. Automatic variables are called automatic because their storage space is allocated for them automatically e.g. when a function is called.

C implements this very efficiently by allocating all the space for local variables in the stack frame for the function when the function is called (i.e. we get into scope).

When the function returns (i.e. we go out of scope), the stack pointer returns to its previous value, thus "freeing" all the local variables at small and near-constant cost.

Consider file `p1name.c`, it contains a common and nasty C bug:

```C
#include <stdio.h>

char* get_name(void) {
    printf("Please enter your name: ");

    // should be enough space for a name
    char line[1024];

    // reads at most 1023 chars from stdin, up to first newline, 
    // EOF or error.
    if(fgets(line, 1024, stdin) == 0) {// we ALWAYS check for I/O errors
        perror("failed to read a name");
        exit(1); 
    }

    // BUG: never return a pointer (e.g. line array)
    // created in the same body of code (e.g. char line[1024])!
    return line; 
}	

int main(void) {
    char* name = get_name(); // recall <type>* <var name> initiates a pointer!
    printf("Your name is %s\n", name);
    return 0;
}	             
```

The image below shows a sketch of the function call stack for a run of this program up to and including the first line in `main`. 
- (1) When the program begins, the frame for `main()` is on the stack, and its local variables use stack memory for storage. The "stack pointer" keeps track of the current "top" of the stack (growing downwards). 
- (2)-(3) When `get_name()` returns, the stack pointer is placed to the end of calling function `main()`'s stack frame. The space used by `get_name()` will be reused by the next function call.

![](./img/stackframes.png)


This mechanism is why:
1. you must declare all your variables in C: the compiler has to decide how large a function's stack frame needs to be before the function runs;
2. C programs can be very fast: memory allocation and deallocation, are very cheap for automatic variables.


The bug in `get_name()` is that the pointer returned by `get_name()` points to data inside that function's stack frame. When the function returns, that pointer is no longer valid. The illustration below explains what happens.
- (2) the return value of `get_name()` is determined to be the address of the `line` character string. 
- (3) `main()`'s name variable is set to the return value of `get_name()` and that function's stack frame is popped from the stack and thus forgotten. 
- (4) `name` points into the forgotten stack frame. This is a nasty bug, since the correct data _might_ still be there! 
- (5) the function call to `printf()` was entitled to overwrite the old data. There's a good chance that `name` now points to garbage.

![](./img/stackframes2.png)

This bug is one of the main reasons people complain about C. The code looks like it should work: the intent is clear; it compiles; it might even work in testing. Yet details of the implementation mean that the code is fatally bugged. This is undoubtedly a bad thing. The fact that it may work in testing is particularly awful.

The good news is that modern compilers will generate a helpful warning if you return a pointer to memory allocated for an automatic variable. 

**Try it yourself!**: Compile `p0name.c` and read its warnings; try to run the program and confirm it breaks as anticipated:
```
$ gcc p0.c -o p0name.o -Wall
```

**Moral of the story**: 
- You CAN NOT return a POINTER that points to an address generated in the stack frame i.e. a local variable.
- You CAN return a POINTER that points to an address generated outside the stack frame.
- You CAN return a LOCAL VARIABLE VALUE (e.g. so far, a variable that is not an array).
- **Read your warnings!** Better still, always use `-Wall` and fix all warnings in your builds, every time.


## First Solution: Allocate in caller

There are two different approaches to fixing this problem. The simpler and faster solution - and thus the best one when you can use it - is to have the calling function allocate the array and pass in a pointer to it, like so:

```C
#include <stdio.h>
#include <stdlib.h>

void get_name(char line[], int maxlen) {
    printf("Please enter your name: ");

    // reads at most maxlen-1 chars from stdin, up to first newline, 
    // EOF or error.
    if(fgets(line, maxlen, stdin) == 0) {// we ALWAYS check for I/O errors
        perror("failed to read a name");
        exit(1);
    }
}	

int main(void) {
    char name[1024];
    get_name(name, 1024);

    // we don't need to be lucky this time
    printf("Your name is %s", name);

    return 0;
}	             
```

This time `get_name()` receives a pointer to array `name` which is stored inside `main()`'s stack frame. Since this is guaranteed to exist longer than the call to `get_name()` this will work correctly.

<div class="steps">

#### Try it yourself

One of the source files you have downloaded for this lab, namely [get_name_parent.c](get_name_parent.c), contains the code above.

1. Open this file in your text editor and have a read through it.

2. Then compile it as follows, enabling all warnings to verify that the program builds without complaining about "function returns address of local variable":

        <pre>$ gcc -Wall get_name_parent.c -o gnp```

3. Run the program and confirm that it works correctly.

Satisfy yourself that you understand it before moving on.

</div>

## Second solution: Explicit memory allocation

The above method requires you to know how large an array your function call will need at most, and to allocate that much memory in advance. It is quite possible that you just don't know how much data to expect. Also, if the amount of data you expect is usually very small, but _could_ be very large, it would be wasteful to always allocate a huge array just in case.

In these cases, we must allocate memory explicitly, using the system call `malloc()`. This allocates memory on the heap, and returns a pointer to it. The allocation will persist until explicitly de-allocated by a call to `free()`. Because the allocation is on the heap, it is available to any function that knows its address, regardless of the current state of the stack.

Here is a simple example, omitting error checking for clarity:

<pre class="prettyprint">// choose a random array length
int len = rand();

// allocate memory for an array of len ints
int* array = malloc(len * sizeof(int));

// array is now a pointer to an array of len integers on the heap
// OR zero (null pointer) if the allocation failed

// ...
// (use the array)
// ...

// I am definitely finished with the array
free(array);

// make sure to cause a segmentation fault (segfault) if I use 
// it again by mistake
array = NULL; // or array = 0;
```

The argument to `malloc()` is a size in bytes, so we almost always use sizeof(some_type) as a multiplier. It returns a special type: a `void*` (pronounced "void pointer"). By default C allows a void pointer to be assigned to any other kind of pointer without having to be converted explicity. All pointers are just memory addresses, after all.

<div class="steps">

#### A more realistic example

Maybe you are not convinced that this could ever be useful.

One of the source files you have downloaded for this lab, namely [randomrandom.c](randomrandom.c), contains a semi-realistic example with error checking included.

1. Open this file in your text editor and have a read through it.

2. Then compile it as follows:

        <pre>$ gcc -Wall randomrandom.c -o rr```

3. Run the program and confirm that it works as expected.

Make sure you understand the code completely before you move on.

</div>

## Limited stack size

There is one more reason to use `malloc()`: the size of the stack is very limited. The exact size depends on your OS, CPU architecture, and current configuration, but is generally a few MB at most, and can be as small as a few KB on embedded systems. The stack has to be limited in size to avoid it growing into the heap and corrupting both segments (called "smashing the stack"). You should allocate large things on the heap with `malloc()` instead. If the heap is out of space, `malloc()` tells you so and you can either cope with it gracefully or quit your program. Automatic variables on the stack do not give you this opportunity.

Once again, it is a downside of C that you must think about things like this. As usual, it's the price you pay for speed and control.

#### How large is too large for the stack?

The answer is system-dependent, but anything over a few KB should probably go on the heap.

## Say that again?

If you'd like to read similar material on memory management, presented differently, [here is a good write-up by Paul Gribble](https://gribblelab.org/CBootCamp/7_Memory_Stack_vs_Heap.html).

# Requirements

<div class="req">

The task structure in this lab is different to your previous labs.

1. Your job, in this lab, is to finish the implementation of several function definitions in the supplied file `imgops.c`. The grading robot will exercise these functions to see if they meet the requirements (specifications).

2. Read the documentation in `imgops.c` or in `imgops.h`. This documentation describes what each function does and the requirements you must satisfy when implementation each function.

3. Implement and compile a task at a time.

4. To test the function(s) of a task, extend the program in `test.c` so that it calls each of your function(s) and displays the resulting image in its own window.

        How to do this will be demonstrated at the beginning of the lab session.

        Writing tests is part of the work of a programmer, so get used to testing as you go.

5. Once you have implemented, compiled and tested a task in `imgops.c`, you can add, commit and push this file to your Git repo and move on to the next task.

The grading robot will grade the pushed file, reporting on the task you have implemented and will mark the other yet-to-be implemented tasks as unsuccessful (red boxes). Repeat the above steps until all your tasks have successfully been tested (green boxes).

Important: DO NOT add a `main()` function in `imgops.c`. Keep it in `test.c`. This is because the grading robot has its own test driver program with a `main()` function. An extra `main()` will prevent the grading robot's test program from compiling.

Also important: DO NOT make your `imgops.c` code rely on any other files. For testing, the grading robot copies only your `imgops.c` and will not bring any of your other files along.

</div>

* * *

<div class="labends">Lab 3 completed. [Back to the course web page](../../).</div>