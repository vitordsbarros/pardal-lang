#include <stdio.h>
#include <stdlib.h>
#include "../include/ast.h"

ASTNode* create_node(NodeType type) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) {
        printf("Erro [Pardal]: Falha de alocação de memória para o nó da AST.\n");
        exit(1);
    }
    node->type = type;
    node->access = ACCESS_PUBLIC; // Padrão da linguagem é público
    node->name[0] = '\0';
    node->string_value[0] = '\0';
    node->body = NULL;
    return node;
}

void execute_ast(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_CLASS_DECL:
            // Executa o corpo da classe
            execute_ast(node->body);
            break;

        case NODE_FUNCTION_DECL:
            // Executa as instruções do método
            execute_ast(node->body);
            break;

        case NODE_PRINTL:
            // Imprime a string no terminal
            printf("%s\n", node->string_value);
            break;
    }
}

void free_ast(ASTNode *node) {
    if (!node) return;
    if (node->body) free_ast(node->body);
    free(node);
}