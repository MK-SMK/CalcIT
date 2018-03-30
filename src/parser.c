/*
* parser.c -- Parser von CalcIT
*/
#include "parser.h"

Token lookahead;
double memory[26];

SemanticValue parsePrimary(void) {
    SemanticValue value;
    int bitHelper;

    if(lookahead == NUMBER || lookahead == BYTE32) {
        value.value = not == 0 ? tokenValue.value : ~(long)tokenValue.value;
        if (not != 0)
            not--;
        if(lookahead == BYTE32 && b == 2) {
            bitHelper = value.value;
            printb(&bitHelper);
        }
        lookahead = nextToken();
        
        return value;
    }

    if(lookahead == VAR) {
        value.value = not == 0 ? memory[tokenValue.index] : ~(long)memory[tokenValue.index];
        if(not != 0)
            not--;
        lookahead = nextToken();
        
        return value;
    }

    if(lookahead == LPAREN) {
        if(not > 0)
            not++;
        lookahead = nextToken();
        value = parseExpr();
        if(value.isErr == 1)
            return value;
        
        if(lookahead != RPAREN) {
            err(E_PARSE, "Schließende Klammer erwartet.");
            value.isErr = 1;
            
            return value;
        }
        lookahead = nextToken();
        not = 0;
        return value;
    }

    if(lookahead == FUNC) {
        lookahead = nextToken();
        if(lookahead != RPAREN) {
            err(E_PARSE, "Schließende Klammer erwartet.");
            value.isErr = 1;
            return value;
        }
        lookahead = nextToken();
        value.value = 1.0;    
        return execFunc(func);
    }

    err(E_PARSE, "Zahl, Variable, Funktion oder öffnende Klammer erwartet.");
    value.isErr = 1;
    
    return value;
}

SemanticValue parseFactor(void) {
    SemanticValue value;

    if(lookahead == PLUS) {
        lookahead = nextToken();
        value = parseFactor();
        
        return value;
    }

    if(lookahead == MINUS) {
        lookahead = nextToken();
        value = parseFactor();
        if(value.isErr != 1)
            value.value = -value.value;
        
        return value;
    }

    value = parsePrimary();
    return value;
}

SemanticValue parseTerm(void) {
    SemanticValue value;
    SemanticValue aux;
    unsigned int bleft, bright;
    bleft = bright = 0;

    value = parseFactor();
    if(value.isErr == 1)
        return value;
    
    while(lookahead == STAR || lookahead == SLASH || lookahead == MOD || 
          lookahead == B_AND || lookahead == B_OR || lookahead == B_XOR ||
          lookahead == LSHIFT || lookahead == RSHIFT) {
        if(lookahead == STAR) {
            lookahead = nextToken();
            aux = parseFactor();
            if(aux.isErr == 1)
                return aux;

            bleft = value.value;
            bright = aux.value;
            value.value *= aux.value;
            if(b == 1) {
                printb(&bleft);
                printb(&bright);
            }
            if(!b && x) {
                printf("0x%X\n", bleft);
                printf("0x%X\n", bright);
            }
        } else if(lookahead == SLASH) {
            lookahead = nextToken();
            aux = parseFactor();
            if(aux.isErr == 1)
                return aux;

            if(aux.value == 0.0) {
                err(E_PARSE, "Division durch 0");
                value.isErr = 1;
                return value;
            }

            bleft = value.value;
            bright = aux.value;
            value.value /= aux.value;
            if(b == 1) {
                printb(&bleft);
                printb(&bright);
            }
            if(!b && x) {
                printf("0x%X\n", bleft);
                printf("0x%X\n", bright);
            }
        } else if(lookahead == MOD) {
            lookahead = nextToken();
            aux = parseFactor();
            if(aux.isErr == 1)
                return aux;

            if(aux.value == 0.0) {
                err(E_PARSE, "Modulodivision durch 0");
                value.isErr = 1;
                return value;
            }

            bleft = value.value;
            bright = aux.value;
            value.value = (long)value.value % (long)aux.value;
            if(b == 1) {
                printb(&bleft);
                printb(&bright);
            }
            if(!b && x) {
                printf("0x%X\n", bleft);
                printf("0x%X\n", bright);
            }
        } else if(lookahead == B_AND) {
            lookahead = nextToken();
            aux = parseFactor();
            if(aux.isErr == 1)
                return aux;

            bleft = value.value;
            bright = aux.value;
            value.value = (unsigned int)value.value & (unsigned int)aux.value;
            if(b != 0) {
                if(b == 2)
                    b++;
                printb(&bleft);
                printb(&bright);
            }
            if(!b && x) {
                printf("0x%X\n", bleft);
                printf("0x%X\n", bright);
            }
        } else if(lookahead == B_OR) {
            lookahead = nextToken();
            aux = parseFactor();
            if(aux.isErr == 1)
                return aux;

            bleft = value.value;
            bright = aux.value;
            value.value = (long)value.value | (long)aux.value;
            if(b != 0) {
                if(b == 2)
                    b++;
                printb(&bleft);
                printb(&bright);
            }
            if(!b && x) {
                printf("0x%X\n", bleft);
                printf("0x%X\n", bright);
            }
        } else if(lookahead == B_XOR) {
            lookahead = nextToken();
            aux = parseFactor();
            if(aux.isErr == 2)
                return aux;
            if(aux.value > 32)
                err(E_WARNING, "Es wird empfohlen sich auf 32 zu beschränken.");

            bleft = value.value;
            bright = aux.value;
            value.value = (unsigned int)value.value ^ (unsigned int)aux.value;
            if(b != 0) {
                if(b == 2)
                    b++;
                printb(&bleft);
                printb(&bright);
            }
            if(!b && x) {
                printf("0x%X\n", bleft);
                printf("0x%X\n", bright);
            }
        } else if(lookahead == LSHIFT) {
            lookahead = nextToken();
            aux = parseFactor();
            if(aux.isErr == 1)
                return aux;
            if(aux.value > 32)
                err(E_WARNING, "Es wird empfohlen sich auf 32 zu beschränken.");

            bleft = value.value;
            bright = aux.value;
            value.value = (unsigned int)value.value << (unsigned int)aux.value;
            if(b != 0) {
                if(b == 2)
                    b++;
                printb(&bleft);
                printb(&bright);
            }
            if(!b && x) {
                printf("0x%X\n", bleft);
                printf("0x%X\n", bright);
            }
        } else if(lookahead == RSHIFT) {
            lookahead = nextToken();
            aux = parseFactor();
            if(aux.isErr == 1)
                return aux;
            if(aux.value > 32)
                err(E_WARNING, "Es wird empfohlen sich auf 32 zu beschränken.");

            bleft = value.value;
            bright = aux.value;
            value.value = (unsigned int)value.value >> (unsigned int)aux.value;
            if(b != 0) {
                if(b == 2)
                    b++;
                printb(&bleft);
                printb(&bright);
            }
            if(!b && x) {
                printf("0x%X\n", bleft);
                printf("0x%X\n", bright);
            }
        }
    }

    return value;
}

SemanticValue parseExpr(void) {
    SemanticValue value;
    SemanticValue aux;
    unsigned int bleft, bright;
    bleft = bright = 0;

    value = parseTerm();
    if(value.isErr == 1)
        return value;
    
    while(lookahead == PLUS || lookahead == MINUS) {
        if(lookahead == PLUS) {
            lookahead = nextToken();
            aux = parseTerm();
            if(aux.isErr == 1)
                return aux;

            bleft = value.value;
            bright = aux.value;
            value.value += aux.value;
            if(b == 1) {
                printb(&bleft);
                printb(&bright);
            }
            if(!b && x) {
                printf("0x%X\n", bleft);
                printf("0x%X\n", bright);
            }
        } else if(lookahead == MINUS) {
            lookahead = nextToken();
            aux = parseTerm();
            if(aux.isErr == 1)
                return aux;

            bleft = value.value;
            bright = aux.value;
            value.value -= aux.value;
            if(b == 1) {
                printb(&bleft);
                printb(&bright);
            }
            if(!b && x) {
                printf("0x%X\n", bleft);
                printf("0x%X\n", bright);
            }
        }
    }

    return value;
}

SemanticValue parseAssign(void) {
    SemanticValue value;

    value = parseExpr();
    if(value.isErr == 1)
        return value;
    
    while(lookahead == STORE) {
        lookahead = nextToken();
        if(lookahead != VAR) {
            err(E_PARSE, "Variable erwartet.");
            value.isErr = 1;
            return value;
        }
        memory[tokenValue.index] = value.value;
        lookahead = nextToken();
    }

    return value;
}

void parseList(void) {
    SemanticValue value;
    unsigned int bres;

    malloc_argv();
    lookahead = nextToken();
    while(lookahead != END_OF_INPUT && lookahead != NEW_LINE) {
            value = parseAssign();
            if(lookahead != NEW_LINE) {
                err(E_PARSE, "Zeilenumbruch erwartet.");
                return;
            }
            if(value.isErr == 1)
                return;

            if(b == 1 || b > 2) {
                bres = value.value;
                printb(&bres);
                if(b > 2)
                    b = 2;
            }
            if(!b && x)
                printf(" = %.8g (0x%X)\n", value.value, (unsigned int)value.value);
            else
                printf(" = %.8g\n", value.value);
    }
    free_argv();
}