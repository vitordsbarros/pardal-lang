
#include <stdio.h>

#include "lexer.h"

int main(void)
{
    const char *source = "lock str: nome = \"Barros;";

    Lexer lexer;
    lexer_init(&lexer, source);

    Token token;

    do
    {
        token = lexer_next_token(&lexer);

        printf(
            "Token: %d | Texto: %.*s | Linha: %zu | Coluna: %zu\n",
            token.type,
            (int)token.length,
            token.literal,
            token.line,
            token.column
        );
    } while (token.type != TOKEN_EOF);

    return 0;
}