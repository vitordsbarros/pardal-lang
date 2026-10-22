
#include <stdio.h>

#include "ast.h"

int main(void)
{
    ASTNode *expression = ast_new_binary(
        AST_OP_ADD,
        ast_new_integer(10),
        ast_new_binary(
            AST_OP_MULTIPLY,
            ast_new_integer(5),
            ast_new_integer(2)));

    if (expression == NULL)
    {
        fprintf(stderr, "Erro ao criar a expressao.\n");
        return 1;
    }

    long result;

    if (!ast_evaluate_integer(expression, &result))
    {
        fprintf(stderr, "Erro ao avaliar a expressao.\n");
        ast_free(expression);
        return 1;
    }

    printf("Resultado: %ld\n", result);

    ast_free(expression);

    return result == 20 ? 0 : 1;
}
