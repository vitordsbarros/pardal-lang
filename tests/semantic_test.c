
#include <stdio.h>

#include "ast.h"
#include "semantic.h"
#include "symbol_table.h"

int main(void)
{
    SymbolTable table;
    symbol_table_init(&table);

    /* Teste 1: declaracao e atribuicao de variavel */
    ASTNode *declaration = ast_new_variable_declaration(
        "idade",
        AST_TYPE_INT,
        ast_new_integer(20));

    if (declaration == NULL ||
        !semantic_analyze(declaration, &table))
    {
        fprintf(stderr, "Falha ao declarar a variavel.\n");
        ast_free(declaration);
        symbol_table_free(&table);
        return 1;
    }

    ast_free(declaration);

    ASTNode *assignment = ast_new_assignment(
        "idade",
        ast_new_integer(25));

    if (assignment == NULL ||
        !semantic_analyze(assignment, &table))
    {
        fprintf(stderr, "Falha ao atribuir valor a variavel.\n");
        ast_free(assignment);
        symbol_table_free(&table);
        return 1;
    }

    ast_free(assignment);

    const Symbol *symbol = symbol_table_find(&table, "idade");

    if (symbol == NULL || symbol->integer_value != 25)
    {
        fprintf(stderr, "O valor da variavel nao foi atualizado corretamente.\n");
        symbol_table_free(&table);
        return 1;
    }

    printf(
        "Teste concluido: atribuicao atualizou idade para %ld.\n",
        symbol->integer_value);

    /* Teste 2: rejeitar atribuicao de tipo incompativel */
    ASTNode *invalid_assignment = ast_new_assignment(
        "idade",
        ast_new_string("vinte e cinco"));

    if (invalid_assignment == NULL)
    {
        fprintf(stderr, "Falha ao criar atribuicao invalida.\n");
        symbol_table_free(&table);
        return 1;
    }

    if (semantic_analyze(invalid_assignment, &table))
    {
        fprintf(stderr, "Erro: foi aceita uma string em uma variavel int.\n");
        ast_free(invalid_assignment);
        symbol_table_free(&table);
        return 1;
    }

    ast_free(invalid_assignment);

    printf("Teste concluido: atribuicao com tipo incompativel rejeitada.\n");

    /* Teste 3: inicializar uma constante inteira */
    ASTNode *constant_declaration = ast_new_constant_declaration(
        "limite",
        AST_TYPE_INT,
        ast_new_integer(100));

    if (constant_declaration == NULL ||
        !semantic_analyze(constant_declaration, &table))
    {
        fprintf(stderr, "Falha ao declarar a constante inteira.\n");
        ast_free(constant_declaration);
        symbol_table_free(&table);
        return 1;
    }

    ast_free(constant_declaration);

    symbol = symbol_table_find(&table, "limite");

    if (symbol == NULL ||
        !symbol->is_constant ||
        symbol->integer_value != 100)
    {
        fprintf(stderr, "A constante nao foi inicializada corretamente.\n");
        symbol_table_free(&table);
        return 1;
    }

    printf(
        "Teste concluido: constante limite inicializada com %ld.\n",
        symbol->integer_value);

    /* Teste 4: impedir alteracao da constante */
    ASTNode *constant_assignment = ast_new_assignment(
        "limite",
        ast_new_integer(200));

    if (constant_assignment == NULL)
    {
        fprintf(stderr, "Falha ao criar atribuicao para a constante.\n");
        symbol_table_free(&table);
        return 1;
    }

    if (semantic_analyze(constant_assignment, &table))
    {
        fprintf(stderr, "Erro: foi permitida a alteracao de uma constante.\n");
        ast_free(constant_assignment);
        symbol_table_free(&table);
        return 1;
    }

    ast_free(constant_assignment);

    symbol = symbol_table_find(&table, "limite");

    if (symbol == NULL || symbol->integer_value != 100)
    {
        fprintf(stderr, "Erro: o valor da constante foi alterado.\n");
        symbol_table_free(&table);
        return 1;
    }

    printf("Teste concluido: alteracao da constante rejeitada.\n");

    symbol_table_free(&table);
    return 0;
}
