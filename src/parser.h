/*
* parser.h -- Parser von CalcIT
*/
#ifndef PARSER_CALCIT_
#define PARSER_CALCIT_

#include "scanner.h"

void parseList(void);
SemanticValue parseAssign(void);
SemanticValue parseExpr(void);
SemanticValue parseTerm(void);
SemanticValue parseFactor(void);
SemanticValue parsePrimary(void);

extern double memory[26];

#endif