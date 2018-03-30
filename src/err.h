/*
* err.h -- Fehler abfangen
*/

#ifndef ERR_CALCIT_
#define ERR_CALCIT_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> //va_list
#include <assert.h>
#include <string.h>
#include "color.h"
#include "general.h"//MAX_INPUT

typedef enum err_type { E_FATAL, E_WARNING, E_PARSE, E_MAX } errType;

void err(errType error, char *msg, ...);

#endif