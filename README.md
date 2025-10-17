# TinyArgs

**TinyArgs is a *lightweight* C Library For CLI Arguments Parsing**

- Features
    * Friendly Output
    * Easy Usage
    * Help Support
    * Support for *-f,--flag*
    * Tested on Windows,Linux


## Usage

``` C
#include <stdio.h>
#include "tinyargs.h"

int main(int argc,char** argv)
{
	ArgTable argTable;
	InitArgTable(&argTable,argv,argc);

    // flag "-n, or "--name" + "Usage Comment" + "Default Value" + "Argument Type" + &Argtable
	NewArgument("-n", "Your Name", StrArg("Hello World"), ARG_STRING, &argTable);
	NewArgument("--age", "Your Age", IntegerArg(5),ARG_INT,&argTable);
	NewArgument("--ismale", "Check if male", BooleanArg(FALSE),ARG_BOOL,&argTable);

	Parse(&argTable);

	printf("%s\n", GetStrArg(&argTable, "-n"));
	printf("%d\n", GetIntArg(&argTable, "--age"));
	printf("%d", GetBoolArg(&argTable, "--ismale"));

	return 0;
}
```
- *InitArgTable()* to initialize the argtable
- *NewArgument()* this function adds a new argument to the table
- **Arg()* these functions used for setting the default value for the flag
- *Parse()* to parse the flags
- *Get*Arg* these functions to get the value for a flag


### Help Output

``` shell
➜  tinyargs git:(master) ✗ ./test -h
Usage: ./test [OPTIONS]

  -s     String              [default: Hello World]
  --number  Number              [default: 5]
  -b     Boolean             [default: false]


```
