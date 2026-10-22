
#include <stdio.h>
#include "lexer.h"

static const char *token_type_name(TokenType type)
{
    switch (type) {
        case TOKEN_INVALID:
            return "TOKEN_INVALID";

        case TOKEN_EOF:
            return "TOKEN_EOF";

        case TOKEN_IDENTIFIER:
            return "TOKEN_IDENTIFIER";

        case TOKEN_INTEGER:
            return "TOKEN_INTEGER";

        case TOKEN_ASSIGN:
            return "TOKEN_ASSIGN";

        case TOKEN_SEMICOLON:
            return "TOKEN_SEMICOLON";

        case TOKEN_PLUS:  
            return "TOKEN_PLUS";

        case TOKEN_MINUS: 
            return "TOKEN_MINUS";

        case TOKEN_MULTIPLY: 
            return "TOKEN_MULTIPLY";

        case TOKEN_DIVIDE:  
            return "TOKEN_DIVIDE";

        case TOKEN_LPAREN: 
            return "TOKEN_LPAREN";
            
        case TOKEN_RPAREN: 
            return "TOKEN_RPAREN";

        default:
            return "TOKEN_UNKNOWN";
    }
}

int main(void) {
    const char *source = "resultado = (2 + 3) * 4;";

    Lexer lexer;
    lexer_init(&lexer, source);

    Token token;

    do {
        token = lexer_next_token(&lexer);

        printf(
            "%-18s | texto: '%.*s' | linha: %zu | coluna: %zu\n",
            token_type_name(token.type),
            (int)token.length,
            token.literal,
            token.line,
            token.column
        );

    } while (token.type != TOKEN_EOF);

    return 0;
}
