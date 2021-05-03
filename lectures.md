14 weeks

- wait and get students to ask questions
- keywords in C/C++, semi colon, brackets, syntax
- garbage collected C/C++
- mention time it takes to complete labs

- Dynamic memory (maloc and free) (new and delete in C++); explain in detail? all new must end with delete or else run out of memory (memory leak if errored! won't delete)

- repl.it use sfu id! SAVE YOUR WORK LOCALLY, it'll be gone. if you don't do it in teams, it will be public :) tell them answer is out there
- documentation generator for cpp: doxygen
  - divide and conquer! software engineering
  - style and documentation: http://www.edparrish.net/common/cppdoc.html

- examples in class try themselves with variations
- makefile for each assignment
- for amortaion: how many lines certain lines are executed for sorting; explain the idea

week 01 2021-05-11
- 00.1 remote login vpn? outside of canada? else won't do tasks
- 00.2 course outline; remote and lab times

week 02 2021-05-18
- 00.3 course outline; content
- 00.4 communication: zoom etiquette, lab hours, office course, canvas discussion, peer tutoring
- 00.5 gitlab basics (VCS)

week 03 2021-05-25
- introduction to C vs C++
  - compiled language > object code (remove comments, > assembler code .c > binary code .o > link binary code to other binary codes)
  - C is strongly typed (all variables have type defining how they are stored in memory and how they are represented in code: sizeof())
  - C vs C++ printf vs std::cout (latter handles type)
    - [intprintf(constchar*format,...)] printf("ascii: %d, character: %c")
  - variables store addresses of a space in memory that holds other variables?
    - inti= 0; printf("Address of iis %p\n",&i); # &i is the address
  - read in formatted inputs (standard in) (default is )
    - [intscanf(constchar*format,...)] scanf("%d",&i); #&i is address where value should be stored; returns number of stored variables
  - conditions: if/else Boolean expression: ==, !=, <, >, <=, >=; logical operations: &&, ||, !
  - loops: repeat code; while, do-while, for (initialize; boolean; modify); break, continue (don't use if don't have to, hard to trace)
  - Google, http://www.cplusplus.com/reference/, https://en.cppreference.com/w/c
- 01.1 software development process (req, design, code, test), use internet
- 01.2 task 1.9 summary
- 01.3 gitlab
- 01.4 academic dishonesty
- LAB 01
  - set up: linux/git
  - task 1: compiling hello world ADD lab 2 task 6 (output to file)
  - task 2: C, variable data types and storage size; output storage size in bits
  - task 3: input/print and pointers
    - ADD C++ - sprint/scanf > cout/cin
  - task 4: if/else
  - task 5: loops
  - task 6: loop over scanf; statistics
  - task 7: horizontal graph; loop, in/output
  - task 8/9: pyramid projection; no need for 2/3rd number...

week 04 2021-06-01
- introduction to C continued + muttability?
  - function declaration, definition
    - function (name, parameters, return value): reusable piece of code; call functions, function call functions/themself (recursion), store in different files (black box)
    - function diagram
    - function call in same file
    - void parameter, return functions (no return, just prints); terminate with "return"
  - header files, implementation files
    - level 1: put all function definition in another file
    - level 2: make a header file with just function declarations and an implementation file with all definitions; use "" instead of <>
      - e.g. <stdio.h>, <math.h> for user-defined header files
  - arrays: 1 name store a bunch of the same value types (elements)
    - int a; int a[100]; int a[] = {1,3,5}; int a[100]; for (int i=0; i<100; i++) { a[i] = 0; }
    - functions need to know size of array and will change content: void addOne (int a[], unsigned int len) {}; addOne(a, 100)
    - C strings (char arrays that end with '\0')
    - e.g. char command[] = "copy"; is the same as: char command[] = {'c',...,'\0'}
    - e.g. int main (char* argv[]) {} --- argv[0] points to a C string, what's [0][0]?
  - algorithm analysis: O(n)
  - arithmetic:+-*/ for numbers (e.g. int(5), long(10), float, double), % for integers (10%2 = 0; 10%3 = 1; 3%10=3)
- 02.1 weekly workflow: lecture, lab task, repo
- 02.2 tips: ADD directory, path, relative...
  - task 1: header files (system supplied <>, my ""), functions, split code into many files ---THEY ALREADY KNOW MAKEFILE
  - (task 2: arrays; pass to function) ADD about pointers * and &
    - * pointer to memory
    - * int  var = 20; int  *ip; ip = &var;
  - (task 3: swap array elements) ADD pointers in functions have void output because edit actual value!
  - task 5: arguments; contains; look up C library string.h; ADD 
    - use std::string name("Hall"); OR std::string name; name = "Hall"; OR std::cin >> name;
    - multidimensional arrays
  - (task 6: redirect stdin and stdout to a file; create a function)
  - task 8: letter frequency; don't do 26 if statements, one for each letter
  - task 10: does a point lie in a rectange? two points of a rectangle
- lab quiz 1 (about)

week 05 2021-06-08
- raster images
  - w x h x 3 (rgb) pixels (1 for greyscale)
  - some instructions on zip file + call draw_Startup
  - new (calls constructor of a class) & delete (calls destructor of a class) in cpp vs malloc() & free() --- classes just learned
    - both allocate the memory dynamically in heap
    - keyword vs function
- 03.1: read lab 3 guide; download zip file (already done); no tasks
  - task 3: memory management, raster/bitmap image representation
  - task 6: other image functions
  - task 7: normalize??
  - task 8: answer given??
- challenge yourself

week 06 2021-06-15
- lab quiz 1

week 07 2021-06-22
- lab quiz 2

week 08 2021-06-29
- composite data types: combine multiple data types; can be used in arrays
  - struct {<type> field1; ...} <compositeType>; ADD -- vs class (private by default and has methods)
  - typedef struct {uint8_t* pixels; unsigned int cols; unsigned int rows;} img_t; img_t myImg;
  - access fields (variables in ct): myImg.cols = 400; myImg.rows = 300;  myImg.pixels = malloc(sizeof(uint8_t)*400*300);
  - access fields if composite variable is a pointer: img_t* myImgPtr = malloc(sizeof(img_t)); (*myImgPtr).cols = 400; myImgPtr -> rows = 300; myImgPtr -> pixels = malloc(sizeof(uint8_t)*400*300); printf("Number of columns: %d\n", (*myImgPtr).cols);
  - take care when assigning its value to another value, especially with pointer fields (SEE EXAMPLE)
- shallow vs deep copy
  - shallow: copy composite type as is, ok for most primitive types (have own copies); not ok for pointers (both have same address)
  - deep: copy non-pointer primitive values the same way BUT makes new memory space for each pointer (new copy of values are created if it's a pointer)
- composite data type free-ing: must free memory allocated to its fields first:
  - img_t* myImgPtr= malloc(sizeof(img_t));myImg-> cols = 400;myImg-> rows = 300;myImg-> pixels = malloc(sizeof(uint8_t)*400*300);//done using myImgPtr; free(myImg-> pixels); //free fields first; myImg-> pixels = NULL; //a good habit to have; free(myImgPtr); //free the variable last; myImgPtr= NULL; //a good habit to have
- sort: insertion sort, bubble sort, quick sort, merge sort, ..., for task 4 (insert or bubble might be easier)
- 05.1: reminder to push code, 
  - task 5; array manipulation functions (download zip) incremental development; stubs (place holder for code not written yet --- toby will teach unit test)
  - task 7, 6; stack: push and pop

week 09 2021-07-06 SHORT
- file i/o (except text and image files in lab 2 and 3)
  - XDR: external data representation stores data (en/decode write/read data types; formats content types)
  - stored as files identified by a relative/absolute path
  - "file pointer" ("read/write position") to keep track of where in file is accessing
  - modes: read, write
  - open (new file, creates file), write (store and move on from data), read (get and move beyond), close (stop accessing and tell os it's free), seek (move file pointer without write/read)
  - e.g. #include<stdlib.h> SEE EXAMPLES
- 06.1: is a function return valid? open/create, close, write to, read from files
  - task 1: int array into binary file (req: call fwrite for len, 1 call to fwrite for whole array), 2 (req: call fwrite for each number in arrray i na for loop), 5: two ways to read/write composite data type; finish lab 5 first
    - fscanf: http://www.cplusplus.com/reference/cstdio/fscanf/?kw=fscanf
    - multi-source file model
  - (task 2: array into json)

week 10 2021-07-13
- linked lists, fast insert deletes (arrays, stacks for pair checking LIFO, queue for scheduling FIFO)
  - head and tail element storage (typedef struct list {element_t* head; element_t* tail;} list_t;) + nodes (typedef struct element {int value; struct element* next;} element_t;) = value of a datum and memory address of next node (scttered in heap memory, no need contnuous)
  - SEE IMAGES + time complexity (compare to arrays, both O(n) except indexing)
    - start empty (head and tail are null) > first node points to null, both head and tail > second node
    - search: traverse whole list (while not tail)
    - delete: change pointers first
  - double linked list (prev and next)
- 07.1: write tests, linked list operations, list sorting
  - (task 1-5)
    - test cases: no need to test for list == NULL; test each possible return value (empty, 1 element, 2 element, +); test if data rep is changed correctly
    - hint: make a pointer variable ot the same type to occupy memory and then free it.
  - task 6: correctly implement list functions
  - task 7: sort list

week 11 2021-07-20
- lab quiz 3

week 12 2021-07-27
- malloc vs realloc ( returns same address realloc(ptr, newLength*sizeof(int)), if itcan't allocate new size, puts somewhere else, copy content over, free original space, return address of new space, if no new space return NULL);; please please please use: https://stackoverflow.com/questions/3482941/how-do-you-realloc-in-c
- assert() vs free(ptr); ptr = NULL;
- 08.1: memory allocation strategies (2) (len=no. points in array, reserved=allocated memory for array; when are they different)
  - task 1: demo.c t0.c -o t0 ...
    - difference with lab 7: list_create allocates new memory for  list, lab 8 point_array_init(point_array_t*) doesn't because array already exist in memory
    - unstable (order changes) remove: copy element at array end over removed element + reduce array length by 
- 08.2: memory allocation strategies (3) how long it takes to append to array with these 3 (new array, copy over; realloc and add 1; realloc and double size)
  - task 2: resize array
  - ADD measure times
  - Big O amortization: 


week 13 2021-08-03
- 10.1: C++ class -- in week 7?
- C vs C++, history, file name convention, struct vs class (public vs private), object = class instance (CMPT 213 more on oop), use class::object, consturctors and desturctors
- lab 09: based on images in lab 5!! and malloc in lab 3
  - C++ classes (vs structs): de/constructor, 2D arrays, refactor code
  - task 1: write image file in cpp
  - task 2: extend 1 with save and load (lab 6)
  - (task 3: alternate implementation with 2D arrays)






week 14 2021-08-10
- lab quiz 4



add problem pseudocode
every other week programing

canvas might be better for quizzes within 24hr

