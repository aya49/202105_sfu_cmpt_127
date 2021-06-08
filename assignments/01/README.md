# Assignment 01: Introduction to C

Due: 2021-05-31 11:59pm.

Download the files for this assignment [here](./files.zip) (or from the [CMPT 127 D100/D200/D300 Canvas page](https://canvas.sfu.ca/courses/62984) > Assignments).

**REMEMBER**:
- Reference [lab 01](../../labs/01) for help!
- DO THE PRACTICE problems! They **directly** help you do the assignment tasks!
- Assignments are to be done individually.
- You may submit/resubmit the assignment as many times as you need before the designated due date (please don't do it too often though).
- The internet is your friend :) Search for documentation online and make sure to understand why things work the way they do!

**CONTENTS**: for this assignment, you will complete the following tasks.
- [Task 01](#task-01)
- [Task 02](#task-02)
- [Task 03](#task-03)
- [Task 04](#task-04)

Your assignment will be graded according to this [**marking rubric**](#marking-rubric).

## Task 01

**REQUIREMENT**: you will write a program to file `t1.c`.
- OUTPUT: `t1.c` should print `Hello World!`, `My name is <your name>.`, and `Nice to meet you!` in 3 separate lines to standard output.

**REMEMINDER**: 
- write comments!! Test and debug your code!
- Compile and run it, and verify that it now produces the correct output (expected result).
- Now your program meets the requirements and you are ready to submit it.

**TESTING**: you can test your program by running:
```
$ make t1 # OR gcc -Werror -Wfatal-errors -g -o t1 t1.c (see Makefile)
$ ./t1
```
(see? Makefiles saves your `gcc` command so you don't have to type this long thing over and over again, convenient huh :D)

## Task 02

**REQUIREMENT**: you will write a program to file `t2.c`. 
- INPUT: `t2.c` should `scanf` two integer values from standard input separated by a space, 
- OUTPUT: `t2.c` should `printf` the sum of these two integers.

**REMINDER**:
- write comments!! Test and debug your code!
- Your program should handle negative numbers (which are also valid integers).
- Prompt the user for what they should enter by printing messages with `printf`, e.g. `"Enter an integer: "`, and let the user know what the output is by printing a message, e.g. `"Here is the sum: "`.

**TESTING**: you can test your program by running:
```
$ make t2 # OR gcc -Werror -Wfatal-errors -g -o t2 t2.c (see Makefile)
$ ./t2
```
(see? Makefiles saves your `gcc` command so you don't have to type this long thing over and over again, convenient huh :D)

**EXAMPLE**: sample inputs and outputs:

```
Give me two integers: 2 5
Here is the sum of your two integers: 7
```

```
Give me two integers: 0 6
Here is the sum of your two integers: 6
```

## Task 03

**REQUIREMENT**: you will write a program to file `t3.c`. 
- INPUT: `t3.c` should read any number of floating point values from standard input, separated by a new line, and stop upon the user entering `0` (the program should discard the `0` and not use it in the output). 
     - Assume that the input is guaranteed to be well-formed and contain at least one valid floating point value.
     - If no floating point value can be parsed (i.e. a blank line was read) there should be no output. To put it another way: blank lines should be ignored.
- OUTPUT: After the user finishes inputting values, `t3.c` will print the product of all the inputs (hint: use the multiplication operator `*`).
     - The printed output should only have 2 decimal places.


**REMINDER**:
- write comments!! Test and debug your code!
- Your program should handle negative numbers.
- Prompt the user for what they should enter by printing messages with `printf`, e.g. `"Enter numbers separated by an enter: "`, and let the user know what the output is by printing a message, e.g. `"Here is the product: "`.

**TESTING**: you can test your program by running:
```
$ make t3 # OR gcc -Werror -Wfatal-errors -g -o t3 t3.c (see Makefile)
$ ./t3
```
(see? Makefiles saves your `gcc` command so you don't have to type this long thing over and over again, convenient huh :D)

**Example**: sample input and output:
```
Provide floats separated by a line: 
3.2 
-1.6 
9.5 
0
The product of your values is: -48.64 

```


## Task 04

**REQUIREMENT**: you will write a program to file `t4.c`. 
- INPUT: `t4.c` should read a user input line containing a positive integer value. This integer will be the width and height of a reversed right triangle. 
    - You can assume that the input is guaranteed to be well-formed, and all values will be in the range \[1,...,50\].
- OUTPUT: `t4.c` should, on standard output, draw the outline of the right triangle `#` character and fill the triangle using the `.` character.

**TESTING**: you can test your program by running:
```
$ make t4 # OR gcc -o -Werror -Wfatal-errors -g t4 t4.c (see Makefile)
$ ./t4
```
(see? Makefiles saves your `gcc` command so you don't have to type this long thing over and over again, convenient huh :D)

**EXAMPLE**: sample user input `scanf` and `printf` output.

You'll need to use a fixed-width font in your terminal for these shapes to look right in your output. (If the examples below don't look symmetrical in your browser, check that your `pre` font is fixed-width.)

```
Enter an integer:
6
Here's your result:
     #
    ##
   #.#
  #..#
 #...#
######
```
```
Enter an integer:
2
Here's your result:
 #
##
```
```
Enter an integer:
1
Here's your result:
#
```

**REMINDER**:
- write comments!! Test and debug your code!
- Prompt the user for what they should enter by printing messages with `printf`, e.g. `"Enter an integer: "`, and let the user know what the output is by printing a message, e.g. `"Here's your result: "`.

# Make sure your code is readable!

Please make sure you follow good coding habits while you are coding:
- indents: use consistent indenting conventions e.g. if you decide to use 2 spaces for an indent, do that across all your tasks.
- readable variable names: the name of a variable explains why you made it if it is not obvious already (likely not ;). You can also add a comment explaining what it is!
- comments at the top + inline: comments at the top is the block I give you to fill in your name, date, etc. Comments inline are comments explaining what your code does, e.g.

```C
// author: alice yue; aya43; 301196607
// date:2021/5/29
// input: void (from main (<<void>>))
// output: int (from <<int>> main (void))
// description: prints the product of multiple 
//     user given integers to standard output.

#include <stdio.h>

int main(void) {
    // declare a variable to hold user input
    float i; 
  
    // declare a variable to hold the product
    float prod;

    // ask and scan for a user input
    printf("Provide floats separated by a line:\n");
    scanf("%f", &a);

    // while the user input is not 0, calculate a cumulative product
    while (a!=0) {
        prod = prod*a;
        scanf("%f", &a);
    }

    // print the product to standard output
    printf("The product of your values is %0.2f\n", product);
    
    return 0;
}
```

# Submission

Make sure you have the following files ready for submission and that they are named appropriately, otherwise they won't be graded.
- Task 01: `t1.c`
- Task 02: `t2.c`
- Task 03: `t3.c`
- Task 04: `t4.c`

Compress these files into a zip file called `a.zip`; you can do this by using the following command from console:
```
$ make submit
```

i.e. you should have ONE file called `a.zip` containing the files listed above (you can open your `a.zip` file to verify you have the correct files in it).

Upload `a.zip` onto to the appropriate assignment submission page on the [CMPT 127 D100/D200/D300 Canvas page](https://canvas.sfu.ca/courses/62984) > Assignments.

# Marking rubric


| Task | Criteria                                      | Points |
|------|-----------------------------------------------|--------|
| All  | The assigment is submitted in the appropriate format (i.e. the submitted files are named as specified and they are compressed into .zip format and uploaded onto canvas). | 1 |
|      | Source code is readable (i.e. student name and program description at the top of program files, variable names are self-descriptive and consistent, comments describing what code does is available where appropriate, indentatations are consistent). | 0.5 |
|      | Where applicable, program prompts user for input and indicates what the outputs are. | 0.5 |
| 01   | Program works as intended.                    | 1      |
| 02   | Program works as intended.                    | 2      |
| 03   | Program works as intended.                    | 2      |
| 04   | Program works as intended.                    | 2      |
|      | Program properly uses a for or while loop.    | 0.5    |
|      | Program properly uses an if/else conditions.  | 0.5    |
| Total|                                               | 10     |