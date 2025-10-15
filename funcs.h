#ifndef FUNCS_H
#define FUNCS_H

#include "types.h"

PVOID StrArg(CHAR* def);
PVOID IntegerArg(INT def);
PVOID BooleanArg(BOOL def);

CHAR* GetStrArg(ArgTable* argTable, CHAR* flag);
INT   GetIntArg(ArgTable* argTable, CHAR* flag);
BOOL  GetBoolArg(ArgTable* argTable, CHAR* flag);

Argument* FindArgument(ArgTable* argTable, CHAR* flag);

void InitArgTable(ArgTable* argTable, CHAR** Argv, INT Argc);
void NewArgument(CHAR* Flag, CHAR* Usage, PVOID Arg, CHAR Type, ArgTable* Table);
void Usage(ArgTable* table);

#endif