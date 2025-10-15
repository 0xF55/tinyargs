#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PVOID StrArg(CHAR* def) {
		
	StringArg* arg = (StringArg*)malloc(sizeof(StringArg));
	if (arg == NULL) {
		return NULL;
	}
	arg->default_value = def;
	arg->value = NULL;
	return (PVOID)arg;

}

PVOID IntegerArg(INT def) {

	IntArg* arg = (IntArg*)malloc(sizeof(IntArg));
	if (arg == NULL) {
		return NULL;
	}
	arg->default_value = def;
	arg->value = 0;
	return (PVOID)arg;

}

PVOID BooleanArg(BOOL def) {

	BoolArg* arg = (BoolArg*)malloc(sizeof(BoolArg));
	if (arg == NULL) {
		return NULL;
	}
	arg->default_value = def;
	arg->value = FALSE;
	return (PVOID)arg;

}

Argument* NewArgument(CHAR* Flag, CHAR* Usage, PVOID Arg, CHAR Type,ArgTable* Table) {

	Argument* pArg = (Argument*)malloc(sizeof(Argument));
	if (pArg == NULL || Flag == NULL || (strcmp(Flag,"") == 0)) {
		return NULL;
	}
	pArg->Flag = Flag;
	pArg->Arg = Arg;
	pArg->Type = Type;
	pArg->Usage = Usage;
	pArg->UseDefault = TRUE;
	pArg->Next = NULL;

	if (Table->Node == NULL) {
		Table->Node = pArg;
		Table->LastNode = pArg;
	}
	else {
		Table->LastNode->Next = pArg;
		Table->LastNode = pArg;
	}

	return pArg;

}

Argument* FindArgument(ArgTable* argTable, CHAR* flag) {
	Argument* node = argTable->Node;

	if (node == NULL) {
		return NULL;
	}


	while (node != NULL) {
		if ((strcmp(node->Flag, flag) == 0)) {
			return node;
		}
		node = node->Next;
	}
	return NULL;
}

void InitArgTable(ArgTable* argTable,CHAR** Argv,INT Argc) {
	argTable->Argv = Argv;
	argTable->Argc = Argc;
	argTable->Node = NULL;
	argTable->LastNode = NULL;
}

#define COLOR_RESET   "\x1b[0m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_CYAN    "\x1b[36m"

void Usage(ArgTable* table) {
	printf(COLOR_CYAN "Usage: %s [OPTIONS]\n\n" COLOR_RESET, table->Argv[0]);
	Argument* Node = table->Node;
	while (Node) {
		printf("  " COLOR_YELLOW "%-5s" COLOR_RESET "  %-20s", Node->Flag, Node->Usage);
		switch (Node->Type) {
		case ARG_STRING:
			printf("[default: %s]\n", ((StringArg*)Node->Arg)->default_value ?
				((StringArg*)Node->Arg)->default_value : "None");
			break;
		case ARG_INT:
			printf("[default: %d]\n", ((IntArg*)Node->Arg)->default_value);
			break;
		case ARG_BOOL:
			printf("[default: %s]\n", ((BoolArg*)Node->Arg)->default_value ? "true" : "false");
			break;
		}
		Node = Node->Next;
	}
	printf("\n");
}

/*
	Get string argument value
*/
CHAR* GetStrArg(ArgTable* table, CHAR* flag) {
	Argument* node = FindArgument(table, flag);
	if (!node || node->Type != ARG_STRING) {
		return NULL;
	}

	StringArg* arg = (StringArg*)node->Arg;
	return node->UseDefault ? arg->default_value : arg->value;
}

/*
	Get integer argument value
*/
INT GetIntArg(ArgTable* table, CHAR* flag) {
	Argument* node = FindArgument(table, flag);
	if (!node || node->Type != ARG_INT) {
		return 0;
	}

	IntArg* arg = (IntArg*)node->Arg;
	return node->UseDefault ? arg->default_value : arg->value;
}

/*
	Get boolean argument value
*/
BOOL GetBoolArg(ArgTable* table, CHAR* flag) {
	Argument* node = FindArgument(table, flag);
	if (!node || node->Type != ARG_BOOL) {
		return FALSE;
	}

	BoolArg* arg = (BoolArg*)node->Arg;
	return node->UseDefault ? arg->default_value : arg->value;
}
