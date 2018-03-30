/*
* scanner.c -- Eingabeerkennung
*/
#include "scanner.h"

int inp_pos = 0;
int not = 0;
SemanticValue tokenValue;
char func[MAX_INPUT + 1];

Token nextToken(void) {
    int c;
    double value, weight;
    int s, e, i, j, lookahead;
    unsigned char bytes[4] = {0};
    unsigned int byteConv = 0;
    char buf[MAX_INPUT];

    c = getchar();
    while(c == ' ' || c == '\t')
        c = getchar();
    
    if(c == EOF)
        return END_OF_INPUT;

    if(c == '~') {
        c = getchar();
        not = 1 - not;
    }

    /* number */
    if(c == '.' || isdigit(c)) {
        value = 0.0;
        
        while(isdigit(c)) {
            value *= 10.0;
            value += c - '0';
            
            c = getchar();
        }

        /* hex */
        if(c == 'x' || c == 'X') {
            c = getchar();
            while(isxdigit(c)) {
                if(isdigit(c)) {
                    value *= 16.0;
                    value += c - '0';

                    c = getchar();
                } else if((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) {
                    value *= 16.0;
                    value += (tolower(c) - 'a' + 10);

                    c = getchar();
                } else {
                    err(E_PARSE, "Keine gültige Hexadezimalzahl.");
                    return PARSE_ERR;
                }
            }
        } /* hex */

        if(c == '.') {
            c = getchar();
            weight = 0.1;

            while(isdigit(c)) {
                value += (c - '0') * weight;
                weight /= 10.0;

                c = getchar();
            }
        } /* decimal / int */

        /* exponent */
        if(c == 'e') {
            c = getchar();

            if(c == '+') {
                s = 1;
                c = getchar();
            } else if (c == '-') {
                s = -1;
                c = getchar();
            } else {
                s = 1;
            }

            if(!isdigit(c)) {
                err(E_PARSE, "Exponent muss eine Zahl sein.\n");
                return PARSE_ERR;
            }

            e = 0;
            while(isdigit(c)) {
                e *= 10;
                e += c - '0';
                c = getchar();
            }
            value *= pow(10, s * e);
        } /* exponent */
        ungetchar();
        tokenValue.value = value;

        return NUMBER;
    } /* number */

    /* unsigned int als bit darstellung */
    //TODO: geht das performanter?
    if(c == 'b') {
        c = getchar();
        if(c == '0' || c == '1') {
            for(i = 0; i < 4; i++) {
                for(j = 0; j < 8; j++) {
                    if(c == '0' || c == '1') {
                        bytes[i] = (*bytes << 1) | (c - '0');
                        c = getchar();
                    } else {
                        ungetchar();
                        byteConv = *(unsigned int *)bytes;
                        tokenValue.value = (double)byteConv;
                        
                        return BYTE32;
                    }
                }
            }
        } else {
            ungetchar();
        }
    }/* unsigned int als bit darstellung */
    
    /* variable oder funktion */
    if(isalpha(c)) {
        lookahead = getchar();
        if(!isalpha(lookahead)) {
            ungetchar();
            tokenValue.index = c - 'a';
            return VAR;
        } else {
            ungetchar();
            ungetchar();
            i = 0;
            while((c = getchar()) && (isalnum(c) || c == '_' || c == '(') && i <= MAX_INPUT) {
                if(c == '(') {
                    break;
                }
                func[i++] = c;
            }
            
            func[i] = '\0';

            if(i == MAX_INPUT && c != '(') {
                err(E_PARSE, "Die Funktion darf maximal %d Zeichen groß sein.", MAX_INPUT);
                return PARSE_ERR;
            }
            
            if(c != '(') {
                err(E_PARSE, "Öffnende Klammer erwartet.");
                return PARSE_ERR;
            }

            /* Argumente Parsen */
            i = 0;
            j = 0;
            while((c = getchar()) && c != '\n' && i <= MAX_INPUT && j <= MAX_ARGS) {

                while(c == ' ' || c == '\t')
                    c = getchar();

                while((isalnum(c) || c == '_' || c == '(') && i <= MAX_INPUT) {
                    buf[i++] = c;
                    c = getchar();
                }

                if(c == ',' || c == ')') {
                    buf[i] = '\0';
                    i = 0;
                    if(c == ',')
                        c = getchar();
                }
                
                strncpy(argv[j++], buf, MAX_INPUT + 1);

                if(c == ')') {
                    break;
                }
            }
            ungetchar();
            
            return FUNC;
        }
    }

    switch(c) {
        case '\n':
            return NEW_LINE;
        case '+':
            return PLUS;
        case '-':
            c = getchar();
            if(c == '>')
                return STORE;
            ungetchar();
            return MINUS;
        case '*':
            return STAR;
        case '/':
        case ':':
            return SLASH;
        case '%':
            return MOD;
        case '&':
            return B_AND;
        case '|':
            return B_OR;
        case '^':
            return B_XOR;
        case '>':
            c = getchar();
            if(c == '>')
                return RSHIFT;
            ungetchar();
            return RSHIFT;
        case '<':
            c = getchar();
            if(c == '<')
                return LSHIFT;
            ungetchar();
            return LSHIFT;
        case '(':
            return LPAREN;
        case ')':
            return RPAREN;
        default:
            err(E_PARSE, "Unbekanntes Zeichen '%c'", c);
            return PARSE_ERR;
    }

    return 0;
}