# MINI_SI Programming Project

Creation of a basic C language for beginners.

## Requirements to execute code:
  None

## Requirements for compiling code:
  C compiler (Such as GCC provided by MSyS2)
  Any IDE to edit the code such as VSC

## Commands supported by our basic language:
  PRINT: This command prints a message to the console.
  SET: This command sets a variable to a value.
  ADD: This command performs addition between two integers.
  ISZERO: This command checks if an integer is zero.
  COMPLAIN: This command generates a generic complaint message.
  
  Other tokens like MESSAGE and ARGUMENT are used as values or arguments for the above commands.
  
  The code also handles unknown commands and prints an error message when encountered.
  
  Please note that the actual behavior of these commands depends on the specific input provided in the input file and the implementation of the functions     
  perform_complain(), perform_print(), perform_set(), perform_add(), and perform_iszero().

[BNF](https://bnfplayground.pauliankline.com/?bnf=%3Cprogram%3E%20%3A%3A%3D%20%3Cstatement%3E%20(%22%5Cn%22%20%3Cstatement%3E)*%0A%0A%3Cstatement%3E%20%3A%3A%3D%20%22PRINT%22%20%22%20%22%20%22(%22%20%3Cexpression%3E%20%22)%22%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%7C%20%22SET%22%20%22%20%22%20%22(%22%20%3Cvariable%3E%20%20%22%2C%20%22%20%3Cexpression%3E%20%22)%22%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%7C%20%22ADD%22%20%22%20%22%20%22(%22%20%3Cexpression%3E%20%22%2C%20%22%20%3Cexpression%3E%20%22)%22%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%7C%20%22SUBSTRACT%22%20%22%20%22%20%22(%22%20%3Cexpression%3E%20%22%2C%20%22%20%3Cexpression%3E%20%22)%22%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%7C%20%22MULTIPLY%22%20%22%20%22%20%22(%22%20%3Cexpression%3E%20%22%2C%20%22%20%3Cexpression%3E%20%22)%22%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%7C%20%22DIVIDE%22%20%22%20%22%20%22(%22%20%3Cexpression%3E%20%22%2C%20%22%20%3Cexpression%3E%20%22)%22%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%7C%20%22IFEQUAL%22%20%22%20%22%20%22(%22%20%3Cexpression%3E%20%22%2C%20%22%20%3Cexpression%3E%20%22)%22%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%7C%20%22IFGREATERTHAN%22%20%22%20%22%20%22(%22%20%3Cexpression%3E%20%22%2C%20%22%20%3Cexpression%3E%20%22)%22%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%7C%20%22IFLESSTHAN%22%20%22%20%22%20%22(%22%20%3Cexpression%3E%20%22%2C%22%20%3Cexpression%3E%20%22)%22%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%7C%20%22COMPLAIN%22%0A%0A%3Cexpression%3E%20%3A%3A%3D%20%3Cterm%3E%20(%20%22%2C%22%20%22%20%22%20%3Cterm%3E)*%0A%0A%3Cterm%3E%20%3A%3A%3D%20%3Cfactor%3E%0A%0A%3Cfactor%3E%20%3A%3A%3D%20%3Cvariable%3E%0A%20%20%20%20%20%20%20%20%20%20%7C%20%3Cnumber%3E%0A%20%20%20%20%20%20%20%20%20%20%7C%20%22(%22%20%3Cexpression%3E%20%22)%22%0A%20%20%20%20%20%20%20%20%20%20%7C%20%22%5C%22%22%20%3Cstring%3E%20%22%5C%22%22%0A%0A%3Cstring%3E%20%3A%3A%3D%20%3Cchar%3E*%0A%3Cchar%3E%20%20%20%3A%3A%3D%20%22%5C%5C%22%20%7C%20%22%5C%22%22%20%7C%20%22%5Cn%22%20%7C%20%3Cletter%3E%20%7C%20%22%20%22%0A%0A%3Cvariable%3E%20%3A%3A%3D%20%3Cletter%3E%2B%0A%0A%3Cnumber%3E%20%3A%3A%3D%20%3Cdigit%3E%2B%0A%0A%3Cletter%3E%20%3A%3A%3D%20%22A%22%20%7C%20%22B%22%20%7C%20%5Ba-z%5D%20%7C%20%5BA-Z%5D%0A%0A%3Cdigit%3E%20%3A%3A%3D%20%5B0-9%5D&name=)



Please note repo history can be viewed here: [Original Github Repo](https://github.com/inds123/MINI_SI)


