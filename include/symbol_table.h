
#ifndef SHAWN_SYMBOL_TABLE_H
#define SHAWN_SYMBOL_TABLE_H

#include "ast.h"

typedef struct
{
    char *name;
    ASTType type;
    int is_constant;
    long integer_value;
} Symbol;

typedef struct
{
    Symbol *symbols;
    int count;
    int capacity;
} SymbolTable;

void symbol_table_init(SymbolTable *table);
void symbol_table_free(SymbolTable *table);

int symbol_table_add(
    SymbolTable *table,
    const char *name,
    ASTType type,
    int is_constant);

const Symbol *symbol_table_find(
    const SymbolTable *table,
    const char *name);

int symbol_table_set_integer(
    SymbolTable *table,
    const char *name,
    long value);

int symbol_table_initialize_integer(
    SymbolTable *table,
    const char *name,
    long value);

#endif