/*
* general.h -- allgemeine Definitionen, Dient zum Auflösen von 
*/
#ifndef GENERAL_CALCIT_
#define GENERAL_CALCIT_

#include <stdio.h>
#include "color.h"

#define VERSION "2.8.0"
#define MAX_INPUT  80
#define MAX_ERR   120
#define MAX_DESC   80

char *input;
extern char *input;

typedef union SemanticValue {
    double value;
    int index;
    int isErr;
} SemanticValue;

/* 
* 1 = binäre Anzeige bei jeder Operation
* 2 = binäre Anzeige bei binärer Operation
*/
int b; 
extern int b;

int x; //hex ausgabe, h durch help belegt.
extern int x;

void printb(const void *value);

#endif