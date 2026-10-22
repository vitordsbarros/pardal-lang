#ifndef SHAWN_PARSER_H
#define SHAWN_PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct
{
    Lexer *lexer;
    Token current_token;
    int has_error;
} Parser;

void parser_init(Parser *parser, Lexer *lexer);
ASTNode *parser_parse_expression(Parser *parser);
ASTNode *parser_parse_statement(Parser *parser);

#endif