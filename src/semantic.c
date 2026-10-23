
#include <stdio.h>

#include "semantic.h"

int semantic_analyze(ASTNode *node, SymbolTable *table)
{
    if (node == NULL || table == NULL)
    {
        return 0;
    }

    switch (node->type)
    {
    case AST_VARIABLE_DECLARATION:
    {
        const char *name = node->as.variable_declaration.name;
        ASTType declared_type = node->as.variable_declaration.declared_type;
        ASTType actual_type =
            ast_infer_type(node->as.variable_declaration.value);

        if (declared_type != AST_TYPE_INFERRED &&
            declared_type != actual_type)
        {
            fprintf(
                stderr,
                "Erro semantico: a variavel '%s' foi declarada como '%s', "
                "mas recebeu um valor do tipo '%s'.\n",
                name,
                ast_type_name(declared_type),
                ast_type_name(actual_type));

            return 0;
        }

        ASTType final_type =
            declared_type == AST_TYPE_INFERRED
                ? actual_type
                : declared_type;

        if (final_type == AST_TYPE_INFERRED)
        {
            fprintf(
                stderr,
                "Erro semantico: nao foi possivel inferir o tipo "
                "da variavel '%s'.\n",
                name);

            return 0;
        }

        if (!symbol_table_add(table, name, final_type, 0))
        {
            fprintf(
                stderr,
                "Erro semantico: a variavel '%s' ja foi declarada "
                "ou nao foi possivel registra-la.\n",
                name);

            return 0;
        }

        if (final_type == AST_TYPE_INT)
        {
            long value;

            if (!ast_evaluate_integer(
                    node->as.variable_declaration.value,
                    &value) ||
                !symbol_table_initialize_integer(table, name, value))
            {
                fprintf(
                    stderr,
                    "Erro semantico: nao foi possivel inicializar "
                    "a variavel '%s'.\n",
                    name);

                return 0;
            }
        }

        return 1;
    }

    case AST_CONSTANT_DECLARATION:
    {
        const char *name = node->as.constant_declaration.name;
        ASTType declared_type = node->as.constant_declaration.declared_type;
        ASTType actual_type =
            ast_infer_type(node->as.constant_declaration.value);

        if (declared_type != AST_TYPE_INFERRED &&
            declared_type != actual_type)
        {
            fprintf(
                stderr,
                "Erro semantico: a constante '%s' foi declarada como '%s', "
                "mas recebeu um valor do tipo '%s'.\n",
                name,
                ast_type_name(declared_type),
                ast_type_name(actual_type));

            return 0;
        }

        ASTType final_type =
            declared_type == AST_TYPE_INFERRED
                ? actual_type
                : declared_type;

        if (final_type == AST_TYPE_INFERRED)
        {
            fprintf(
                stderr,
                "Erro semantico: nao foi possivel inferir o tipo "
                "da constante '%s'.\n",
                name);

            return 0;
        }

        if (!symbol_table_add(table, name, final_type, 1))
        {
            fprintf(
                stderr,
                "Erro semantico: a constante '%s' ja foi declarada "
                "ou nao foi possivel registra-la.\n",
                name);

            return 0;
        }

        if (final_type == AST_TYPE_INT)
        {
            long value;

            if (!ast_evaluate_integer(
                    node->as.constant_declaration.value,
                    &value) ||
                !symbol_table_initialize_integer(table, name, value))
            {
                fprintf(
                    stderr,
                    "Erro semantico: nao foi possivel inicializar "
                    "a constante '%s'.\n",
                    name);

                return 0;
            }
        }

        return 1;
    }

    case AST_ASSIGNMENT:
    {
        const char *name = node->as.assignment.name;
        const Symbol *symbol = symbol_table_find(table, name);

        if (symbol == NULL)
        {
            fprintf(
                stderr,
                "Erro semantico: a variavel '%s' nao foi declarada.\n",
                name);

            return 0;
        }

        if (symbol->is_constant)
        {
            fprintf(
                stderr,
                "Erro semantico: nao e permitido alterar "
                "a constante '%s'.\n",
                name);

            return 0;
        }

        ASTType actual_type =
            ast_infer_type(node->as.assignment.value);

        if (symbol->type != actual_type)
        {
            fprintf(
                stderr,
                "Erro semantico: a variavel '%s' e do tipo '%s', "
                "mas recebeu um valor do tipo '%s'.\n",
                name,
                ast_type_name(symbol->type),
                ast_type_name(actual_type));

            return 0;
        }

        if (symbol->type == AST_TYPE_INT)
        {
            long value;

            if (!ast_evaluate_integer(
                    node->as.assignment.value,
                    &value))
            {
                fprintf(
                    stderr,
                    "Erro semantico: nao foi possivel avaliar "
                    "o valor atribuido a '%s'.\n",
                    name);

                return 0;
            }

            if (!symbol_table_set_integer(table, name, value))
            {
                fprintf(
                    stderr,
                    "Erro semantico: nao foi possivel atualizar "
                    "a variavel '%s'.\n",
                    name);

                return 0;
            }
        }

        return 1;
    }

    default:
        return 1;
    }
}
