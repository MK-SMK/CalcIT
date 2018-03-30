/*
* main.h -- Hauptroutine
*/
#ifndef MAIN_CALCIT_
#define MAIN_CALCIT_

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <assert.h>

#include "err.h"
#include "parser.h"
#include "general.h"

#define HIST_FILE "./.calcitHist"
#define LST_SZ(l) sizeof((l)) / (l)

void show_help(char **argv);

typedef struct optEntry {
   char flag;
   char desc[MAX_DESC];
} OptEntry;

#endif