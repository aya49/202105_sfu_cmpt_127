# Assignment 01: Introduction to C

Open assignment 01 on [repl.it](https://replit.com/team/202105cmpt127) > Team Projects > 01_assignment

**Remember**:
- Reference [lab 01](../../labs/01) for help!
- Assignments are to be done individually.
- You may submit/resubmit the assignment on repl.it as many times as you want before the designated due date.
- The internet is your friend :) Search for documentation online and make sure to understand why things work the way they do!

**Contents**: for this assignment, you will complete the following tasks.
- [Task 01](#task-01)
- [Task 02](#task-02)
- [Task 03](#task-03)
- [Task 04](#task-04)

## Task 01

**REQUIREMENT**: Save your program to `t1.c` that writes `Hello World!`, `My name is <your name>.`, and `Nice to meat you!` in 3 separate lines to standard output.

**REMEMINDER**: 
- write comments!! Test and debug your code!
- Fix the error in code in `t1.c` by adding the missing exclamation point.
- Compile and run it, and verify that it now produces the correct output (expected result).
- Now your program meets the requirements and you are ready to submit it.


## Task 02

**REQUIREMENT**: Save your program in the file `t2.c`. Write a program to `scanf` two integer values from standard input separated by a space, then `printf` their sum.

**REMINDER**:
- write comments!! Test and debug your code!
- Your program should handle negative numbers (which are also valid integers).
- Prompt the user for what they should enter by printing messages with `printf`, e.g. `"Enter an integer: "`, and let the user know what the output is by printing a message, e.g. `"Here is the sum: "`.


## Task 03

**REQUIREMENT**: Save your program to the file `t3.c`. Write a program to read any number of floating point values from standard input, separated by a space. After the user finishes inputting values, your program will print the product of all the inputs (hint: use the multiplication operator `*`).
- Assume that the input is guaranteed to be well-formed and contain at least one valid floating point value.
- The printed output should only have 2 decimal places.
- If no floating point value can be parsed (i.e. a blank line was read) there should be no output. To put it another way: blank lines should be ignored.

**REMINDER**:
- write comments!! Test and debug your code!
- Your program should handle negative numbers (which are also valid integers).
- Prompt the user for what they should enter by printing messages with `printf`, e.g. `"Enter integers; after each integer, press enter: "`, and let the user know what the output is by printing a message, e.g. `"Here is the sum: "`.

**Example**: sample input and output:
```
Provide floats separated by enter (line):
3.2
-1.6
9.5
0
The product of your values are:

```


## Task 04

**REQUIREMENT**: Save your program to the file `t4.c`. Write a program to ead a user input line containing a positive integer value. This integer will be the width and height of a reversed right triangle. On standard output, draw the outline of the right triangle `#` character and fill the triangle using the `.` character.
- You can assume that the values are separated by one or more spaces, the input is guaranteed to be well-formed, and all values will be in the range \[1,...,50\].

**EXAMPLE**: sample user input `scanf` and `printf` output.

You'll need to use a fixed-width font in your terminal for these shapes to look right in your output. (If the examples below don't look symmetrical in your browser, check that your `pre` font is fixed-width.)

```
Enter an integer:
6
     #
    ##
   #.#
  #..#
 #...#
######

2
 #
##

1
#
```

**REMINDER**:
- write comments!! Test and debug your code!
- Prompt the user for what they should enter by printing messages with `printf`, e.g. `"Enter an integer: "`, and let the user know what the output is by printing a message, e.g. `"Here is the result: "`.