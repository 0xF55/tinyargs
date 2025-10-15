#define ARG_STRING 0
#define ARG_INT 1
#define ARG_BOOL 2


#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>   
#include <stddef.h>

/*
 * Platform Detection
 */
#if defined(_WIN32) || defined(_WIN64)
#define OS_WINDOWS 1
#else
#define OS_WINDOWS 0
#endif

typedef char                CHAR;
typedef unsigned char       UCHAR;
typedef unsigned char       BYTE;
typedef short               SHORT;
typedef unsigned short      USHORT;
typedef int                 INT;
typedef unsigned int        UINT;
typedef long                LONG;
typedef unsigned long       ULONG;
typedef int64_t             LONGLONG;
typedef uint64_t            ULONGLONG;

typedef float               FLOAT;
typedef double              DOUBLE;


#ifndef BOOL
typedef int BOOL;
#endif

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef void* PVOID;
typedef void* HANDLE;
typedef char* PCHAR;
typedef const char* PCCHAR;
typedef unsigned long       DWORD;
typedef DWORD* PDWORD;

#if OS_WINDOWS
#include <Windows.h>
#else

#define WINAPI
#define MAX_PATH 260
typedef unsigned long DWORD;
typedef unsigned int WPARAM;
typedef unsigned long LPARAM;
typedef void* LPVOID;
typedef const char* LPCSTR;
typedef char* LPSTR;
#endif



typedef struct Argument* pArgument;


typedef struct {

	CHAR* value;
	CHAR* default_value;

}StringArg;

typedef struct {
	INT value;
	INT default_value;
}IntArg;

typedef struct {
	BOOL value;
	BOOL default_value;
}BoolArg;

typedef struct Argument {
	LPCSTR Flag;
	LPCSTR Usage;
	PVOID Arg;
	CHAR Type;
	BOOL UseDefault;
	pArgument Next;
} Argument,*pArgument;

typedef struct {
	pArgument Node;
	pArgument LastNode;
	CHAR** Argv;
	INT Argc;
} ArgTable;

#endif