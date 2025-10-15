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

    // flag (")
	NewArgument("-s", "String", StrArg("Hello World"), ARG_STRING, &argTable);
	NewArgument("--number", "Number", IntegerArg(5),ARG_INT,&argTable);
	NewArgument("-b", "Boolean", BooleanArg(FALSE),ARG_BOOL,&argTable);

	Parse(&argTable);

	printf("%s\n", GetStrArg(&argTable, "-s"));
	printf("%d\n", GetIntArg(&argTable, "--number"));
	printf("%d", GetBoolArg(&argTable, "-b"));

	return 0;
}
```
- *InitArgTable()* to initialize the argtable
- *NewArgument()* this functions adds a new argument to the table
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
