#include "funcs.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
    Parse() - Responsible for parsing command-line arguments
*/
BOOL Parse(ArgTable* argTable) {

    for (int i = 0; i < argTable->Argc; i++) {

        CHAR* flag = argTable->Argv[i];

        /*
            Skip invalid or short flags
        */
        if (flag[0] != '-' || strlen(flag) < 2)
            continue;

        /*
            Handle built-in help flags (-h, --help)
        */
        if (strcmp(flag, "-h") == 0 || strcmp(flag, "--help") == 0 || argTable->Argc == 1) {
            Usage(argTable);
            continue;
        }

        /*
            Find the argument node by its flag
        */
        Argument* node = FindArgument(argTable, flag);
        if (node == NULL) {
            fprintf(stderr, "[!] Unknown Flag '%s'\n", flag);
            return FALSE;
        }

        /*
            Process argument based on its type
        */
        switch (node->Type) {

            /*
                Boolean flag (no value required)
            */
        case ARG_BOOL: {
            BoolArg* boolArg = (BoolArg*)node->Arg;
            boolArg->value = TRUE;
            node->UseDefault = FALSE;
            break;
        }

                     /*
                         Integer argument (requires numeric value)
                     */
        case ARG_INT: {
            IntArg* intArg = (IntArg*)node->Arg;
            CHAR* nextarg = argTable->Argv[i + 1];

            if (nextarg != NULL && strlen(nextarg) > 0) {
                BOOL valid = TRUE;

                // Validate that argument contains only digits
                for (CHAR* c = nextarg; *c != '\0'; c++) {
                    if (!isdigit(*c)) {
                        valid = FALSE;
                        break;
                    }
                }

                if (valid) {
                    intArg->value = atoi(nextarg);
                    node->UseDefault = FALSE;
                }
                else {
                    fprintf(stderr, "[!] Invalid integer for '%s': %s\n", flag, nextarg);
                }

                i++;
            }
            break;
        }

                    /*
                        String argument (requires value)
                    */
        case ARG_STRING: {
            CHAR* nextarg = argTable->Argv[i + 1];

            if (nextarg != NULL && strcmp(nextarg, "") != 0) {
                StringArg* val = (StringArg*)node->Arg;
                val->value = nextarg;
                node->UseDefault = FALSE;
                i++;
                continue;
            }

            fprintf(stderr, "[!] Missing value for %s\n", node->Flag);
            break;
        }

                       /*
                           Unknown / unsupported argument type
                       */
        default: {
            fprintf(stderr, "[!] Unknown argument type for '%s'\n", flag);
            break;
        }
        }
    }

    return TRUE;
}
