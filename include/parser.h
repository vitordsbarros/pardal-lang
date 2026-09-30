#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

/*
 * Struct Parser:
 * Mantém o estado da análise sintática (ponteiro do código e token atual).
 */
typedef struct {
    const char *src;
    Token current_token;
} Parser;

void parser_init(Parser *parser, const char *src);
ASTNode* parse_program(Parser *parser);

#endif // PARSER_H