/*
* function.h -- Funktionserweiterungen
*/

#ifndef FUNCTION_CALCIT_
#define FUNCTION_CALCIT_

#include <string.h>
#include <stdlib.h>
#include "general.h"
#include "err.h"
#include "main.h"

#define MAX_ARGS    10

void *malloc_argv(void);
void free_argv(void);
SemanticValue execFunc(const char *funcName);

extern char **argv;

#endif