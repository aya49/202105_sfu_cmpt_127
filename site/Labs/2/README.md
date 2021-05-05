<div class="lab">

# Laboratory 2: Functions and Arrays

#### Functions, arrays, C character strings, arguments to main, header files

<div id="floatingCornerLeft">[![](../img/balloon0.jpg)](http://books.google.ca/books?id=RFJiAgAACAAJ&dq=%22Computer+lieben+Frauen&hl=en&sa=X&ei=H9SoUuCrBI_YoASa2oCADQ&ved=0CEcQ6AEwAA)</div>

<div id="floatingCornerRight">[![](../img/balloon1.jpg)](http://books.google.ca/books?id=RFJiAgAACAAJ&dq=%22Computer+lieben+Frauen&hl=en&sa=X&ei=H9SoUuCrBI_YoASa2oCADQ&ved=0CEcQ6AEwAA)</div>

### Goals

After this lab you will be able to

1.  Create and use functions
2.  Create and use statically allocated arrays
3.  Create and use text strings (null-terminated character arrays)
4.  Build programs from multiple source files
5.  Create and use header files containing function declarations
6.  Use arguments passed to `main()`
7.  Compile a program from two source files.
8.  Test a function for correctness.

### Setup

<div class="steps">

In the terminal:

1.  Use the `cd` command to change directory (the `ls` command to list the content of a directory may be helpful as well) until you find yourself in your **local repo**.
2.  Download the [new material](2.zip) for Lab 2, stored in a compressed file called **2.zip**.
3.  Uncompress this file as follows:

    <pre>$ unzip 2.zip
    </pre>

    You should now see a directory called **2**.
4.  Once you have uncompressed **2.zip**, you can safely remove this compressed file with the `rm` command.
5.  Add this new directory **2** to your Git repository:

    <pre>$ git add 2
    </pre>

6.  Change directory into **2**, which will be our working directory for Lab 2.

<mark>BTW: never `git add` any executable binary files like `a.out` to your Git repository.</mark>

</div>

### Tasks

1.  [Min/max](#t_funcs)
2.  [Identical](#t_identical)
3.  [Reverse](#t_reverse)
4.  [Scrambled](#t_scrambled)
5.  [Contains](#t_argv)
6.  [Count](#t_redirect)
7.  [CENSORED](#t_censored)
8.  [Letter frequency](#t_lfreq)
9.  [Vertical graph](#t_vgraph)
10.  [InRectangle](#t_inrectangle)

<div class="task" id="t_func1">

## 1\. Function definitions, declarations and header files

### Guide

C is a [structured, procedural programming language](http://en.wikipedia.org/wiki/Procedural_programming_language), that is, it supports the definition of isolated, self-contained blocks of code that can be re-used as components of larger programs. In C and Python these are called _functions_, but other languages call them _procedures, subroutines_, or _methods_.

Given a well-designed function, you can often use it for what it does, and ignore the internal details of how it works. This idea of functional _encapsulation_ makes it feasible for humans to write complex programs by breaking them down into small, more manageable pieces. You have already used several functions provided by the standard library, such as `printf` and `floor`, without seeing how they were implemented. One such function is `max()`, which could be implemented and used as follows:

<pre class="prettyprint linenums">// returns the larger of the two arguments
int max( int int1, int int2)
{
  int larger = int2;
  if( int1 > int2 )
  {
    larger = int1;
  }
  return larger;
}

int main( void )
{
  int num1 = 11;
  int num2 = 12;
  printf( "The max of our numbers is %d\n", max( num1, num2 );
  return 0;
}
</pre>

Reading the first 9 lines of code top-to-bottom, left-to-right, we see:

*   Line 1: A comment describing what the following function does. Commenting our code is a good programming style to adopt.
*   Lines 2-10 are the function definition, as follows:
    *   The result, or _return value_ of running this function is of type `int`.
    *   The name of the function is `max`.
    *   The function takes two integer arguments called `int1` and `int2`.
    *   The _body_ of the function, i.e. the code that will execute when the function is called, starts at `{`.
    *   In the body of the function, the keyword `return` evaluates the expression to it's right which becomes the function's _return value_, then exits the function. Creating functions with only one _return_ statement (only one exit point) is a good programming style to adopt.
    *   The _body_ of the function ends at the closing `}`.

Having been _defined_ in lines 2 to 10, function `max()` is _called_ on line 16. The values of integers `num1` and `num2` are assigned to `int1` and `int2` inside `max()`, the function does its work, and the return value is passed as the second argument to `printf()`.

The syntax for C functions is

<pre class="prettyprint">type functionName( type arg_name1 [, type arg_name2, ...] )
{
    // code-block function body enclosed by curly braces
}
</pre>

Note that `main()` itself is a normal function. The system calls it to start the program.

The name "function" is a little unfortunate, since these are not the same as mathematical functions. Mathematical functions express relationships, while program functions perform sequences of operations on data. To see the difference, consider the function `max()` above and the following function `output()`:

<pre class="prettyprint linenums">void output( double val )
{
  printf( "the value is %.2f\n", val );
}
</pre>

where `void` is a special type that means "nothing". Since there is nothing to return, we can omit the `return` statement and the function will finish at the end of the code block.

Clearly `output()` does not describe a relationship between entities; instead it causes useful things to happen. Strictly speaking this is true of the C function `max()` as well: it _implements_ the mathematical function `max()` by returning the largest of its arguments.

We are stuck with the C convention of calling our procedures "functions". In practice this is not usually a problem. We will return to the differences between "true" functions and C functions later in a discussion of software engineering approaches.

#### Multiple arguments

As the syntax above indicates, function definitions can specify an arbitrary number of arguments, for example:

<pre class="prettyprint linenums">double volume( double width, double height, double depth )
{
  return width*height*depth;
}
</pre>

However, C functions can have only a single return value. Other languages such as Lisp and Go support multiple return values, so this asymmetry between the number of arguments and results was a design decision in C. It keeps the syntax simple.

#### Functions in functions

Since `main()` is a function, it should be apparent that functions can call other functions. In general a function may call any other function. One interesting situation is when a function calls itself, a process called _recursion_. Many algorithms are elegantly expressed as recursive functions. You may have seen this idea before: proof by induction relies on it.

#### Function Declarations

Above we looked at three function definitions: `max()`, `output()` and `volume()`. A function can be called in a C source code file below its definition. Why only below? The compiler reads the source file from top to bottom. If it sees a call to function `foo()`, it doesn't know anything about that function. Did you specify the right number and type of arguments? There's no way to know. The compiler will complain.

When you want to use a function that is not defined in your source file, for example a standard library function, we need some way to tell the compiler the name of the function, its arguments and return type. The implementation of the function will be provided from a library or some other source file.

A function declaration is the same as its definition, but with the function body replaced by a semicolon. Thus for `volume()` above, a matching declaration is:

<pre class="prettyprint">double volume( double width, double height, double depth );
</pre>

#### Header files

Your code almost always begins by including some header files:

<pre class="prettyprint">#include <stdio.h>
#include <math.h>
(etc)
</pre>

Recall that `#include` copies the contents of the indicated file into the current source file. Specifying the name of the header file `<like this>` forces the compiler to look for the file in the directories where your compiler was installed. To specify file you wrote yourself put the filename in quotes `"like this"`. For example:

<pre class="prettyprint">#include <stdio.h> // a system-supplied header
#include "myheader.h" // a header I wrote myself
</pre>

The quotes version understands paths relative to the current directory, and absolute paths, e.g.:

<pre class="prettyprint">#include "myheader.h" // in the current directory
#include "include/myheader.h" // in a subdirectory
#include "../myheader.h" // in the parent directory
#include "/opt/local/include/myheader.h" // an absolute path
</pre>

C header files usually contain mostly function declarations. In the case of the standard library the implementations of these functions were pre-compiled for you into code _libraries_ and shipped with your compiler to save you time. The required libraries are _linked_ into your program at the last step of compilation. The library containing `printf()` is used so often it is linked by default. The math library containing `floor()`, etc. is used less often, so we have to request it in in the compile command. It is still used a lot, so [the designer](http://en.wikipedia.org/wiki/Dennis_Ritchie) gave it the nice short name `m`.

<pre>$ gcc -o mycode mycode.c -lm </pre>

Header files also provide important constant values, such as the special value EOF (usually -1) returned by `scanf()` when reaching the end of a file. Occasionally they also declare global variables.

Now you know how to define and declare functions, and what header files do.

### Using multiple source files

Function declarations and header files are also used when breaking your own code up into multiple source files. For example, in your working directory you have the source files `funcs.c` containing useful function definitions and `main.c` containing your main program:

Contents of `funcs.c`:

<pre class="prettyprint linenums">// returns the larger of the two arguments
int max( int int1, int int2 )
{
  int larger = int2;
  if( int1 > int2 )
  {
    larger = int1;
  }
  return larger;
}

// returns the smaller of the two arguments
int min( int int1, int int2 )
{
  int smaller = int2;
  if( int1 < int2 )
  {
    smaller = int1;
  }
  return smaller;
}
</pre>

Contents of `main.c`:

<pre class="prettyprint linenums">#include <stdio.h>

int main( void )
{
  int num1 = 11;
  int num2 = 12;
  printf( "The max of our numbers is %d.\n", max( num1, num2 ));
  printf( "The min of our numbers is %d.\n", min( num1, num2 ));
  return 0;
}
</pre>

Given multiple source files on its command line, the compiler will attempt to compile them all into one program. Try this now:

<pre class="steps">$ gcc -Wall funcs.c main.c -o fcn</pre>

The `-Wall` compiler option enables "all warnings". The compiler therefore will be very strict when it compiles your code and will warn you about potential problems.

With these files as they are you will get warnings and possibly errors complaining that in `main.c`, `min()` and `max()` are not properly declared. The exact message you get depends on your compiler vendor and version, but in CSIL we get:

<pre class="prettyprint">main.c:7:45: warning: implicit declaration of function 'max' is invalid in C99
 [-Wimplicit-function-declaration]
  printf( "The max of our numbers is %d\n", max( num1, num2 ));
                                            ^
main.c:8:45: warning: implicit declaration of function 'min' is invalid in C99
 [-Wimplicit-function-declaration]
  printf( "The min of our numbers is %d\n", min( num1, num2 ));
                                            ^
2 warnings generated.
</pre>

Note that your code will execute even if it generated some warnings during compilation. However, it is good programming practice to investigate the cause(s) of the warnings as they may indicate potential problemsin your code.

### Requirements

First, check that you completed the Setup section above, so your current working directory is `<local repo>/2` . The shell command `pwd` prints the current working directory.

<div class="req">

1.  Create a new file called `funcs.h` that contains function declarations for all the functions in `funcs.c`. Remember (as we have seen above) that a function declaration is the same as its definition, but with the function body replaced by a semicolon. Thus for `volume()` above, a matching declaration is:

    <pre class="prettyprint">double volume( double width, double height, double depth );
    </pre>

    Edit the file `main.c` to `#include` the new header file.
2.  The finished code must compile with this command with no errors or warnings. In this command, the executable file is named `fcn`:

    <pre>$ gcc main.c funcs.c -o fcn</pre>

3.  The finished code must output

    <pre>The max of our numbers is 12.
    The min of our numbers is 11.
    </pre>

</div>

### Testing and Submitting

The compiler will produce informative complaints if your declarations are not correct. Read the compiler output very carefully, starting with the top lines.

<div class="steps">

Submit by adding your header file and committing your changes:

<pre>$ git add funcs.h
$ git commit -m "task1 is working"
$ git push 
</pre>

</div>

</div>

<div class="task" id="t_identical">

## 2\. Arrays

### Guide

In C any type can be used to create both simple variables and arrays:

<pre class="prettyprint">int anInt;	     // a single integer
int intArray[100];   // an array of 100 integers

char aChar;          // a single character
char charArray[100]; // an array of 100 characters
</pre>

Array elements are accessed by index, counting from 0:

<pre class="prettyprint">int intArray[100];        // an array of 100 integers

intArray[0] = 99;         // set the first element of intArray to 99
int int1 = intArray[42];  // get the 43rd element of intArray
int int2 = intArray[100]; // OOPS! this is the 101st element of a 100-element array
</pre>

C arrays have some important limitations compared to arrays/vectors in other languages:

1.  All elements of the array are the same type;
2.  The length of an array is fixed at creation time;
3.  The value of array elements is not initialized;
4.  Access to elements is not bounds checked (i.e. lookups are not checked to make sure (0 <= index < array size)).

These limitations mean that C arrays must be used carefully but are _very fast indeed_. There is a trivial amount of overhead in accessing data from an array compared to a normal variable. There is also very little cost to creating arrays. For these reasons C programmers use arrays a lot despite the limitations.

Arrays are allocated as contiguous chunk of memory, of size (array-length * sizeof(type)) bytes. The name of the array can be used like a pointer to the first byte of the first element in the array. The memory is automatically freed when the array variable goes out of scope. And that is all there is to implementing arrays in C. It is an incredibly simple and efficient design.

Because the name of an array can be used like a pointer, these things are true:

<pre class="prettyprint">int intArray[100];
&intArray[0] == intArray;
*(intArray+5) == intArray[5];
*(5+intArray) == intArray[5];
(5+intArray) == &intArray[5];
</pre>

Most people find the square-bracket array-indexing syntax easier to read than pointer arithmetic, but they are exactly equivalent to the compiler.

### Passing arrays to functions

Since array variables can be used like pointers, you can pass them into functions as such. Consider this code:

<pre class="prettyprint linenums">#include <stdlib.h>
#include <stdio.h>

// return the largest int in the array
// (pointer syntax)
int array_max_ptr( int* arr, unsigned int len )
{
   int max = arr[0];
   for( unsigned int i=1; i<len; i++ )
   {
      if( arr[i] > max )
      {
         max = arr[i];
      }
   }

   return max;
}

// return the largest int in the array
// (preferred array-specific syntax)
int array_max_brackets( int arr[], unsigned int len )
{
   int max = arr[0];
   for( unsigned int i = 1; i < len; i++ )
   {
      if ( arr[i] > max )
      {
         max = arr[i];
      }
   }

   return max;
}

const unsigned int sz = 10;

int main( void )
{
   int arr[sz];
   for( unsigned int i = 0; i < sz; i++ )
   {
      arr[i] = random();
      printf( "arr[%u] == %d\n", i, arr[i] );
   }

   printf( "Largest was\n %d\n %d\n",
	   array_max_ptr( arr, sz ),
	   array_max_brackets( arr, sz ) );

   return 0;
}
</pre>

The two versions of the array_max function have different syntax for passing the array, but are otherwise identical. You should almost always use the array-bracket syntax version ( `int arr[]` ) since it tells the human reader that an array is expected. The compiler doesn't care.

Note that we had to pass the length of the array into both versions. C arrays do not know how long they are.

Notice also that we used an `unsigned int` for the array length. This is sensible because negative-length arrays can not exist. Since the compiler will ensure that `len` does not have a negative value, we avoid a whole class of possible bugs. In general we always use the most restrictive type available so that the compiler can help us notice such mistakes.

Read this example carefully and make sure you understand every bit before you move on.

### Requirements

<div class="req">

1.  Create a new file called `identical.c`, containing a single function that matches this declaration:

    <pre>int identical( int arr1[], int arr2[], unsigned int len );</pre>

2.  Arrays `arr1` and `arr2` are both of length `len`, and contain arbitrary integer values.
3.  The function `identical()` should return 1 iff arrays `arr1` and `arr2` contain the same values in the same order, or 0 otherwise.
4.  `len` can have any unsigned int value, including 0.
5.  If `len` is 0 then `identical()` should return 1 (since the arrays have the same - empty - contents).
6.  You must not change the contents of the arrays.

</div>

Examples of arrays for which `identical` should return 1:

*   arr1 = {10,15,20}, arr2 = {10,15,20}
*   arr1 = {100}, arr2 = {100}
*   arr1 = {5,2,2,3,4,5,5}, arr2 = {5,2,2,3,4,5,5}
*   arr1 = {}, arr2 = {} (i.e. len = 0)

Examples of arrays for which `identical` should return 0:

*   arr1 = {1,1}, arr2 = {1,2}
*   arr1 = {10,15,20}, arr2 = {10,15,21}
*   arr1 = {1,2,3,4,5}, arr2 = {5,3,4,2,2}

Example of a program that uses your function:

<pre class="prettyprint linenums">#include <stdio.h>
// declaration of function implemented in identical.c
int identical( int intArray1[], int intArray2[], unsigned int len );

int main( void )
{
   int arr1[3] = {10, 15, 20};
   int arr2[3] = {10, 20, 15};

   if( identical( arr1, arr2, 3 ) == 1 )
   { 
      printf( "arr1 and arr2 are identical\n" );
   }  else {
      printf( "arr1 and arr2 are NOT identical\n" );
   }

   return 0;
}
</pre>

Note the curly-brace syntax for initializing arrays. This only works when you first declare the array. The items listed between curly braces must be constant values.

### Testing and submission

You should write your own test program (also called _test driver_) with a `main()` function, using the example above as a guide.

When your function works, add and commit only the single source file to the repo:

<pre>$ git add identical.c
$ git commit -m "identical is working"
$ git push 
</pre>

<div class="task" id="t_reverse">

## 3\. Reverse

### Requirements

<div class="req">

1.  Create a new file called `reverse.c`, containing a single function that matches this declaration:

    <pre>void reverse( int arr[], unsigned int len );</pre>

2.  Array `arr` is of length `len`, and contains arbitrary integer values.
3.  The function should reverse the contents of the array _in-place_, so that on returning, the array contains the same values as before, but in the reverse order.

</div>

### Guide

Example of a program that uses your function:

<pre class="prettyprint linenums">#include <stdio.h>

// declaration of function implemented in reverse.c
void reverse( int arr[], unsigned int len );

int main( void )
{
  int intArray[] = {11, 12, 13};
  unsigned int len = 3;

  reverse( intArray, len );

  for( unsigned int i = 0; i < len; i++ )
  {
     printf( "%d ", intArray[i] );
  }
  printf( "\n" );

  return 0;
}
</pre>

This code prints:

<pre>13 12 11
</pre>

Notice that the length of the array

<pre>intArray[]</pre>

is not specified explictly: it is set to the length of the initialization list

<pre>{11, 12, 13}</pre>

i.e. 3.

### Testing and submission

You should write your own test program with a `main()` function, using the example above as a guide.

When your function works, add and commit only the single source file to the repo:

<pre>$ git add reverse.c
$ git commit -m "reverse is working"
$ git push 
</pre>

</div>

<div class="task" id="t_scrambled">

## 4\. Scrambled

Here is a programming puzzle that you might find in the real world. It requires conditionals, loops and arrays. There is a simple _O(n)_ algorithm to solve the problem (i.e. you do not need to sort anything).

### Requirements

<div class="req">

1.  Create a new file called `scrambled.c`, containing a single function that matches this declaration:

    <pre>int scrambled( unsigned int arr1[], unsigned int arr2[], unsigned int len );</pre>

2.  Arrays `arr1` and `arr2` are both of length `len`, and contain values in the range [0 .. 99] inclusive, only.
3.  The function `scrambled()` should return 1 iff arrays `arr1` and `arr2` contain the same values in any order, or 0 otherwise.
4.  `len` can have any unsigned int value, including 0.
5.  If `len` is 0 then `scrambled()` should return 1 (since the arrays have the same - empty - contents).
6.  You must not change the contents of the arrays.
7.  Use an algorithm that has run time linear in the array length `n`. Note that this means you **can not sort the arrays** since that can not be done in linear time.

</div>

Examples of arrays for which scrambled should return 1:

*   arr1 = {10,15,20}, arr2 = {10,15,20}
*   arr1 = {99}, arr2 = {99}
*   arr1 = {1,2,3,4,5}, arr2 = {5,3,4,2,1}
*   arr1 = {}, arr2 = {} (i.e. len = 0)
*   arr1 = {2,1,3,4,5}, arr2 = {1,2,4,3,5}

Examples of arrays for which scrambled should return 0:

*   arr1 = {1,1}, arr2 = {1,2}
*   arr1 = {10,15,20}, arr2 = {10,15,21}
*   arr1 = {1,2,3,4,5}, arr2 = {5,3,4,2,2}

Example of a program that uses your function:

<pre class="prettyprint linenums">#include <stdio.h>
// declaration of function implemented in scrambled.c
int scrambled( unsigned int arr1[], unsigned int arr2[], unsigned int len );

int main( void )
{
  unsigned int arr1[3] = {10, 15, 20};
  unsigned int arr2[3] = {10, 20, 15};

  if( scrambled( arr1, arr2, 3 ) == 1 )
  {
     printf( "arr2 is a scrambled version of arr1\n" );
  } else {
     printf( "arr2 has different contents to arr1\n" );
  }

  return 0;
}
</pre>

### Hint

The number of different values you see is known and quite small.

### Testing and submission

You should write your own test program with a `main()` function, using the example above as a guide. To reiterate: you must not submit a complete program, though you will need to write one to test your function yourself. You must submit a single file containing a single function.

When your function works, add and commit **only the file `scrambled.c` to the repo**:

<pre>$ git add scrambled.c
$ git commit -m "scrambled is working"
$ git push 
</pre>

<div class="task">

## 5\. Program arguments

So far you have written programs that read their input from stdin. Another way to get data into a program is with program _arguments_. For example when using the shell's file copy program `cp` we type:

<pre>$ cp original copy</pre>

`cp` is not using stdin, so how does it learn about the filenames to read from and copy to? The answer is as arguments to `main()`. Your program must have a single main function and it can be declared like this if it needs no arguments from the outside world:

<pre class="prettyprint">int main( void )
{
...
}</pre>

or, if it needs arguments, like this:

<pre class="prettyprint">int main( int argc, char* argv[] )
{
...
}</pre>

These two arguments work for _any_ possible arguments to your program. This is quite a clever design, and it works by using arrays and pointers.

The arguments are interpreted as follows:

*   `int argc` is the number of arguments passed into `main`, plus one. For the `cp original copy` example, this is 3.
*   `char* argv[]` is an array of char pointers. The `argv` array is `argc` pointers long. The zeroth entry in argv is always the program's own name (what use is this?). The subsequent entries are the program arguments in order. For our cp example the contents of the array are:

    <pre>argv[0] : "cp"
    argv[1] : "original"
    argv[2] : "copy"
    </pre>

Recall that a C string is a character array containing a special NULL character (the character '\0' or value 0) to mark the end of its text: the _null terminator_. Each pointer in the `argv` array points to the first character in a character array. The result for our example can be drawn as follows, if we use arrows to represent pointers:

![](../img/argv.png)

Thus we can sketch an implementation of `cp` like this:

<pre class="prettyprint linenums">int main( int argc, char* argv[] )
{
  int inputfile = open( argv[1], O_RDONLY ); // open a file for read only
  int outputfile = open( argv[2], O_RW | O_CREAT );  // create a new file for writing

  while( ... ) // we haven't read everything from inputfile
  {
     ... // read bytes from inputfile and write them to outputfile
  }
 return 0; // success!
}
</pre>

Function `open()` is called twice: once with `argv[1]`, the name of the file to copy (i.e. "original" in the example). Then `open()` is called again with `argv[2]`, the name of the destination file to copy to (i.e. "copy" in the example).

#### I want numbers, not text strings

Since main's arguments are stored as character strings, another step is needed to convert strings that represent numbers into number types before you use them. The `atoi()` and `atof()` functions provided in the standard library convert strings to integers and floating point values respectively:

<pre class="prettyprint linenums">#include <stdlib.h> // for atoi() and friends

// takes two arguments: an integer followed by a float
int main( int argc, char* argv[] )
{
  if( argc != 3 ) // yes 3! argv[0] is the program name
  {
     printf( "I wanted 2 arguments\n" );
  }

  int anInt = atoi( argv[1] );
  float aFloat = atof( argv[2] );
  ...
}
</pre>

The program can be run like so and work as expected:

<pre>$ ./a.out 5 3.14</pre>

<t3>Requirements</t3>

<div class="req">

1.  Write a program called "contains" that takes two text strings as arguments and prints "true" followed by a newline if the second string is entirely contained within the first, or "false" followed by a newline otherwise.
2.  The strings contain only ASCII characters and may be any length > 0 characters. Strings in `argv` are always null-terminated.

</div>

This is an [important problem in computer science](http://en.wikipedia.org/wiki/Substring), with wide applications from searching the internet, to understanding text, to finding DNA matches. It's easy to state and easy to code. It gets interesting when the strings are long and you want to do it very efficiently. For now you can be happy with a simple solution to practice managing `argv` array and char strings.

Example runs:

<pre>$ ./contains "I have a really bad feeling about this" "bad feeling"
true
$ ./contains "To be or not to be" "That is the question"
false
$ ./contains "I am the walrus" "I am the walrus"
true
$ ./contains "the walrus" "I am the walrus"
false
$ ./contains "kmjnhbvc45&^$bn" "."
false
</pre>

Notice that the strings do not have quote characters around them when delivered to your program via `argv`. The quotes prevent the shell from breaking the strings up into individual words.

You may find the standard library function `strlen()` (along with other string-related functions) useful. Read its manpage.

**NOTE: pay attention to the requirements, e.g. don't forget the newlines.**

### Testing and submission

Save your implementation as the single C source file `contains.c`, compile it and test it using the example runs above and others. When you think your code works, add and commit `contains.c`, then push your changes as usual.

</div>

<div class="task">

## 6\. Redirecting stdin and stdout

From here on, the guide section will often include links to other material that can be crucial to solving the task. You should practice consulting online references and tutorials: this is a significant part of real-world programming. To encourage you to practice, we use external links instead of writing everything out in the guide. To be absolutely clear: <mark>not everything you need to know is contained in our instructions. Therefore, you need to read about the new material discussed in the labs (e.g., C library functions, etc...) using the links and maybe searching online. This is deliberate and not cause for complaint!</mark>

### Guide

You will find it tedious to type lots of text into your program's stdin. The shell has a powerful tool to help with this: _stream redirection_. This allows you to route the stdin and stdout for a program away from the console and into a file. For example, if we have a program called `hello` that prints "Hello world!\n" on stdout, we can do this:

<pre>$ ./hello > myfile.txt
</pre>

This creates a new file `myfile.txt`. Anything written to stdout in the `hello` program is written to the file `myfile.txt`. To confirm this, inspect the contents of the file with `cat`:

<pre>$ cat myfile.txt
Hello world!
</pre>

Similarly, we can take the contents of a file, and stream it into the standard input of our program. So if we have a program `sort` that reads lines from stdin, sorts them into lexical order then writes them on stdout, we can do this:

Contents of file `beatles.txt`:

<pre>john
paul
george
ringo
</pre>

<pre>$ sort < beatles.txt
george
john
paul
ringo
</pre>

Input and output redirection can be used together:

<pre>$ sort < beatles.txt > sorted.txt
$ cat sorted.txt
george
john
paul
ringo
</pre>

This is a very powerful mechanism that is great for testing with lots of different inputs. It's much more convenient to redirect a file into stdin than to type many lines followed by ctrl-d over and over. Make sure you understand file redirection!

Here is a terse but good introduction to [BASH shell programming](http://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO.html), including a section on [redirection](http://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO-3.html).

Here is an task that will make you glad you know about shell redirection:

### Requirements

<div class="req">

1.  Write a C program that counts the number of characters, words and lines read from standard input until EOF is reached.
2.  Assume the input is [ASCII](http://en.wikipedia.org/wiki/ASCII) text of any length.
3.  Every byte read from stdin counts as a character except EOF.
4.  Words are defined as contiguous sequences of letters (a through z, A through Z) and the apostrophe ( ', value 39 decimal) separated by any character outside these ranges.
5.  Lines are defined as contiguous sequences of characters separated by newline characters ('\n').
6.  Characters beyond the final newline character will not be included in the line count.
7.  On reaching EOF, use this output command:

    <pre class="prettyprint">printf( "%lu %lu %lu\n", charcount, wordcount, linecount );</pre>

    Where `charcount`, `wordcount` and `linecount` are all of type `unsigned long int`. You may need these large types to handle long documents.

</div>

### Guide

You may find the standard library function `getchar()` useful. Check it out onlin or read its manpage.

There's a handy standard program called `wc` that does a similar job, but it does not match the requirements exactly (it is a little more clever about word boundaries and will sometimes count fewer words than our simple program). Your program should agree with wc's character and line counts, as the logic for those is the same.

#### Escape characters

This [Q&A on StackOverflow](http://stackoverflow.com/questions/2414478/c-escaping-an-apostrophe-in-a-string) gives advice on representing the apostrophe character using an _escape sequence_. StackOverflow is very useful indeed.

### Testing and submission

Submit your solution as a complete program (i.e. with a `main()` function) in a C source file called `count.c`.

</div>

</div>

<div class="task">

## 7\. CENSORED

### Requirements

<div class="req">

1.  Write a C program called `censored.c` that takes any number of one-word text string arguments, each less than 128 characters long.
2.  "Word" is defined as in the previous task. (Tip: Can you reuse some of the code you wrote for Task 6?)
3.  The program copies text from stdin to stdout, except that any of the words seen in the input are replaced with the word "CENSORED".
4.  The argument and the input stream are both [ASCII](http://en.wikipedia.org/wiki/ASCII).
5.  The input to stdin is of any length.

</div>

Example runs:

<pre>$ cat poem.txt
Said Hamlet to Ophelia,
I'll draw a sketch of thee,
What kind of pencil shall I use?
2B or not 2B?
$ ./censor Ophelia < poem.txt
Said Hamlet to CENSORED,
I'll draw a sketch of thee,
What kind of pencil shall I use?
2B or not 2B?
</pre>

<pre>$ cat beatles.txt
paul
ringo
george
john
$ ./censor paul ringo john < beatles.txt
CENSORED
CENSORED
george
CENSORED
</pre>

### Testing and submission

Submit your solution as a complete program in a C source file called `censored.c`.

</div>

<div class="task">

## 8\. Letter frequency

### Requirements

<div class="req">

1.  Write a program that calculates the frequency of letter occurrences in text.
2.  Read ASCII text from standard input.
3.  On reaching EOF, print to stdout the normalized frequency of occurrence for each letter a-z that appeared in the input, one per line, in alphabetical order using the format produced by

    <pre>printf( "%c %.4f\n", letter, freq);</pre>

4.  Letters that occur zero times should not appear in the output.
5.  Characters other than lower and upper case letters should be ignored.
6.  Lower and upper case instances count as the same letter, e.g. 'a' and 'A' are both reported for the letter 'a' on the output.
7.  The frequencies reported should sum to approximately 1 (with a little slack for accumulation of `printf` rounding errors).
8.  By the way, you cannot implement this function by writing 26 "if" statements (1 for each letter). Hint: Each letter has a numerical ASCII value. Can this numerical value be used at all?

</div>

#### Example runs

Assume you have named your executable `lfreq`. The first two example runs show the user entering the text manually in the terminal. The third and fourth runs have text piped in from a file (and the middle of the alphabet is omitted from the output for brevity). A text file `happy_prince.txt` containing a classic story in English is provided for testing.

<pre>$ ./lfreq
aaab
a 0.7500
b 0.2500
</pre>

<pre>$ ./lfreq
q
q 1.0000
</pre>

<pre>./lfreq < happy_prince.txt
a 0.0841
b 0.0140
c 0.0206
...
y 0.0240
z 0.0002
</pre>

<pre>$ ./lfreq < "large novel in English.txt"
a 0.0817
b 0.0149
c 0.0278
...
y 0.0197
z 0.0001
</pre>

### Testing and submission

Submit your solution as a complete program in a C source file called `letterfreq.c`.

</div>

<div class="task" id="t_vgraph">

## 9\. Vertical graph

In Lab 1 we plotted a histogram horizontally. In order to plot a histogram vertically, we need to have finished reading all the input before we start drawing the graph on the output. An array is suitable for this.

A standard terminal window is 80 character-columns across. If we limit the number of columns we can graph to a maximum of 80, we know how large an array we need to allocate and this program is simple to write.

### Requirements

<div class="req">

1.  Read integer values from stdin, separated by one or more spaces or newlines, until reaching EOF.
2.  The input is guaranteed to be well-formed. (Hum... what does this mean?)
3.  The input contains no more than 80 values.
4.  On standard output, render a simple vertical column graph representation of the input values, in order left to right, using hash '#' characters as shown in the examples below. The number of hashes printed in each column should be equal to the corresponding input value.
5.  The area above a completed column should be filled with space characters.
6.  Ignore empty lines. Do not output a column for an empty line.
7.  The entire graph must end with a newline character.

</div>

### Guide

Hint: you may find it helpful to draw your graphs upside down (increasing down the screen) first, then change your code to flip the output it up the right way.

### Examples

1.  Input:

    <pre>1 1 3 1</pre>

    Output:

    <pre>  #
      #
    ####
    </pre>

    The requirements mean that the graph fills a rectangular area with hashes and spaces, so this example is printed as:

    <pre>' ', ' ', '#', ' ', '\n'
    ' ', ' ', '#', ' ', '\n'
    '#', '#', '#', '#', '\n'
    </pre>

    In particular, notice the spaces before the newlines on the first two lines. They are necessary.

2.  Input:

    <pre>3 4 5</pre>

    Output:

    <pre>  #
     ##
    ###
    ###
    ###
    </pre>

3.  Input:

    <pre>0 3 0 4 5</pre>

    Output:

    <pre>    #
       ##
     # ##
     # ##
     # ##
    </pre>

    Notice the empty columns that correspond to the zeros in the input, including the leading zero.

4.  Input:

    <pre>5
    15
    16
    15
    12
    12
    12
    8
    6
    3
    2
    19
    21
    17
    15
    12
    11
    10
    9
    8
    7
    7
    </pre>

    Output:

    <pre>            #
                #
               ##
               ##
               ###
      #        ###
     ###       ####
     ###       ####
     ###       ####
     ######    #####
     ######    ######
     ######    #######
     ######    ########
     #######   #########
     #######   ###########
     ########  ###########
    #########  ###########
    #########  ###########
    ########## ###########
    ######################
    ######################
    </pre>

5.  Input:

    <pre>0
    0
    2
    1
    0
    </pre>

    Output:

    <pre>  #
      ##
    </pre>

### Testing and submission

Submit your solution as a complete program in a C source file called `verticalgraph.c`.

</div>

<div class="task" id="t_inrectangle">

## 10\. In Rectangle

In this task you must write a function that determines whether a point lies inside a rectangle. The point and rectangle are both specified using arrays of floating point values.

### Requirements

<div class="req">

1.  Write a function that matches the following declaration:

    <pre class="prettyprint">int InRectangle( float pt[2], float rect[4] );
    </pre>

2.  Argument `pt[2]` defines a point on the plane: `pt[0]` is the x-coordinate, `pt[1]` is the y-coordinate.
3.  Argument `rect[4]` defines a rectangle on the same plane. `rect[0]` and `rect[1]` define the x- and y- cordinates respectively of one corner of the rectangle. `rect[2]` and `rect[3]` define the opposite corner.
4.  Coordinates may be any valid floating point value, including negative values.
5.  The function returns int `0` (false) for any point that lies outside the rectangle, and `1` (true) for any other point (i.e. points inside and on the boundary of the rectangle).

</div>

### Guide and Testing

It is very common to represent geometric figures using small, fixed-size arrays like this. Note that the size of the arrays are specified in the function declaration. This allows the compiler to check that the function is called with a correctly-sized array.

Since this task calls for a function only, and not a complete program, you need to write a program to test your function. The grading robot uses a program that looks something like this:

<pre class="prettyprint linenums">// declaration of function to test
int InRectangle( float pt[2], float rect[4] );

int main( int argc, char* argv[] )
{
  // define a rectangle from (1,1) to (2,2)
  float rect[4] = {1.0, 1.0, 2.0, 2.0 };

  // define a point that is inside the rectangle
  float p_in[2] = { 1.5, 1.5 };

  // define a point that is outside the rectangle
  float p_out[2] = {2.5, 0.5};

  // define a point that is on the edge of the rectangle
  float p_edge[2] = {1.0, 1.0};

  // InRectangle() should return 0 (false) for points that are NOT in
  // the rectangle, and non-zero (true) for points that are in the
  // rectangle. Points on the edge are considered *in* the rectangle.

  // test 1
  if( InRectangle( p_in, rect ) == 0 )
  {
    puts( "error: should return true for p_in." );
    return 1; // indicate error
  }

  // test 2
  if( InRectangle( p_out, rect ) != 0 )
  {
    puts( "error: should return false for p_out." );
    return 1; // indicate error
  }

  // test 3
  if( InRectangle( p_edge, rect ) == 0 )
  {
    puts( "error: should return true for p_edge." );
    return 1; // indicate error
  }

  return 0; // all tests passed
}
</pre>

The code tests that the function works correctly with these parameters:  

<center>![](../img/InRectangle.png)</center>

The actual test used by the grading robot is longer and more comprehensive than this. Above, we gave a simplified example for clarity.

Note the syntax for initializing arrays with constant values at compile-time, e.g. line 7\. This only works for constant values, unfortunately.

You should **always** write a test for your functions. Consider an untested function to be incorrect. It helps to assume the function was written by a complete idiot who has no idea what they are doing, even if the author was you. Then test the function to find out what craziness that daft person implemented.

Once a function passes all the tests you can think of, you might cautiously believe it might be correct. In software engineering, like any quality-focused pursuit, it helps to be skeptical.

#### Compiling two files into one program

Since the file you submit must not contain a `main()` function (see Submission section below), it is convenient to make a test program from two source files: one containing the `InRectangle()` function, and one with `main()`. You can start out with the code above, and extend it to be a more thorough test.

Recall from above that you can compile a single program from multiple source files by simply listing the sources on the compiler command line:

<pre>$ gcc -o test inrect.c main.c
</pre>

### Submission

Submit your solution as a C source file called `inrect.c`. The file must not contain a `main()` function, even though you wrote one for testing. The grading robot will compile your file along with it's own `main()`. Since there can only be one `main()`, if you provide a second, the compilation will fail.

</div>

<div class="labends">Lab 2 completed. [Back to the course web page](../../).</div>

</div>

</div>
