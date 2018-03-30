/*
* err.c -- Fehler abfangen
*/
#include "err.h"

void err(errType error, char *msg, ...) {
    va_list args;
    char *prolog;

    assert(strnlen(msg, MAX_ERR + 1) <= MAX_ERR);

    switch(error) {
        case E_FATAL:
            prolog = B_RED "Fehler: " C_RES;
            break;
        case E_PARSE:
            prolog = B_BLU "Eingabefehler: " C_RES;
            break;
        case E_WARNING:
            prolog = B_YLW "Warnung: " C_RES;
            break;
        default:
            prolog = B_RED "Unbekannter Fehlertyp: " C_RES;
            break;
    }

    fprintf(stderr, "%s", prolog);

    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);

    fprintf(stderr, "\n");

    if(error == E_FATAL)
        exit(1);
}