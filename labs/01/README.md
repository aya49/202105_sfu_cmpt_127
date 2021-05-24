# Lab 01: Introduction to C

Download lab files [here](./files.zip).

Lecture recording(s): [2021-05-18](https://youtu.be/LRRYe0YWVdk)

Review "Guide"s and accompanying slides (we will go over these during the lab lecture).
- Course outline ([slides](https://docs.google.com/presentation/d/19MI7qZW5vdthKojCezivhSF3kx9NnZdOIc2e-Kr7E5Y/edit?usp=sharing))
- [Guide 01](#guide) ([slides](https://docs.google.com/presentation/d/1zwLTZjPFa8Ff4Eq3Qk9nTL72QQyCl22rLGIVo0gGdvs/edit?usp=sharing)): introduction to C; C syntax, workflow, and compiling
- [Guide 02](#guide-1) ([slides](https://docs.google.com/presentation/d/190OipgViJdy5Lr_GlBDHxRkRSY8iP_xixe3slwoyx58/edit?usp=sharing)): variables
- [Guide 03](#guide-2) ([slides](https://docs.google.com/presentation/d/1dBXA2Lsim2lFisvjnfkTylcQ2rqIEl9g1VZ0JA44pRY/edit?usp=sharing)): conditions and loops

Try "Practice" problems; these will NOT be graded. Note that the solutions given for Practices is just one of many possible solutions, better ones may exist.
- [Practice 01](#practice-01)
- [Practice 02.1](#practice-021)
- [Practice 02.2](#practice-022)
- [Practice 03](#practice-03)
- [Practice 04](#practice-04)

Do [Assignment 01](../../assignments/01).

Always remember, the internet is your friend :) Search for documentation online and make sure to understand why things work the way they do!

# Introduction: basic C syntax and compile workflow

In this course you will learn to code in C. C was created by [Dennis Ritchie](https://en.wikipedia.org/wiki/Dennis_Ritchie). [Brian Kernighan](https://en.wikipedia.org/wiki/Brian_Kernighan) wrote the first C tutorial. The first edition of this book written by them (called K&R for short) was published in 1978.


## Guide

### C syntax

```C
// author: <YOUR SFU USER ID HERE>
// date: 2021-05-18
// input: void
// output: int
// description: prints a greeting to standard output.

#include <stdio.h>

int main(void) {
    printf("Hello World\n");
    return 0;
}
```

This C or C++ program prints a greeting to the [standard output (stdout)](http://www.linfo.org/standard_output.html), a text stream that your command-line-based program (shell) uses to output text to the screen (or other places we will see later).

- `//` starts a line of comments; comments are text not processed by the computer and are there for documentation purposes only.
- `#include <stdio.h>` copies the contents of `stdio.h` directly into the program code. Below the `#include` line we can call any functions declared in the included file, including `printf`. Before we use `printf`, we need to tell the compiler where to find it so we import a declaration of its name and the arguments it accepts. This is provided with your compiler installation in the file `stdio.h`. The compiler is set up so that it knows where to look for it. It's often in the `/usr/include` directory on Linux.
- `int main(void)` defines a function called `main` that returns an integer (`int`) and takes no arguments (`void`). C programs always start running at the `main` function. It's a bit more complicated in C++, but in both languages every program contains exactly one `main`, which is called by the operating system when the program starts. If you forget to define `main`, the compiler will report an error because it does not know where to start the program execution. The body of the function is contained within curly braces `{ ... }`. Unlike Python, the C compiler ignores indentation and newlines completely: they are only used to lay out the code for humans to read. Spaces, tabs and newlines do nothing except separate the tokens - the linguistic atoms - of the language.
- `printf` is a C function from `stdio.h` that composes a chunk of text and sends it to standard output (stdout). As in many other languages, C strings are a sequence of characters contained within double-quote characters `"like this"`. We will come back to the details of C strings later. 
- `\n` is an **escape sequence** that represents the newline character. This is different from a `print` statement in Python that automatically ends the line for you: the C function `printf` does not. To have a newline in output, we have to represent it with this special escape sequence.
- Statements end with a semicolon `;`. This is different from Python which uses newlines to end statements.
- `return 0;` causes the `main` function to return the integer value `0` (zero) as the result of the function. Back on `int main(void)`, we promised that the main function would return an integer, and the compiler would warn us if we forgot to do so. Since this is the `main` function, the caller is the command shell which invoked (ran) the program, which receives the value zero as the program's result. C programs always return an integer, and programmers conventionally use this value to indicate that the program was successful by returning zero, or a non-zero error code if something went wrong. We return zero to indicate that we detected no problems.


### Compiling the C program

Go to your **shell**, this is where you replay commands to your machine.

1. Compile the source code file `t1.c` to create a binary executable file that can be run from the shell:

```
$ gcc t1.c
``` 
    
2. If the program compiled correctly, the compiler created a new file in the current directory called `a.out` containing your executable program. Instead if you get error messages read them carefully, top to bottom and edit the code to fix the first reported error, then compile again. Once all looks well, run your program using its name like so:

```
$ ./a.out
``` 
    
(where "./" means "this directory"). You should see the expected output on your console:

```
Hello World
```

3. Specify a more descriptive name for your program than the default `a.out` with the compiler output name option `-o`:

```
$ gcc t1.c -o t1
$ ./t1
Hello World
```
    
You now have a working program written in C and built with your bare hands using only the command line. Not bad.


### IMPORTANT: designing, testing, and debugging programs

All programs you will design can be seen as a black box that have 
- some **input** (e.g. no input `void`), 
- some **output** (e.g. integer output `0`), and 
- some **behaviour** (e.g. print out a greeting `Hello World`).

Always think about what your program does in terms of input, output, behaviour!

Testing is extremely important, and beginners often underestimate how much time and effort is required for good testing. In this case the test is easy and can be done by a human directly. Does the output text match exactly the required text? You will learn more about unit testing in CMPT 125.


## Practice 01

**REQUIREMENT**: you will write a C program to file `p1.c`; can you modify the example code in [C syntax](#c-syntax) to get the following output?

```
Hello world
How are you?
```

**TESTING**: you can test your program by running:
```
$ make p1
$ ./p1
```

Try it yourself first; then verify your solutions [here](./files/solution/p1.c).


    

# Variables

Variables are the basic building blocks of C.

## Guide

There are 4 things that define a variable: 
1. a **data type** of the value assigned to the variable (the computer determines how much space in memory to allocate to your variable based on the type of data value it will store), and 
2. a **pointer** or an address indicating where in memory the variable's value is stored (we get this by prepending a `&` to the variable).
3. a **variable name**, a human readable name you give to the variable, 
4. a **value**, the value assigned to the variable (this is what functions take as input).


A variable in C is created by the `=` operator:

```C
int i = 0;
```

- `int` is a key word (a "noun" in C) that represents the data type (integer).
- `i` is the variable name you give to the variable. 
- `=` is an operator (a "verb" in C) that initializes the variable and assigns it a value.
- `0` is the value you assign to the variable.
- You can access `i`'s pointer with `&i`.


### Value data types, `sizeof`, and `printf`

C is a **strongly typed** language. This means:
- all variables have a static **type** that identifies the kind of data they store; a variable's type cannot change.
- every variable has a **value** which is the data it stores; a variable's value may change

Advantages to being **strongly typed**:
- Explicit statement of intent. You tell the compiler and people reading the code what kind of data you are manipulating.
- Error prevention at compile time. If you violate your stated intent, the compiler lets you know right away.

C has several native (i.e. predefined) variable types. They differ by the kind of value they store and by the range of possible values. Here are the most commonly used variable types in C:

`void` is a special type that means "nothing".

**floating-point types**

| Type specifiers | Precision (decimal digits) | Exponent range |
| --------------- | -------------------------- | ---------------|
| `float`         | 6                          | ±38 (8 bits)   |
| `double`        | 10                         | ±307 (11 bits) |

**integer types**

| Type specifier  | Minimum value   | Maximum value |
| --------------- | --------------- | ------------- |
| `char`          | \-127           | 127           |
| `int`           | \-32,767        | 32,767        |

A **characters** `char` uses 7 bits (bits = either 0 or 1) so it can represent 2^7 or 128 possible values. Hence, each character is represented by a unique set of numbers, see [ASCII](https://en.wikipedia.org/wiki/ASCII).

Integer and floating point types represent numbers exactly over a limited range and approximately based on the number of bits respectively. [A complete list of the native types is available at Wikipedia](http://en.wikipedia.org/wiki/C_syntax#Primitive_data_types).



**`sizeof`**

C provides a `sizeof` [operator](http://en.cppreference.com/w/c/language/sizeof) that tells you the storage size of any type in **bytes**. For example:
```C
printf( "%lu\n", sizeof(int) );
```

Results in
```C
4
```

**`scanf`**

```C
int i = 0; // integer
char c = '+'; // character
float pi = 3.14159; // floating point number

printf( "here: %d %.2f %c \n", i, pi, c);
```
Output:
```
here: 0 3.14 + 

```

`printf` allows you to print all the native variable types. Using `printf` is similar to using the `%` idiom in Python's `print` function. `printf` is less flexible about its input than Python's `print`, but you can do a lot with it. For floating point numbers, you can specifiy the precision at which the number is printed by adding `.2` with `2` being the number of decimal points ot print to `%f` \> `%.2f`.

### Standard fixed-size integer types

`sizeof(int)` or the number of bytes an integer requires in memory varies with machine architecture. Therefore, it is often useful to specify a standard set of sizes for your variables exactly. This way, your code will use predictable variable sizes no matter which machine you run it on.

The header file `stdint.h` (add `#include <stdint.h>` to use this!) defines a set of sized integer variable types for you:

```
 int32_t     (32 bit signed int)
uint32_t     (32 bit unsigned int)
 int64_t     (64 bit signed int)
uint64_t     (64 bit unsigned int)
  int8_t     (8 bit signed int)
 uint8_t     (8 bit unsigned int)
```

In this lab we will use `uint8_t` in place of its exact equivalent `unsigned char` for brevity. Note it is C convention that the suffix `_t` denotes a type.

See [C data types](https://en.wikipedia.org/wiki/C_data_types) for more details.

### Arithmetic expressions

```C
int a = 2;
int b = 10;

// a
// a+b // addition
// a*(b+c) // multiplication
// a*sqrt(b) // square root
// a/b

printf( "the product of a and b equals %d\n", a*b );
```

An expression in C is a sequence of variables, operators and function calls. The following are valid simple expressions.

The result of any given expression is always a value with a type. This means that an expression can be used anywhere a value is expected, such as following the format string in a call to printf. For example, the following is valid


### Pointers and `scanf`

The **pointer** of a variable is the address to where things are stored in memory. Each byte of memory has a unique numeric address, numbered from 0 to the size of the space. For example, if your memory is 4GB, it has around 2^64 or 4.3 billion bytes. Every address contains a single value from 0 to 2^8 (255).

REMINDER: a bit is a 0 or 1, a byte is 8 bits.

When you declare a variable, e.g. `char c = 42;`, the compiler chooses an unused address to contain it, e.g.`4`, then writes the initial value `42` into the memory at that address i.e. `c`'s
- variable name is `c`,
- value is `42`, and
- pointer address is `4`.

If your value is larger than 2^8, the compiler allocates a sequence of addresses and gives the variable the lowest-numbered address of this sequence.

Python and many other 'high level' languages have different storage models and you rarely have to think about them. That's part of what 'high level' means. C allows/requires you to think about data storage more directly. Many languages, e.g., Java, do not allow you to use pointers, and have references instead. These are implemented internally as pointers, with an extra little safety net limiting how you use them. C has only pointers, for simplicity. C++ has both pointers and references.

Now let's look at a C program that reads user inputs as an integer and echoes it back.

```C
#include <stdio.h>

int main(void) {
    int i = 0; // 0 is just a placeholder value

    printf("Enter an integer: ");

    scanf("%d", &i); // scanf(<"type of input">, <the memory address, i.e. pointer, where scanf should put the input value into>)
    printf("Your integer was: %d\n", i);

    return 0;
}
```

`scanf` is roughly the inverse of `printf`; it reads text from **standard input** `stdin` and assigns it to a variable.
- argument 1 type string e.g. `%d`: this is the format string argument that tells `scanf` that it should interpret the user input as a decimal integer. Whitespace is ignored.
- argument 2 address in memory where it will store user input e.g. `&i`: arguments to functions are **passed by value** (recall, `printf` has always printed the **value** of our variables); however, if we give `scanf` `i`, it will see `0` which isn't an address in memory! So we prepend `i` with a `&` to get `i`'s pointer, the address in memory where we are currently storing `0`, and tell `scanf` to replace this value of `i` with the user input.

**Syntax rules: value vs pointer**:

| Syntax             | Example | Value or pointer | Comment           |
|--------------------|---------|------------------|-------------------|
| `<variable name>`  | `i`     | value            | By default we pass the value of a variable to a function. |
| `&<variable name>` | `&i`    | pointer          | Putting a `&` in front of your variable gets you its |
| `*<pointer>`       | `*(&i)` | value            | Putting a `*` in front of your pointer gets you the value stored at the location in memory where the pointer points to. |

## Practice 02.1

**REQUIREMENT**: 
- Answer the following question. What happens if we remove the `&` from `&i`? Why do you think that happens? 
- Use C program `p2.1.c` to verify your answer.

<details>
<summary style="margin-left: 25px;">Try it yourself first; then verify your solutions here.</summary>
<div style="margin-left: 25px;">

If we do omit the `&` before the argument `i` we get an error message because `scanf` is expecting a pointer not a value.
```C
int i = 0;
scanf("%d", i); // ERROR!
```

</div>
</details>

## Practice 02.2

**REQUIREMENT**: Answer the following question. What does the following code output? Do you understand the output?
- Use C program `p2.2.c` to verify your answer.
- Add comments on the code to document what the code is doing!

```C
#include <stdio.h>

int main(void) {
    // ADD COMMENT HERE
    float i = 0.0;
    float j = 1.0;
    float k = 2.0;
    
    // ADD COMMENT HERE
    printf("give me an integer: \n");
    scanf("%f", &i);
    
    // ADD COMMENT HERE
    printf("the value of i is %.2f, its pointer points to address in memory %p\n", i, &i);
    printf("the value of j is %.1f, its pointer points to address in memory %p\n", j, &j);
    printf("the value of k is %.0f, its pointer points to address in memory %p\n", k, &k);
    
    return 0;
}
```

<details>
<summary style="margin-left: 25px;">Try it yourself first; then verify your solutions here.</summary>
<div style="margin-left: 25px;">

The code outputs the values and pointers of variables `i`, `j`, and `k`; the value of `i` was replaced by the user input because we gave the pointer of `i` to `scanf`. It went to the pointer address we provided and replaced what was at that address, `i`'s value `0.0`, with the user input.

</div>
</details>







# Conditions and loops
## Guide

### `if`/`else` conditions

Humans often use decision trees to determine the right course of action. Decision trees can be framed as an if/else statement. For example, if it is raining outside, I will wear a rain coat, else I won't.

To embed decision making and condition handling in software, we use the `if`/`else` statements

C's basic conditional is `if` and it has the form:

```C
if (<statement>) {
    // this block is executed if and only if <statement> evaluates to true (non zero)
} 
```
    
For example:

```C
int s = 96;
int highscore = 95;

if (s > highscore) {
    highscore = s;
    printf( "Congratulations on a new high score!\n" );
}
```

An optional `else if` and `else` block can be added that will run only if the condition is false. Thus you can choose between two courses of action, for example:

```C
int s = 96;
int highscore = 95;

if (s > highscore) {
    highscore = s;
    printf( "Congratulations on a new high score!\n" );
} else if (s == highscore) {
    printf("Ok!\n");
} else {
    printf( "Bad luck. Try again\n" );
}
```

### Infix operators

`>` and `==` are examples of **infix** comparison operators and can be put between variables to evaluate their relationship with each other.

These comparisons are statements that give our `if`/`else if`/`else` statements a **Boolean** value: true (non-0), false (0)

| name                     | syntax     |
| ------------------------ | ---------- |
| equal to                 | \==        |
| not equal to             | !=         |
| less than                | <          |
| greater than             | \>         |
| less than or equal to    | <=         |
| greater than or equal to | \>=        |
| not                      | !          |

Notice the **equal to** operator "==" is distinct from the assignment operator "=" . Mixing these up is a common bug for C beginners. Double-check every time you intend to use "==".


### Loops

Let's extend `scanf` to handle any numer of inputs. For this we need to repeat part of our program to deal with each value that comes. We need a **conditional loop**. C has only two options: while and for.

    

#### `while` loops

The while keyword has the following form:

```C
while (/*condition*/) {
    // this block executes repeatedly as long as condition evaluates to true
}
 ```     


For example this code

```
int i = 0;

while (i < 6) { 
    printf( "%d ", i ); 
    i++; // ++ is an increment operator that is a shorthand for i = i + 1
    // i-- is a decrement operator that is a shorthand for i = i - 1
}

printf( "\n" );
```

and (almost) equivalently

```C
int i = 0; 
while (!(i == 6)) { 
    printf( "%d ", i ); 
    i++; 
} 
printf( "\n" );
```

produces the output

```
0 1 2 3 4 5
```

The repeating block of code is contained in curly braces `{ ... }` the same as with the conditional structure we saw earlier.

#### `do`/`while` loops

If the while condition is false on the first evaluation, the body of the loop is never executed; to ensure that at least one execution of the loop is done, we can alternatively use `do`/`while`:

```C
do    {
    // this block executes at least once, 
    // then repeats as long as
    // condition evaluates true
} while (/*condition*/);
```

For example this code

```C
int i = 0; 
do { 
    i++;
} while (i <= 1000);
```


DANGER: if `i` never becomes equal or greater than `1000`, this program will happily run forever D:!


#### `for` loops

The pattern above, where we initialize a variable, test its value, then perform a loop that changes the value, is so frequently used that it has a special syntax: the **for loop**, which has the form

```C
for(/*initialize*/; /*condition*/; /*modify*/) {
    // this code runs until condition evaluates to false 
}
```
        
Any valid C expression can be used in each of the three for() components, separated by semicolons. But they are usually quite simple. For example:
```C
for (int i=0; i<6; i++) { 
    printf("%d ", i);
} 
printf("\n");
```
is functionally identical to our first while example.

Every for loop has an equivalent while, and _vice versa_, so choose whichever is neatest for the loop at hand.


#### `break` and `continue`

```C
for (int i=0; i<105; i++) { 
    if (i == 100) {
        break;
    }
    printf("%d ", i++); // prints the value and THEN increments it
}
```

You can break out of a loop body with the break; statement. For example, the code above will print integers in sequence from 0, but has a 1% chance of leaving the loop every time around. The function random() returns a random integer and the % operator is the integer modulus operator, so the code will print consecutive numbers up to 999 or until random() returns a multiple of 100, whichever comes sooner.


```C
for (int i=0; i<105; i++) {
    if (i == 100) {
        continue;
    }
    printf("%d ", i++); // prints the value and THEN increments it 
}
```

You can jump to the beginning of a loop body with the continue; statement. For example, the code above will print integers of increasing value, but every loop iteration has has a 1% chance of jumping to the beginning of the loop without printing. Thus this code will continue to loop until it reaches 1000, but might skip a few numbers.




## Practice 03

**REQUIREMENT**: you will write a C program to file `p3.c`. In it, re-write the previous example without using `continue`.

**TESTING**: you can test your program by running:
```
$ make p3
$ ./p3
```

Try it yourself first; then verify your solutions [here](./files/solution/p3.c).





# Putting it all together: more practice with `scanf` (READ HINTS!)

## Practice 04

**REQUIREMENT**: you will write a program to file `p4.c`. 
- INPUT: `p4.c` should read an arbitrary number of positive integer values separated by a space using `scanf`.
    - You may assume that the inputs are well-formed. 
- OUTPUT: `p4.c` should, on standard output, render a simple graph representation of the input values, in order, using hash `#` characters as shown in the examples below.
    - The number of hashes printed should be equal to the input value.
    - Your program should output exactly one line per input value.

**TESTING**: you can test your program by running:
```
$ make p4
$ ./p4
```

**HINT**: did you know that if `scanf`is looking for a series of integers separated by a space as input? You can directly input `1 3 5 6`, press enter, and `scanf` will help you loop through each integer. Try it out below!

```C
#include <stdio.h>

int main(void) {
    // initialize while loop variable
    int j = 0;
    
    // promt for input
    printf("Enter integers separated by space and press enter:\n");
    
    // while the user does not end i.e. ctrl-d; print loop variable
    while (scanf("%d", &j) == 1) { // remember, 1 means true, 0 means false! True here meaning that scanf is still reading user inputs :)
        printf("%d", j);
    }
    return 0;
}
```

`scanf` keeps going until you press `ctrl-d`, so press `ctrl-d` to stop the program.

**EXAMPLE**: 

Example `scanf` user input and `printf` output:

```
Enter integers separated by space and press enter:
5 3 3 7 1

Output:
#####
###
###
#######
#
```

Try it yourself first; then verify your solutions [here](./files/solution/p4.c).


# Bonus material: C vs C++

C is a subset of C++; all C functions/keywords/code will work with a C++ compiler. In this section, we go over some functions/keywords that are analagous to each other in C and C++.

Let's look at how C and C++ read/write to standard output.

|                  | C                                      | C++              |
|------------------|----------------------------------------|------------------|
| Function/keyword | `printf`                               | `std::cout`      |
| Example          |`printf("This is the number 1: %d", i);`| `std::cout << "This is the number 1: " << i;` |
| | | |
| Function/keyword | `scanf`                                | `std::cin`       |
| Example          | `scanf("%d%", &i);`                    | `std::cin >> i;  |
| | | |
| Comments         | Data types are explicit.               | Handles all data types without needing to state them. Always use this in C++. |

# Bonus material: for your enjoyment

## What does a compiler do?

Invoking the compiler `gcc` on the source code file `t1.c` did the following things:

- First the **C preprocessor** runs. It scans the file manipulating its text; mainly removing comments and newlines and **expanding macros**. C **Macros** are preprocessor instructions beginning with a hash symbol `#`. The preprocessor replaces each macro with the results of the macro, which is always text. `#include` is a macro which causes the entire line it sits on to be replaced by the contents of the named file. Following the preprocessor run, we now have an intermediate C file that contains no comments or macros.
- Next the **C compiler** program runs and translates the C source code into assembler code that is specific to your CPU type. To see that this is so, let's ask the compiler to stop after this stage and take a look at the assembly generated for our program:

```
$ gcc -S t1.c
```                
        
- This produces a file called `t1.s` which you can view using `less t1.s` that contains the assembly output. Let's look at the assembly output for our hello world program.

```C
    	.file	"t1.c"
    	.text
    	.section	.rodata
    .LC0:
    	.string	"Hello World!"
    	.text
    	.globl	main
    	.type	main, @function
    main:
    .LFB0:
    	.cfi_startproc
    	pushq	%rbp
    	.cfi_def_cfa_offset 16
    	.cfi_offset 6, -16
    	movq	%rsp, %rbp
    	.cfi_def_cfa_register 6
    	leaq	.LC0(%rip), %rdi
    	call	puts@PLT
    	movl	$0, %eax
    	popq	%rbp
    	.cfi_def_cfa 7, 8
    	ret
    	.cfi_endproc
    .LFE0:
    	.size	main, .-main
    	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
    	.section	.note.GNU-stack,"",@progbits
```

- Looking at this assembly, you can see why C and other high level languages were invented. They are a lot easier for humans to read and write. C and C++ have proven themselves to be at a sweet spot between human usuability and the efficiency of their code at run-time. At this point we still have a text representation of our program, now in a different language. The computer can not run it yet.

- The next step is to translate the assembly representation into the binary format that the computer can read directly. This is now a sequence of numbers, each representing either a datum value, a memory address, or an actual CPU operation to perform (**opcode**). This is no longer readable by most humans, but it is a direct translation of the assembly so you can translate back and forth if needed.
    
- The program is now a chunk of binary data called an **object**, and the compiler writes it to a file in called an **object file** `t1`, so `t1.c` creates `t1`. If multiple source files were compiled, each gets its own object file.
    
- To see this happening, we can ask the compiler to stop at the object stage:

```
$ gcc -c t1.c
```
        
- The working directory will contain the file `t1`. Opening this in an editor, you will see a lot of unreadable stuff, with some familiar bits here and there, such as the string "Hello World" which is stored in the object as data. You'll also see the function names `main` and `printf` which are kept around in human-readable form in case we want to debug the program as it runs.
        
- The final stage is to **link** together all the object files, along with any code libraries they referenced, to create the complete executable program. Code libraries are just collections of object files all smooshed together with an index at the start. (Object files are often small and numerous, so collecting them simplifies distribution).
        
- Invoking the compiler with our object file will do the link to create a new executable called `t1` in the current directory:

```
$ gcc -o t1 t1
```

Now you have seen a typical C compiler process from start to finish. In practice you will almost always let the compiler do the whole thing at once for you. It deletes the intermediate files when it's finished with them, so you won't even see them unless you look hard.

## Note on variable size

C provides a `sizeof` [operator](http://en.cppreference.com/w/c/language/sizeof) that tells you the storage size of any type in bytes. For example:
```C
printf( "%lu\n", sizeof(int) );
```

Results in
```
4
```        

on my machine. Note this is larger than the minimum 2 bytes required by the standard. This is because the architecture of my machine handles data in 4-byte chunks more efficiently than 2-byte chunks.

The `printf` format string contained the `%lu` format specifier, which prints a unsigned long integer type. I chose this format because on my 64-bit machine `sizeof` outputs an unsigned long (storage size can only be positive). If you are using a 32-bit operating system, you might need to use "%u" instead of "%lu". The compiler will complain if you have the wrong format.

`sizeof` also accepts a variable name for its argument. It figures out the type automatically
```C
unsigned int a=73;
printf( "%u %lu\n", a, sizeof(a) );
```

Results in
```
73 4
```

Note, there are usually 8 bits in a byte. The number of bits in a byte on your machine is defined in the file `limits.h` in the variable `CHAR_BIT`

```C
#include <stdio.h>
#include <limits.h>

int main(void) {
    printf("number of bits in a byte: %d\n", CHAR_BIT);
}
```
Do not be tempted to just print the example output. Your code might be tested on a very weird machine.

As reminder, here's an example of building and running your new program

```
$ gcc -o sz t2.c
$ ./sz
8 8 32 32 64 64 32 64 128
```    

## Additional arithmetic functions

You can access for arthimetic functions by including the `math.h` file and its function in the header:

```C
#include <stdio.h>
#include <math.h>
```

`math.h` includes functions such as `floor`, `ceil`, and `round` that return the floor, ceiling, and rounded integer of a given value.

## EOF: the end of the file

One of the most powerful ideas behind the design of the UNIX operating system and environment is that ["everything is a file"](http://en.wikipedia.org/wiki/Everything_is_a_file). Since stdin behaves like a file, it can have an "end". The shell program connects your typed input to your program's stdin. We can break this connection by typing the special character sequence `Ctrl-d`, The shell receives this command, sends a special "End-of-file" or **EOF** indicator to the connected stdin, and then closes the connection.

Inside the running program, the EOF indicator is detected by input functions such as `scanf`. `scanf` will return an integer with a special value to indicate EOF. This is often -1, but the actual value depends on your system. The standard library defines the symbol "EOF" which has the correct value for your system. You can use it like so:
```C
int i=0; 
int result = scanf("%d", &i); 
if (result == EOF) { // note double-equals for comparison! 
        printf( "End of file detected\n" ); 
}
```
By definition, once an EOF is seen in an input stream, any subsequent read will also return EOF.

We can use the combination of conditional loops and EOF indicator to make the rounding program work for an arbitrary number of input values.


## Good reads

- [Beginners guide to using the Linux terminal](http://linuxcommand.org)
- [A concise introduction to C by W3school](https://www.w3schools.in/c-tutorial/intro/).


# Credit

Last updated 2021-05 by Alice Yue. 

Course material designed, developed, and initially taught by [Prof. Richard Vaughan](https://rtv.github.io/); this material has since been taught and adapted by Anne Lavergn, Victor Cheung, and others.
