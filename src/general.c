/*
* general.c -- allgemeine Funktionen
*/
#include "general.h"

void printb(const void *value) {
    for (int i = 31; i >= 0; i--) {
        printf("%s", (*((unsigned int *)value) & (0x01 << i)) ? (B_WHT "1" C_RES) : "0");
        if (i % 4 == 0)
            printf(" ");
    }
    if(x)
        printf(" (0x%X)", *(unsigned int *)value);
    
    printf("\n");
}