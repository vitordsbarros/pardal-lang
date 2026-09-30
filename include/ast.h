#ifndef AST_H
#define AST_H

/*
 * AccessModifier:
 * Modificadores de acesso para Orientação a Objetos.
 * Na linguagem Pardal, o padrão é PUBLIC quando omitido.
 */
typedef enum {
    ACCESS_PUBLIC,
    ACCESS_PRIVATE,
    ACCESS_PROTECTED
} AccessModifier;

/*
 * NodeType:
 * Tipos de nós que compõem a Árvore Sintática Abstrata (AST).
 */
typedef enum {
    NODE_CLASS_DECL,    // Declaração de classe
    NODE_FUNCTION_DECL, // Declaração de método
    NODE_PRINTL         // Instrução printl(...)
} NodeType;

/*
 * Struct ASTNode:
 * Estrutura de nó de árvore que armazena a hierarquia do código compilado/interpretado.
 */
typedef struct ASTNode {
    NodeType type;
    AccessModifier access;   // Visibilidade (Public por padrão)
    char name[256];          // Nome da classe ou método
    char string_value[256];  // Conteúdo literal para instruções como printl
    struct ASTNode *body;    // Ponteiro para o corpo interno do bloco
} ASTNode;

ASTNode* create_node(NodeType type);
void execute_ast(ASTNode *node);
void free_ast(ASTNode *node);

#endif // AST_H