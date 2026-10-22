
#include <stdio.h>
#include "ast.h"

int main(void)
{
    ASTNode *left = ast_new_integer(2);
    ASTNode *right = ast_new_integer(3);

    if (left == NULL || right == NULL) {
        ast_free(left);
        ast_free(right);
        fprintf(stderr, "Erro ao criar inteiros.\n");
        return 1;
    }

    ASTNode *sum = ast_new_binary(AST_OP_ADD, left, right);

    if (sum == NULL) {
        ast_free(left);
        ast_free(right);
        fprintf(stderr, "Erro ao criar a soma.\n");
        return 1;
    }

    ASTNode *four = ast_new_integer(4);

    if (four == NULL) {
        ast_free(sum);
        fprintf(stderr, "Erro ao criar o inteiro 4.\n");
        return 1;
    }

    ASTNode *expression =
        ast_new_binary(AST_OP_MULTIPLY, sum, four);

    if (expression == NULL) {
        ast_free(sum);
        ast_free(four);
        fprintf(stderr, "Erro ao criar a multiplicacao.\n");
        return 1;
    }

    ast_print(expression);
    ast_free(expression);

    return 0;
}