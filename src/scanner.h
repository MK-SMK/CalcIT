/*
* scanner.h -- Eingabeerkennung
*/
#ifndef SCANNER_CALCIT_
#define SCANNER_CALCIT_

#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "err.h"
#include "general.h"
#include "function.h"

typedef enum token {
    END_OF_INPUT,
    PARSE_ERR,
    NUMBER,
    BYTE32,
    B_NOT,
    VAR,
    FUNC,
    NEW_LINE,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    MOD,
    B_OR,
    B_AND,
    B_XOR,
    LSHIFT,
    RSHIFT,
    LPAREN,
    RPAREN,
    STORE,
    TOKEN_LEN
} Token;

#define getchar() (input[(inp_pos++)])
#define ungetchar() (inp_pos--)

Token nextToken(void);

extern SemanticValue tokenValue;
extern int inp_pos;
extern int not;
extern char func[MAX_INPUT + 1];

#endif