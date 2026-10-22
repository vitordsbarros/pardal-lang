
#include <stdio.h>

#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "semantic.h"
#include "symbol_table.h"

static int analyze_source(const char *source, SymbolTable *table)
{
    Lexer lexer;
    lexer_init(&lexer, source);

    Parser parser;
    parser_init(&parser, &lexer);

    ASTNode *root = parser_parse_statement(&parser);

    if (root == NULL || parser.has_error)
    {
        fprintf(stderr, "Erro ao analisar a instrucao.\n");
        ast_free(root);
        return 0;
    }

    int success = semantic_analyze(root, table);

    if (success)
    {
        ast_print(root);
    }

    ast_free(root);
    return success;
}

int main(void)
{
    SymbolTable table;
    symbol_table_init(&table);

    if (!analyze_source("set total = 10;", &table))
    {
        symbol_table_free(&table);
        return 1;
    }

    if (analyze_source("set total = 20;", &table))
    {
        fprintf(stderr, "Erro: a declaracao duplicada foi aceita.\n");
        symbol_table_free(&table);
        return 1;
    }

    printf("Teste concluido: declaracao duplicada rejeitada.\n");

    symbol_table_free(&table);
    return 0;
}
