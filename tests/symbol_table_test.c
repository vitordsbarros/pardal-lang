
#include <stdio.h>

#include "symbol_table.h"

int main(void)
{
    SymbolTable table;
    symbol_table_init(&table);

    if (!symbol_table_add(&table, "idade", AST_TYPE_INT, 0))
    {
        printf("Erro ao adicionar simbolo.\n");
        symbol_table_free(&table);
        return 1;
    }

    if (!symbol_table_set_integer(&table, "idade", 25))
    {
        printf("Erro ao atualizar idade.\n");
        symbol_table_free(&table);
        return 1;
    }

    const Symbol *symbol = symbol_table_find(&table, "idade");

    if (symbol == NULL)
    {
        printf("Simbolo nao encontrado.\n");
        symbol_table_free(&table);
        return 1;
    }

    printf("Nome: %s\n", symbol->name);
    printf("Tipo: %s\n", ast_type_name(symbol->type));
    printf("Constante: %s\n", symbol->is_constant ? "sim" : "nao");
    printf("Valor de idade: %ld\n", symbol->integer_value);

    
    if (!symbol_table_add(&table, "limite", AST_TYPE_INT, 1))
    {
        printf("Erro ao adicionar constante.\n");
        symbol_table_free(&table);
        return 1;
    }
    
    if (symbol_table_set_integer(&table, "limite", 100))
    {
        printf("Erro: a constante foi alterada.\n");
        symbol_table_free(&table);
        return 1;
    }
    
    printf("Teste concluido: constante protegida.\n");
    symbol_table_free(&table);
    return 0;
}
