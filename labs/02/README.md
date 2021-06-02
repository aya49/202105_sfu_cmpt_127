# Lab 02: functions, arrays, C character strings, arguments to main, and header files

Download lab files [here](./files.zip).

Review "Guide"s and accompanying slides (we will go over these during the lab lecture).
- [Guide 01](#guide) ([slides](https://docs.google.com/presentation/d/1e5x62e1PLZV4hSXGmtKIsqWdjSpwY1aWi8lX-5QL4AI/edit?usp=sharing)): Function definitions, declarations, and header files
- [Guide 02](#guide-1) ([slides](https://docs.google.com/presentation/d/1myUYQWCfbC6jIHIoT9gjfbKLfEuthosidxkpz3ajc74/edit?usp=sharing)): Arrays
- [Guide 03](#guide-2); [Guide 04](#guide-3) ([slides](https://docs.google.com/presentation/d/1hxiZTsV0BkjZplmKtpoH7uvxjHwy7ufDymR-hCQUyyc/edit?usp=sharing)): Program arguments and C strings; stream redirection


Try "Practice" problems; these will NOT be graded. Note that the solutions given for Practices is just one of many possible solutions, better ones may exist.
- [Practice 01](#practice-01)
- [Practice 02](#practice-021)
- [Practice 03](#practice-03)
- [Practice 04.1](#practice-041)
- [Practice 04.2](#practice-042)

Do [Assignment 02](../../assignments/02).

Note: from here on, the guide section will often include links to other material that can be crucial to solving the task. You should practice consulting online references and tutorials: this is a significant part of real-world programming. To encourage you to practice, we use external links instead of writing everything out in the guide. To be absolutely clear: **not everything you need to know is contained in our instructions. Therefore, you need to read about the new material discussed in the labs (e.g., C library functions, etc...) using the links and maybe searching online. This is deliberate and great practice!**

Always remember, the internet is your friend :) Search for documentation online and make sure to understand why things work the way they do!


# Function definitions, declarations, and header files

## Guide

**Functions** (not to be confused with functions in mathematics): C is a [structured, procedural programming language](http://en.wikipedia.org/wiki/Procedural_programming_language). This means that C supports functions: isolated, self-contained blocks of code that can be re-used as components of larger programs. Other languages may call functions **procedures, subroutines**, or **methods**.

**Encapsulation** is a trait of well-designed functions where you can often use it for what it does, and ignore the internal details of how it works. This makes it feasible for humans to write complex programs by breaking them down into small, more manageable pieces.

**Functions in a nutshell**:
- You **pass** 0+ arguments into a function, 
- the function creates a **copy** of your arguments (this is IMPORTANT! IT'S NOT USING THE ORIGINAL COPY!), 
- does something with the copy of your arguments (encapsulation), 
- then the function returns 0 (`void`) or 1 thing to you.

You have already used several functions provided by the standard library, such as `printf`, without seeing how they were implemented.

### Function syntax

```C
type functionName(type arg_name1 <, type arg_name2, ...>) {
    // code-block function body enclosed by curly braces
}
```

Let's look at an example implementation of the function.

File: `p1funcs.c`
```C
// returns the larger of the two arguments
int max(int int1, int int2) {

    // let's assume int2 is the larger integer
    int larger = int2;
    
    // if int2 isn't the larger integer, then int1 is the larger integer
    if (int1 > int2) {
        larger = int1;
    }
    return larger;
}
```

File: `p1.c`
```C
int main(void) {
    int num1 = 11;
    int num2 = 12;

    // use max to test which integer is larger
    printf("The max of our numbers is %d\n", max(num1, num2));
    return 0;
}
```

Let's read our `max` function top-to-bottom, left-to-right: `int max(int int1, int int2)`:
- `int` is the **return value** of running this function is of type `int`. If the return type is `void`, we can omit the `return` statement, The function will finish at the end of the code block and return nothing.
- `max` is the name of the function.
- arguments `int1` and `int2` are what the function takes as input; in this case, the input is two integer arguments called `int1` and `int2`; function definitions can specify an **arbitrary number of arguments**.
- The **body** of the function, i.e. the code that will execute when the function is called, is written between `{...}`.
- `return` ..., or the value of the expression to the right of keyword `return` is the function's **return value**, or what the function outputs. Functions can only have **one return value**.

In `int main(void)`,
- Calling a function: the function `max` is **called** (like this: `max(num1, num2)`) in `printf`.
    - Input: the values of integers `num1` and `num2` are assigned to `int1` and `int2` inside `max()`.
    - Output: `max` does its work and the return value is passed as the second argument to `printf()`.

Other important notes on functions:
- In general a function may call any including itself (e.g. `max` is called inside `main()`, both are functions).
- A function can only be called below its definition because the compiler reads the source file from top to bottom, it doesn't know what it hasn't seen!

**Header files**

When you start writing lots of functions, it is good practice to break up your code into multiple source files.

For example, in your working directory you have the source files `p1funcs.c`, containing useful function definitions, and `p1.c`, containing your `main()` program. To use all of these files together, you would have to give your compiler multiple source files. 

As it is now, the compiler will attempt to compile all files into one program... which is not great; you will get warnings and possibly errors complaining that in `p1.c`, `min()` and `max()` are not properly declared. Try it:

```
$ gcc p1funcs.c p1.c -o p1.o -Wall
```

(the `-Wall` compiler option enables "all warnings" i.e. the compiler will warn you about potential problems; options like `-Wall` are added automatically in your Makefile!)

For this to work, you will need to do the following:

1. Write a header file for `p1funcs.c`, called `p1funcs.h`.
    - **Header files** are files that contain the function declarations of your the functions you defined in the separate file(s).
    - A **function declaration** tells the compiler the name of the function, its arguments and return type by writing a function declaration. A function declaration is the same as its definition, but with the function body replaced by a semicolon. For example:
```C
int max(int int1, int int2);
```
2. `#include` a copy of the the contents of the source file into your program `p1.c`. The contents of these source files are linked to your program at the last step of compilation.
    - `<>`: specifying the name of the header file `<like this>` forces the compiler to look for the file in the directories where your compiler was installed; the impelmentations of the functions in these files are implementations of these functions were pre-compiled for you into code to save your time.
        - These functions were pre-compiled for you into code **libraries** and shipped with your compiler to save you time. The required libraries are **linked** into your program at the last step of compilation. 
        - The library `<stdio.h>` containing `printf()` is used so often it is linked by default (so you actually didn't need to add the line `#include <stdio.h>`).
    - `""`: specifying the name of the header file `"like this"` copies the contents of a file you wrote. This quoted version understands paths relative to the current directory, and absolute paths (paths starting from root):

Examples of `#include` statements:

```C
#include <stdio.h> // a system-supplied header
#include <math.h> // a system-supplied header that contains functions like floor(), ceiling(), round()
#include "p1funcs.h" // a header file I wrote myself

// #include "p1funcs.h" // p1funcs.h is in the current directory
// #include "include/p1funcs.h" // p1funcs.h is in a subdirectory called `include`
// #include "../p1funcs.h" // p1funcs.h is in the parent directory
// #include "/opt/local/include/p1funcs.h" // an absolute path
// (etc)
```

In addition to functions, header files can also declare global variables or provide important constant values, such as `M_PI` or the value of pi specified in `<math.h>`.

**Summary**

- **Functions**: encapsulate a piece of code (e.g. `int max(int int1, int int2) {...}`).
- If you have lots of functions, it's good practice to put your functions into separate files (e.g. `p1funcs.c`). To use these files together with your program (e.g. `p1.c`), you need to:
    1. Create **header files** associated with your function files; header files have the `.h` file extension (e.g. `p1funcs.h`). In your header files, put in the **function declarations** for the functions in the associated function files (e.g. `int max(int int1, int int2);`).
    2. `#include` your header file in your program (e.g. `#include "p1funcs.h"`).



## Practice 01

**REQUIREMENT**: you will
- create a file called `p1funcs.h` that contain function declarations for all the functions in `p1funcs.c`.
- edit the file `p1.c` to `#include` the new header file.

**TESTING**: the finished code must compile with this command with no errors or warnings:
```
$ make p1
$ ./p1
The max of our numbers is 12.
The min of our numbers is 11.
```

**REMEMBER**: header files contain function declarations, these are the same as a function definition except the braces and everything in the braces are replaced by a `;`.

<details>
<summary style="margin-left: 25px;">Try it yourself first; then verify your solutions here.</summary>
<div style="margin-left: 25px;">

File: `p1funcs.h`
```C
int max(int int1, int int2);
int min(int int1, int int2);
```

Add the following line to the top of file: `p1.c`
```C
#include "p1funcs.h"
```

</div>
</details>


# Arrays

## Guide

There are 3 things that define an array: 
1. a **data type** of the value of the values inside the array, and 
2. a **variable name** == **pointer** or an address indicating where in memory the array's first element is stored, and
4. the **elements** == **values** stored inside the array.

In C, we can create variables that hold a single value or an **array** of values of the same type.

Let's initialize some arrays:
```C
char c; // a single character
char c_array[100]; // an array of 100 characters

int i; // a single integer
int i_array[100]; // an array of 100 integers
int i_array3[3] = {10, 15, 20}; // you can also initialize an array with values! {} are only ever used in association with arrays in this case
```

Array elements are accessed by index, starting from 0:
```C
i_array[0] = 99; // set the first element of i_array to 99
int i1 = i_array[0]
```

Be careful not to access something not in the array:
```C
int i2 = i_array[100]; // ERROR! the 101st element doesn't exist in a 100-element array
```

**Cons** of C arrays (compared to vectors in C++):
1. All elements of the array must be of the same type;
2. The length of an array is fixed at creation time;
3. The value of array elements is not initialized;
4. Access to elements is not bounds checked (i.e. lookups are not checked to make sure (0 <= index < array size)).
5. Therefore C arrays must be used carefully.

**Pros** of C arrays: they are **very very fast**! Arrays have an incredibly simple and efficient design. There is a trivial overhead in accessing data from an array; there is also very little cost to creating arrays. For these reasons C programmers use arrays a lot despite the limitations.

Array vs memory:
- In memory: arrays are allocated as contiguous chunk of memory, of size `array-length * sizeof(type)` bytes.
- Like variable, the memory allocated to the array is automatically freed when the array variable goes out of scope i.e. if you initialize an array in a function, after exiting the function, your array will be automatically freed from memory.
- **IMPORTANT**: The variable of an array does **NOT** have a separate pointer, the variable name itself is passed as a pointer that points to the first byte of the first element in the array so the following are true:

```C
int i_array[100];

// the pointer (&) of the 1st element in the array (i_array[0]) 
// IS the name of the variable (i_array)
&i_array[0] == i_array;

// the value (*) stored in the place in memory the 1st element in the array + 5 (i_array+5) points to
// IS the value of the 6th element in the array
*(i_array+5) == i_array[5];
*(5+i_array) == i_array[5];

// the pointer pointing to the first element in the array + 5 (i_array+5)
// IS the pointer (&) of the 6th element in the array (i_array[5]) 
(5+i_array) == &i_array[5];
```

### Passing pointers/arrays to functions

Since array variables can be used like pointers, you can pass them into functions as pointers. Let's look at two identical functions `array_max_brackets` and `array_max_ptr`.

```C
#include <stdlib.h>
#include <stdio.h>

// note: data type `unsigned int` is like int, but unsigned; because negative-length arrays can not exist

// PREFERED WAY
// return the largest int in the array
// `[]` says: "this argument is an array!"; 
// arr[] is an unsized array; specifying the size is optional but more restrictive e.g. arr[10]
int array_max_brackets(int arr[], unsigned int len) { 
    int max = arr[0];
    for (unsigned int i = 1; i < len; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// return the largest int in the array
// `*` says: "this argument is a pointer!"; recall, functions take in "values" by defaults, *<pointer> = value.
int array_max_ptr(int* arr, unsigned int len) { 
    int max = arr[0];
    for (unsigned int i=1; i<len; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

const unsigned int sz = 10; // adding `const` makes the variable read-only

int main(void) {
    int arr[sz];

    for (unsigned int i=0; i<sz; i++) {
        arr[i] = random();
        printf("arr[%u] == %d\n", i, arr[i]);
    }

    printf("Largest was\n %d\n %d\n",
    array_max_ptr(arr, sz),
    array_max_brackets(arr, sz));

    return 0;
}
```

Some notes:
- The two versions of the `array_max` function passes a pointer and the name of the array respectively. To the compiler, these are the same because the name of your array is passed as a pointer.
- You should almost always use the array-bracket syntax version (`int arr[]`) since it tells the human reader that an array is expected.
- We had to pass the length of the array into both versions. C arrays do not know how long they are.

### Passing pointers/arrays to functions vs passing variables to functions

**Pointer vs value**: passing a pointer/array is essentially different from passing a variable (by default, the variable value) to a function.
- **Value**: If you pass a variable (and hence it's value), you make a COPY of the value inside your function, so your function CANNOT MODIFY your original variable value.
- **Pointer**: if you pass a pointer (which is the case for arrays), you make a COPY of the pointer (address) to the SAME value, so your function CAN MODIFY your original values (i.e. array).

Knowing this, if your functions' intent is to modify your array, your function does not need to give a return value, because it will access and modifying the same array via the pointer you passed to it. Let's take a look at the `reverse` function below, a function that reverses the order of your array (e.g. `{0,2,6,3}` > `{3,6,2,0}`).

```C
#include <stdio.h>

// a function that reverses the elements in arr;
// note that it has no return
void reverse(int arr[], unsigned int len) {
    for (int i = 0, j = len-1; i < len/2; i++, j--) {
        int tmp = 0;
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

int main(void) {
    int i_array[] = {11, 12, 13}; // initialize i_array
    unsigned int len = 3;

    reverse(i_array, len); // copy the pointer, modify the same i_array

    for(unsigned int i=0; i<len; i++) {
         printf("%d ", i_array[i]); // print the modified i_array
    }
    printf("\n");

    return 0;
}
```

Note that your array values do not go out of scope (is not removed) once you finish executing the function, the pointer that the function created a copy of does.


## Practice 02.1

**REQUIREMENT**: you will write to file `p2identical.c`, a single function `identical()` with the following declaration:

```C
int identical(int arr1[], int arr2[], unsigned int len);
```

- INPUT: `identical` takes as input, two `int` arrays `arr1` and `arr2`, and `len`.
    - Arrays `arr1` and `arr2` are both of length `len`, and contain arbitrary integer values.
    - `len` can have any unsigned int value, including 0.
- OUTPUT: `identical` returns 1 iff arrays `arr1` and `arr2` contain the same values in the same order, or 0 otherwise.
    - If `len` is 0 then `identical()` should return 1 (since the arrays have the same - empty - contents).
    - You must not change the contents of the arrays.

**TESTING**: you can test your program by running:
```
$ make p2
$ ./p2
```

**EXAMPLE**

Examples of arrays for which `identical` should return 1:

```C
arr1 = {10,15,20}, arr2 = {10,15,20}
arr1 = {100}, arr2 = {100}
arr1 = {5,2,2,3,4,5,5}, arr2 = {5,2,2,3,4,5,5}
arr1 = {}, arr2 = {} (i.e. len = 0)
```

Examples of arrays for which `identical` should return 0:

```C
arr1 = {1,1}, arr2 = {1,2}
arr1 = {10,15,20}, arr2 = {10,15,21}
arr1 = {1,2,3,4,5}, arr2 = {5,3,4,2,2}
```

File: `p2.c` is an example of a program that uses your function:

```C
#include <stdio.h>
#include "p2identical.h"

int main(void) {
    int a1[3] = {10, 15, 20};
    int a2[3] = {10, 20, 15};

    if (identical(a1, a2, 3) == 1) { 
        printf("a1 and a2 are identical\n");
    } else {
        printf("a1 and a2 are NOT identical\n");
    }

    return 0;
}
```

Try it yourself first; then verify your solutions [here](./files/solution/p2identical.c)

## Practice 02.2: challenge yourself!

**REQUIREMENT**: can you modify your `identical` function such that it returns `1` if the contents of the two arrays are exactly the same regardless of the order? Define another function called `scrambled` in your `p2identical.c` file. Add `scrambled`'s declaration into the `p2identical.h` file, and add a line in in your program `p1.c` that calls your `scrambled` function.

**HINT**:
- You can assume that the values in `arr1` and `arr2` are between `0` and `100`.
- You can initialize a length `101` array where the value of all of its elements are initialized to zero:

```C
int arr[101] = {0};
```

**TESTING**: you can test your program by running:
```
$ make p2
$ ./p2
```

**EXAMPLE**

Examples of arrays for which scrambled should return 1:
```C
arr1 = {10,15,20}, arr2 = {10,15,20}
arr1 = {99}, arr2 = {99}
arr1 = {1,2,3,4,5}, arr2 = {5,3,4,2,1}
arr1 = {}, arr2 = {} // (i.e. len = 0)
arr1 = {2,1,3,4,5}, arr2 = {1,2,4,3,5}
```

Examples of arrays for which scrambled should return 0:
```C
arr1 = {1,1}, arr2 = {1,2}
arr1 = {10,15,20}, arr2 = {10,15,21}
arr1 = {1,2,3,4,5}, arr2 = {5,3,4,2,2}
```

Try it yourself first; then verify your solutions [here](./files/solution/p2identical.c).


# Program arguments and C strings

## Guide

So far you have written programs that read their input from stdin using `scanf`. Another way to get data into a program is with program arguments. For example when we compile our progrmas, we use:

```
$ gcc main.c
```

`gcc` is not using stdin, so how does it know the files to compile? Well we give it the file `main.c` as a program argument. 

**Program arguments** are special arguments that are passed to a special function in your program, `main()`. Your program must have a single main function.
- `main` can be declared like this if it needs no arguments `void` from the outside world:
```C
int main(void) {...}
```
- `main` can be declared like this if it does need arguments from the outside world:

```C
int main(int argc, char* argv[]) {...}
```

These two arguments, `argc` and `argv`, work for all possible arguments to your program and it works by using arrays and pointers. The arguments are interpreted as follows:
- `int argc` is the number of arguments passed into `main`, plus one (e.g. for `gcc main.c`, this is 2).
- `char* argv[]` is an array of char pointers. The `argv` array is `argc` pointers long. 
    - The 0th entry in `argv` is always the program's own name (e.g. `gcc`). The subsequent entries are the program arguments in order. For our cp example the contents of the array are:
```
argv[0] : "gcc"
argv[1] : "main.c"
```
**C string**: a string in C is just a character array containing a special NULL character (a null terminator: '\0' or value 0) to mark the end of its text. Each pointer in the `argv` array points to the first character in a character array: `argv` is an array of arrays!

We can sketch an implementation of `gcc` like this:

```C
int main(int argc, char* argv[]) {
    int filename = open(argv[1], O_RDONLY); // open the file for read only
    int outputfile = open("a.out", O_RW | O_CREAT); // create a new executable file for writing

    while (...) { // we haven't read everything from inputfile
        ... // read bytes from inputfile, translate to executable, and write them to outputfile
    }
    return 0; // success!
}
```


### I want numbers, not text C strings

Since main's arguments are stored as character strings, another step is needed to convert strings that represent numbers into number types before you use them. The `atoi()` and `atof()` functions provided in the standard library convert strings to integers and floating point values respectively:

```C
#include <stdlib.h> // for atoi() and friends

// takes two arguments: an integer followed by a float
int main(int argc, char* argv[]) {
    if (argc != 3) { // argv[0] is the program name
        printf("I wanted 2 arguments\n");
    }

    int i_int = atoi(argv[1]); // converts a string into an "i" integer
    float j_float = atof(argv[2]); // converts a string into a "f" float
    // ...
}
```

The program can be run like so and work as expected (we use `a.out` as the program name):

```
$ ./a.out 5 3.14
```

## Practice 03

For this practice, we'll go over how to implement a "substring" function in C.

**REQUIREMENT**: you will write a program to file `p3.c`.
- INPUT: `p3.c` takes two text strings as program arguments.
    - You can assume the two strings contain at least one character.
- OUTPUT: prints "true" followed by a newline if the second string is entirely contained within the first, or "false" followed by a newline otherwise.

Recall that you can name your executable file with `-o` e.g. `gcc p3.c -o p3.o` and run it by `./p3.o`.

This is an [important problem in computer science](http://en.wikipedia.org/wiki/Substring), with wide applications from searching the internet, to understanding text, to finding DNA matches. It's easy to state and easy to code. It gets interesting when the strings are long and you want to do it very efficiently. For now you can be happy with a simple solution to practice managing `argv` array and char strings.

**HINT**: you can find useful string functions like `strlen()` (length of a C string) in the header you included, `#include <stdio.h>`, by looking up its [manual/documentation](https://www.tutorialspoint.com/c_standard_library/stdio_h.htm) online!

**TESTING**: you can test your program by running:
```
$ make p3
$ ./p3
```

**EXAMPLE**

Example runs:

```
$ ./p3 "I have a really bad feeling about this" "bad feeling"
true
$ ./p3 "To be or not to be" "That is the question"
false
$ ./p3 "I am the walrus" "I am the walrus"
true
$ ./p3 "the walrus" "I am the walrus"
false
$ ./p3 "kmjnhbvc45&^$bn" "."
false
```

Notice that the strings do not have quote characters around them when delivered to your program via `argv`. The quotes prevent the shell from breaking the strings up into individual words.


<details>
<summary style="margin-left: 25px;">Try it yourself first; then verify your solutions here.</summary>
<div style="margin-left: 25px;">

Click [here](./files/solution/p3.c) for the solution code.

Note: `#include <string.h>` contains function `strstr()` that solves the substring problem. The algorithm implemented in `strstr()` is not the most efficient, there are algorithms with better asymptotic runtimes; can you find more efficient implementations of a solution to the substring problem? 

You will learn the terms **algorithm** and **asymptotic runtime** in CMPT 125, come back to this after you've mastered them and read the note again ;)

Response to note: Theoretically there are more efficient implementations, but usually, if a function already exists, we would use it, unless someone makes a better one. 

</div>
</details>

# Stream redirection: redirecting stdin and stdout (`scanf` and `printf`)

## Guide

You will find it tedious to type lots of text into your program's stdin. The shell has a powerful tool to help with this: **stream redirection**. 

**stream redirection** allows you to route the stdin and stdout for a program away from the console and into a file. 

**stream redirection**; stdout: If we have a program called `p4hello` that prints "Hello world!\n" on stdout, we can redirect this output to `p4.txt`:

```
$ gcc p4hello.c -o p4hello
$ ./p4hello > p4.txt
```

To confirm this, inspect the contents of the file with `cat`:

```
$ cat p4.txt
Hello world!
```

**stream redirection**; stdin: Similarly, we can take the contents of a file, and stream it into the standard input of our program. So if we have a program `sort` that reads lines from stdin, sorts them into lexical order then writes them on stdout, we can do this:

Contents of file `p4beatles.txt`:

```
john
paul
george
ringo
```

```
$ ./sort < p4beatles.txt
george
john
paul
ringo
```

**stream redirection**; stdin and stdout: Input and output redirection can be used together:

```
$ ./sort < p4beatles.txt > sorted.txt
$ cat sorted.txt
george
john
paul
ringo
```

This is a very powerful mechanism that is great for testing with lots of different inputs. It's much more convenient to redirect a file into stdin than to type many lines followed by `ctrl-d` over and over. Make sure you understand file redirection!

Here is a terse but good introduction to [BASH shell programming](http://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO.html), including a section on [redirection](http://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO-3.html).


## Practice 04.1

**REQUIREMENT**: add comments on file `p4.1.c` explaining what each line(s) is doing; do you understand the rationale behind these lines?

Here is a program that would have been very tedious to run without stream redirection. `p4.1.c` counts the number of characters, words and lines read from standard input until `ctrl-d` (`EOF`, if interested, see extra materials in [lab 01](../01/README.md#EOF-the-end-of-the-file)).
- Every byte read from stdin counts as a character.
- Words are defined as contiguous sequences of letters (a through z, A through Z) and the apostrophe (', value 39 decimal) separated by any character outside these ranges.
- Lines are defined as contiguous sequences of characters separated by newline characters ('\n').
- Characters beyond the final newline character will not be included in the line count.

There are new functions `getchar()` and `isalpha()` here which we haven't seen before. Check it out online or read its manual. There's a handy standard program called `wc` that does a similar job as `getchar()`, but it does not match the requirements exactly (it is a little more clever about word boundaries and will sometimes count fewer words than our simple program).

**Escape characters**: This [Q&A on StackOverflow](http://stackoverflow.com/questions/2414478/c-escaping-an-apostrophe-in-a-string) gives advice on representing the apostrophe character using an **escape sequence**. StackOverflow is very useful indeed.

```C
#include <stdio.h> // getchar, EOF constant
#include <ctype.h> // isalpha

// main() is the same as main(int argc, char* argv[])
// main(int argc, char* argv[]) is used so much that it was made the default!
int main() {
    // unsigned long int is a data type, search it up!
    unsigned long int charcount = 0;
    unsigned long int wordcount = 0; 
    unsigned long int linecount = 0;
    unsigned long int space = 0;

    // COMMENT HERE
    char last = getchar(); // getchar reads a character from stream, kind of like scanf
    
    // while not the end of file / ctrl-d
    while (last != EOF) { 
        // COMMENT HERE
        charcount++;

        // COMMENT HERE
        char current = getchar();

        // COMMENT HERE
        if (!isalpha(last) && isalpha(current)) { 
            wordcount++;
        }

        // COMMENT HERE
        if (current == '\n') {
            linecount++;
        }
        last = current;
    }
    printf("%lu %lu %lu\n", charcount, wordcount, linecount);

    return 0;
}
```

Solution? I'm sure you can do this one on your own ( \*u\*)b

DID YOU KNOW: there will be times when you need to store words you read in as C strings (perhaps in your assignment). Here is a piece of code that allows you to do that, do you understand what it is doing?

```C
int i = 0;
char* str[100];
char c;
while ((c = getchar()) c != EOF ) {
    if (i < nchars) {
        str[i++] = c;
    }
}
str[i] = '\0';
```

## Practice 04.2

**REQUIREMENT**: you will write a program to file `p4.2.c`. 
- INPUT: `p4.2.c` should read ASCII text from stdin.
- BEHAVIOUR: `p4.2.c` will count the occurence frequency of each letter in the input.
    - Letters that occur zero times should not appear in the output.
    - Characters other than lower and upper case letters should be ignored.
    - Lower and upper case instances count as the same letter, e.g. 'a' and 'A' are both reported for the letter 'a' on the output.
- OUTPUT: `p4.2.c` will print the normalized frequencies for each letter a-z to stdout upon reaching EOF (end of file / `ctrl-d` in shell). 
    - The frequencies reported should sum to approximately 1 (with a little slack for accumulation of `printf` rounding errors).
    - The results should be printed as one letter per line, in alphabetical order using the format produced by:

```C
printf("%c %.4f\n", letter, freq);
```

By the way, you cannot implement this function by writing 26 "if" statements (1 for each letter). Hint: Each letter has a numerical [ASCII](https://en.wikipedia.org/wiki/ASCII) value. Can this numerical value be used at all?

**TESTING**: you can test your program by running:
```
$ make p4.2
$ ./p4.2
```

**EXAMPLE**: Assume you have named your executable `p4.2`. The first two example runs show the user entering the text manually in the terminal. The third and fourth runs have text piped in from a file (and the middle of the alphabet is omitted from the output for brevity). A text file `happy_prince.txt` containing a classic story in English is provided for testing.

```
$ ./p4.2
aaab
a 0.7500
b 0.2500
```

```
$ ./p4.2
q
q 1.0000
```

```
./p4.2 < p4.2prince.txt
a 0.0841
b 0.0140
c 0.0206
...
y 0.0240
z 0.0002
```

Try it yourself first; then verify your solutions [here](./files/solution/p4.2.c).


# Bonus material: C vs C++ (C strings vs `std::string`)

C is a subset of C++; all C functions/keywords/code will work with a C++ compiler. In this section, we go over some functions/keywords that are analagous to each other in C and C++.

Let's look at the difference between C string and string in C++.

- C strings are `char` arrays terminated by a null element/byte `\0`; everything that applies to arrays apply to C strings.
- `std::string` in C++ are **objects** (recall: classes); you could even dynamic stuff like:

```C++
std::string s = "Hello";
s += " World!";
```

Always use `std::string` if you have C++ handy, they are a lot safer and easier to use, especially for the novices.

# Bonus material: C vs C++ (pointer vs reference)

You can think of a reference as a constant pointer (i.e. once initialized to a value/object, you cannot change the reference so that it points to something else). Let's look at their differences.

The three main differences are at the top:

| | pointer | reference |
|-|---------|-----------|
| can it store null? | yes | no |
| how do you declare it? | `int\* r = &i;` (declaration is not necessary, pointers get atuomatically created for `int i;`, just do `&i\`) | `int& r = i;` (initialization/assignment is mandatory at declaration; not to be confused with pointer `&i`) |
| can you re-assign another address to it after it is initialized to an address? | yes  | no |
| | |
| what is it? | the address in memory where a value is or can be stored | same as pointer |
| where is it in memory? | stored exactly like an integer variable value on the stack and has its own memory address | has the same memory address as its value BUT also takes up additional space on the stack |
| syntax to access its struct fields (see lab 04) | `->` | `.` |

As a rule of thumb, pointers are great for when you need a null pointer (i.e. you want C to throw an error if it uses this variable with a null pointer) or if you want to do pointer arithmetics (e.g. `*(1+ia)`). For other situations, if you have access to C++, use a reference.

# Credit

Last updated 2021-05 by Alice Yue. 

Course material designed, developed, and initially taught by [Prof. Richard Vaughan](https://rtv.github.io/); this material has since been taught and adapted by Anne Lavergn, Victor Cheung, and others.