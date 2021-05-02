14 weeks

mention time it takes to complete labs

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
- 02.2 tips: 
  - task 1: split code into many files
  - (task 3: swap array elements)
  - task 5: contains; look up C library string.h
  - task 6: create a function
  - task 8: don't do 26 if statements, one for each letter
  - task 10: two points of a rectangle
- lab quiz 1 (about)

week 05 2021-06-08
- raster images
  - w x h x 3 (rgb) pixels (1 for greyscale)
  - some instructions on zip file + call draw_Startup
  - new (calls constructor of a class) & delete (calls destructor of a class) in cpp vs malloc() & free() --- classes just learned
    - both allocate the memory dynamically in heap
    - keyword vs function
- 03.1: read lab 3 guide; 
  - task 3: memory management, raster/bitmap image representation
  - task 6: other image functions
  - task 7: normalize
  - task 8: answer given
- challenge yourself

week 06 2021-06-15
- lab quiz 1

week 07 2021-06-22
- lab quiz 2

week 08 2021-06-29
- composite data types: combine multiple data types
- shallow vs deep copy
- 05.1: reminder to push code, 
  - task 5, 7, 6

week 09 2021-07-06
- 06.1: is a function return valid? open/create, close, write to, read from files
  - task 1,2,5

week 10 2021-07-13
- 07.1: find bugs
  - task 1-5

week 11 2021-07-20
- lab quiz 3

week 12 2021-07-27
- 08.1: memory allocation strategies (2) (len=no. points in array, reserved=allocated memory for array; when are they different)
  - task 1-4
- 08.2: memory allocation strategies (3) how long it takes to append to array with these 3
  - Big O amortization

week 13 2021-08-03
- 10.1: C++ class -- in week 7?
- project presentation: if doing 125




Dynamic memory (maloc and free) (new and delete in C++)


week 14 2021-08-10
- lab quiz 4

- 


add problem pseudocode
every other week programing

canvas might be better for quizzes within 24hr

