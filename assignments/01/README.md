# Assignment 01: Introduction to C

Download the files for this assignment [here](./files.zip) (or from the [CMPT 127 D100/D200/D300 Canvas page](https://canvas.sfu.ca/courses/62984) > Assignments > 01).

**Remember**:
- Reference [lab 01](../../labs/01) for help!
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

**REQUIREMENT**: you will write a program to file `t1.c`.
- OUTPUT: `t1.c` should print `Hello World!`, `My name is <your name>.`, and `Nice to meet you!` in 3 separate lines to standard output.

**REMEMINDER**: 
- write comments!! Test and debug your code!
- Fix the error in code in `t1.c` by adding the missing exclamation point.
- Compile and run it, and verify that it now produces the correct output (expected result).
- Now your program meets the requirements and you are ready to submit it.

**TESTING**: you can test your program by running:
```
$ make t1
$ ./t1
```

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
$ make t2
$ ./t2
```

## Task 03

**REQUIREMENT**: you will write a program to file `t3.c`. 
- INPUT: `t2.c` should read any number of floating point values from standard input, separated by a space. 
     - Assume that the input is guaranteed to be well-formed and contain at least one valid floating point value.
     - If no floating point value can be parsed (i.e. a blank line was read) there should be no output. To put it another way: blank lines should be ignored.
- OUTPUT: After the user finishes inputting values, `t2.c` will print the product of all the inputs (hint: use the multiplication operator `*`).
     - The printed output should only have 2 decimal places.


**REMINDER**:
- write comments!! Test and debug your code!
- Your program should handle negative numbers (which are also valid integers).
- Prompt the user for what they should enter by printing messages with `printf`, e.g. `"Enter integers; after each integer, press enter: "`, and let the user know what the output is by printing a message, e.g. `"Here is the sum: "`.

**TESTING**: you can test your program by running:
```
$ make t3
$ ./t3
```

**Example**: sample input and output:
```
Provide floats separated by enter (line):
3.2
-1.6
9.5
0
The product of your values is: 0

```


## Task 04

**REQUIREMENT**: you will write a program to file `t4.c`. 
- INPUT: `t4.c` should read a user input line containing a positive integer value. This integer will be the width and height of a reversed right triangle. 
    - You can assume that the input is guaranteed to be well-formed, and all values will be in the range \[1,...,50\].
- OUTPUT: `t4.c` should, on standard output, draw the outline of the right triangle `#` character and fill the triangle using the `.` character.

**TESTING**: you can test your program by running:
```
$ make t4
$ ./t4
```

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

Upload `a.zip` onto to the appropriate assignment submission page on the [CMPT 127 D100/D200/D300 Canvas page](https://canvas.sfu.ca/courses/62984) > Assignments.

# Marking rubric


| Task | Criteria                                      | Points |
|------|-----------------------------------------------|--------|
| All  | The assigment is submitted in the appropriate format (i.e. the submitted files are named as specified and they are compressed into .zip format and uploaded onto canvas) | 1 |
|      | Programs are well documentated  (i.e. student name and program description at the top of program files) | 0.5 |
|      | Where applicable, program prompts user for input and indicates what the outputs are. | 0.5 |
| 01   | Program works as intended.                    | 1      |
| 02   | Program works as intended.                    | 2      |
| 03   | Program works as intended.                    | 2      |
| 04   | Program works as intended.                    | 2      |
|      | Program properly uses a for or while loop.    | 0.5    |
|      | Program properly uses an if/else conditions   | 0.5    |
| Total|                                               | 10     |