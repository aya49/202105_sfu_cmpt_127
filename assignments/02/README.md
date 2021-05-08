# Assignment 02: Functions, Arrays, C character strings, arguments to main, and header files

Open assignment 02 on [repl.it](https://replit.com/team/202105cmpt127) > Team Projects > 02_assignment

(if repl.it doesn't work, download files [here](./files), and upload your files in a zip file to Canvas)

**Remember**:
- Reference [lab 02](../../labs/02) for help!
- DO THE PRACTICE problems! They **directly** help you do the assignment tasks!
- Assignments are to be done individually.
- You may submit/resubmit the assignment on repl.it as many times as you want before the designated due date.
- The internet is your friend :) Search for documentation online and make sure to understand why things work the way they do!

**Contents**: for this assignment, you will complete the following tasks.
- [Task 01](#task-01)
- [Task 02](#task-02)
- [Task 03](#task-03)
- [Task 04](#task-04)

Your assignment will be graded according to this [**marking rubric**](#marking-rubric).

## Task 01

**REQUIREMENT**: Create a file called `t1funcs.h` that contain function declarations for all the functions in `p1funcs.c`.
- Edit the file `t1.c` to `#include` the new header file.
- The finished code must compile with this command with no errors or warnings:
```
$ gcc t1.c p1funcs.c -o t1.o -Wall
$ ./t1.o
The product of our numbers is 12.
The quotient of our numbers is 3.
```

**REMEMBER**: header files contain function declarations, these are the same as a function definition except the braces and everything in the braces are replaced by a `;`.


## Task 02

**REQUIREMENT**: Create a new file called `t2mirror.c`, containing a single function `mirror` with the following function declaration:
```C
int mirror(int arr1[], int arr2[], unsigned int len);
```
- INPUT: The `mirror` function has the following declaration:
    - Arrays `arr1` and `arr2` are both of length `len`, and contain arbitrary integer values.
    - `len` can have any unsigned int value, including 0.
    - If `len` is 0 then `mirror()` should return 1 (since the arrays have the same - empty - contents).
    - You must not change the contents of the arrays.
- OUTPUT: `mirror` should return 1 iff arrays `arr1` and `arr2` contain the same values in the reverse order, or 0 otherwise. 

**EXAMPLE**

Examples of arrays for which `mirror` should return 1:

```C
arr1 = {10,15,20}, arr2 = {20,15,10}
arr1 = {100}, arr2 = {100}
arr1 = {5,2,2,3,4,5,5}, arr2 = {5,5,4,3,2,2,5}
arr1 = {}, arr2 = {} (i.e. len = 0)
```

Examples of arrays for which `mirror` should return 0:

```C
arr1 = {1,1}, arr2 = {1,2}
arr1 = {10,15,20}, arr2 = {10,15,20}
arr1 = {1,2,3,4,5}, arr2 = {5,3,4,1,2}
arr1 = {1,2,3,4,5}, arr2 = {5,3,4,2,2}
```

File: `t2.c` is an example of a program that uses your function:

```C
#include <stdio.h>
// FILL IN HERE: include header for t2mirror.c

int main(void) {
    int a1[3] = {10, 15, 20};
    int a2[3] = {10, 20, 15};

    if (mirror(a1, a2, 3) == 1) { 
        printf("a1 and a2 are mirrored\n");
    } else {
        printf("a1 and a2 are NOT mirrored\n");
    }

    return 0;
}
```


## Task 03

**REQUIREMENT**: Write a C program called `t3.c`.
- INPUT: `t3.c` takes two text strings as arguments.
    - You can assume your strings are of length at least 1.
- OUTPUT: `t3.c` prints "true" followed by a newline if the second string is entirely **in the same order but not necessarily continuously** contained within the first, or "false" followed by a newline otherwise.

Recall that 
- you can name your executable file with `-o` e.g. `gcc t3.c -o t3.o` and run it by `./t3.o`.
- in lab 02 practice 03, you made a similar program, take caution not to confuse the requirements of the practice problem and this task!

**EXAMPLE**

Example runs:

```
$ ./p3.o "I have a really bad feeling about this" "had fling"
true
$ ./p3.o "To be or not to be" "to not be"
true
$ ./p3.o "To be or not to be" "be to not"
true
$ ./p3.o "I am the walrus" "I am the walrus"
true
$ ./p3.o "the walrus" "I am the walrus"
false
$ ./p3.o "kmjnhbvc45&^$bn" "."
false
```


## Task 04

**REQUIREMENT**: Write a C program called `t4.c`.
- INPUT: `t4.c` takes two program arguments of type C string: `str1` and `str2`. The program would also read from stdin, a text file. 
    - Every byte read from stdin counts as a character.
    - Words are defined as contiguous sequences of letters (a through z, A through Z) and the apostrophe (', value 39 decimal) separated by any character outside these ranges.
    - You can assume your strings are of length at least 1.
- OUTPUT: `t4.c` should output to console, the number of times the `str1` and `str2` occurs in the text document (continuously, like in practice 03) in two separate lines.

Recall escape characters --- may be helpful ;)

Your program should work as follows:
```
$ ./t4.o as to < t4prince.txt
```

**EXAMPLE**

Example outputs include:

```
$ ./t4.o r in < p4beatles.txt
r : 2
in : 1

$ ./t4.o go ge < p4beatles.txt
go : 1
ge : 2
```


# Marking rubric

| Task | Criteria                                      | Points |
|------|-----------------------------------------------|--------|
| All  | Programs are well documentated  (i.e. student name and program description at the top of program files, commented on important code sections) | 0.5    |
| All  | Programs are coded with good coding styles (i.e. no extra code after final return statement in functions, variables initiated are used, arrays are properly passed etc.). | 0.5    |
| 01   | Program works as intended.                    | 1      |
| 02   | Program works as intended.                    | 1      |
| 03   | Program works as intended.                    | 1      |
| 03   | Program properly uses while or for loops      | 0.5    |
| 04   | Program works as intended.                    | 1      |
| 04   | Program properly uses an if/else conditions.  | 0.5    |
| Total|                                               | 6      |