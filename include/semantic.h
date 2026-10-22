
#ifndef SHAWN_SEMANTIC_H
#define SHAWN_SEMANTIC_H

#include "ast.h"
#include "symbol_table.h"

int semantic_analyze(ASTNode *node, SymbolTable *table);

#endif
