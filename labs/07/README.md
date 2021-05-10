# Lab 07: Testing and linked lists

Linked lists have been described in CMPT 125, but it doesn't hurt to see them again.

# Drawing - a tool for thinking

Drawing diagrams is very helpful before writing code that modifies lists. In general, sketching machines - including code - is a tool for thinking; even if you think you know what you are doing, drawing out the operations is a concrete test of your understanding. Even very experienced people with great intuition use drawings for thinking.

# Linked lists

## Guide

**Linked lists** are data structures that contain a sequence of data elements, like arrays, but with different dynamic properties. The key idea in the linked list is to use a simple data structure to store each data element along with a pointer to the next element in the list. The end of the list is denoted by a `NULL` pointer.

Our implementation uses a second data structure called a **header** to store pointers to the first (head) and last (tail) elements in the list.

The list is assembled as follows:

First a `list_t` structure is allocated on the heap, with its head- and tail-pointers set to NULL, representing an empty list.

![](../img/list1.png)

To insert the first value into the list, a new `element_t` is allocated on the heap, the value is stored in it, and the header's head- and tail-pointers are both set to point to it. The first element's next-pointer is `NULL` to indicate it is the last element in the list.

![](../img/list2.png)

When a subsequent element is added, the next-pointer of the tail element and the tail-pointer of the header are both changed to the address of the new element:

![](../img/list3.png)

One more addition using the same mechanism. Notice that the tail element always has its next-pointer set to `NULL`.

![](../img/list4.png)


A common variant is the **double-linked list** in which every element contains a previous-pointer in addition to the next-pointer. Double-linked lists can be traversed forwards and backwards, at the cost of a little more storage space per element.

### Linked lists vs arrays: runtime

| Task | Arrays | Linked lists | Double-linked list |
|------|--------|--------------|--------------------|
| Add an element to the start/end | O(n) | **O(1)** | **O(1)** |
| Access an element based on index| **O(1)** | O(n) | O(n) |

List elements are therefore best accessed in order, since accessing the next element takes constant time.

## Tasks 1..5

The compressed file you downloaded contains a header file `list.h` that contains an interface specification for a linked-list-of-integers data structure. See the Guide above for notes on linked lists. Six slightly different implementations are provided, in files `tN.c` where N = [1..5]. The file `main.c` contains a very weak test program for the linked list code.

The `Makefile` will build programs t1 through t5, each linking the same `main.c` with one of the list implementation C files.

Build each program by naming it as your 'make' target, e.g.

```
$ make t1
$ make t5

```

The above two make commands will each create an executable 't1' and 't5'. You can also build all programs by using the following command:

```
$ make all
```

Running the resulting programs, you will see that every one passes the test in `main.c`. At this point the beginner might relax and load up Minecraft. But we have left blissful ignorance behind us. We are suspicious. In fact all of these implementations contain bugs.

Your task is to extend `main.c` to thoroughly test the list implementations. Your program must reliably distinguish all these faulty implementations from a correct one.

The grading robot tests work as follows: Your `main.c` will be compiled with each of tN.c as well as a bug-free version (not supplied to you). You pass Task N if your program consistently returns 1 when it runs the buggy code, but 0 when it runs the bug-free code. Remember: returning 1 means an error has occured during the execution of your program while returning 0 means that your program successfully executed.

### Requirements

<div class="req">

1. A program built from your `main.c` and linked against any implementation of the functions in `list.h` must return 0 if the functions are bug-free, or 1 if they contain one or more bugs.
2. Preferably, your program should not crash or halt on `assert()`. But a crash (e.g., segmentation fault) or assertion will be recorded as indicating the code contained bugs, just like with the grading robot.
3. Preferably, print an explanatory error message on stdout describing the problem you discovered.
4. You may produce (a sensible amount) of other text output on stdout or stderr if you wish.
5. The grading robot will not test your text output: only the return value. Try to make the text output helpful for yourself or an instructor/TA helping you.

</div>

### Submission

Commit a revised version of `main.c`. This will be linked against each of the buggy list implementations `tN.c` used by the grading robot in the same way you did locally. The grading robot also has a correct version of the code. Your program should return zero when linked to the correct code, and non-zero when linked to any of the buggy versions.

Task N will be passed if your program can reliably distinguish between a buggy and correct version of the code. To test reliability, your test program will be run several times. It must correctly detect bugs or no-bugs every time.

</div>

<div class="task">

## Task 6

### Requirements

<div class="req">

1. Commit a new file called `list.c` containing correct implementations of all the functions described in `list.h`.
2. You may use any piece(s) of the supplied code, or write your own.
3. Your code should pass all your tests (i.e., the `main.c` you extended in Tasks 1 to 5, and the grading robot's tests.

</div>

### Submission

Commit a single C file called `list.c`.

</div>

<div class="task">

## Task 7

Write a function that sorts an instance of our linked list of integers from smallest to largest value.

### Requirements

<div class="req">

1. Commit a new file called `sort.c` containing at least the function `list_sort()`
2. Your file must not contain a `main()` function or change the structures in `list.h`.
3. The function must #include the `list.h` header...
4. ... and be consistent with the function declaration:

        <pre class="prettyprint"> void list_sort(list_t* list); 
```

5. **Use [an efficient algorithm](http://en.wikipedia.org/wiki/Sorting_algorithm), i.e., an algorithm that sorts in O(n log n)!**
6. Did you read requirement 5?
7. Do **not** turn your list into an array, sort it, then turn it back into a list. That's cheating.

</div>

### Submission

Commit a single C file called `sort.c`.

</div>

* * *

# Credit

Last updated 2021-05 by Alice Yue. 

Course material designed, developed, and initially taught by [Prof. Richard Vaughan](https://rtv.github.io/); this material has since been taught and adapted by Anne Lavergn, Victor Cheung, and others.