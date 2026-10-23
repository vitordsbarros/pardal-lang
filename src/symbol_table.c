
#include <stdlib.h>
#include <string.h>

#include "symbol_table.h"

void symbol_table_init(SymbolTable *table)
{
    if (table == NULL)
    {
        return;
    }

    table->symbols = NULL;
    table->count = 0;
    table->capacity = 0;
}

void symbol_table_free(SymbolTable *table)
{
    if (table == NULL)
    {
        return;
    }

    for (int i = 0; i < table->count; i++)
    {
        free(table->symbols[i].name);
    }

    free(table->symbols);

    table->symbols = NULL;
    table->count = 0;
    table->capacity = 0;
}

const Symbol *symbol_table_find(
    const SymbolTable *table,
    const char *name)
{
    if (table == NULL || name == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < table->count; i++)
    {
        if (strcmp(table->symbols[i].name, name) == 0)
        {
            return &table->symbols[i];
        }
    }

    return NULL;
}

int symbol_table_add(
    SymbolTable *table,
    const char *name,
    ASTType type,
    int is_constant)
{
    if (table == NULL || name == NULL || type == AST_TYPE_INFERRED)
    {
        return 0;
    }

    if (symbol_table_find(table, name) != NULL)
    {
        return 0;
    }

    if (table->count == table->capacity)
    {
        int new_capacity = table->capacity == 0
                               ? 4
                               : table->capacity * 2;

        Symbol *new_symbols = realloc(
            table->symbols,
            (size_t)new_capacity * sizeof(*new_symbols));

        if (new_symbols == NULL)
        {
            return 0;
        }

        table->symbols = new_symbols;
        table->capacity = new_capacity;
    }

    size_t length = strlen(name) + 1;
    char *name_copy = malloc(length);

    if (name_copy == NULL)
    {
        return 0;
    }

    memcpy(name_copy, name, length);

    Symbol symbol;
    symbol.name = name_copy;
    symbol.type = type;
    symbol.is_constant = is_constant;
    symbol.integer_value = 0;

    table->symbols[table->count] = symbol;
    table->count++;

    return 1;
}

int symbol_table_set_integer(SymbolTable *table, const char *name, long value)
{
    if (table == NULL || name == NULL)
    {
        return 0;
    }

    for (int i = 0; i < table->count; i++)
    {
        Symbol *symbol = &table->symbols[i];

        if (strcmp(symbol->name, name) == 0)
        {
            if (symbol->type != AST_TYPE_INT || symbol->is_constant)
            {
                return 0;
            }

            symbol->integer_value = value;
            return 1;
        }
    }

    return 0;
}

int symbol_table_initialize_integer(
    SymbolTable *table,
    const char *name,
    long value)
{
    if (table == NULL || name == NULL)
    {
        return 0;
    }

    for (int i = 0; i < table->count; i++)
    {
        Symbol *symbol = &table->symbols[i];

        if (strcmp(symbol->name, name) == 0)
        {
            if (symbol->type != AST_TYPE_INT)
            {
                return 0;
            }

            symbol->integer_value = value;
            return 1;
        }
    }

    return 0;
}