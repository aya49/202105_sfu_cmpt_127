# Make sure your code is readable!

Please make sure you follow good coding habits while you are coding:
- indents: use consistent indenting conventions e.g. if you decide to use 2 spaces for an indent, do that across all your tasks.
- readable variable names: the name of a variable explains why you made it if it is not obvious already (likely not ;). You can also add a comment explaining what it is!
- comments at the top + inline: comments at the top is the block I give you to fill in your name, date, etc. Comments inline are comments explaining what your code does.

Regarding **input/output/description**: the input, output, and description is associated with the input, output, and behaviour of your program (remember the black box model?). There are 2 ways you can approach this:
- Program style: in a literal sense, your program and main are synonymous.
  - input: the input of your program is what you put into `int main(<<HERE>>)` i.e. your program arguments. If you expect your user to give you two random strings as program arguments, then you would put `// input: 2 strings as program argument`.
  - output: the output of your program is what you put into `<<HERE>> main()` i.e. the type of output your program returns.
  - description: the behaviour of your program. Since stream redirection is not considered a formal input output of the program, your `scanf()` and `printf()` will be described here.
- Conceptual style: conceptually, stream redirections are also inputs and outputs.
  - input: in addition to your program arguments, you would put your stream redirected inputs here too (e.g. what you `scanf()`), because that makes sense!
  - output: in addition to your program outputs, you would put your stream redirected outputs here too (e.g. what you `printf()`), because that makes sense!
  - behaviour: everything else your program does.

Program style and conceptual style input/output/description are both accepted --- remember, this is to help you start writing your program!

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