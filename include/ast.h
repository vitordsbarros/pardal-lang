#ifndef SHAWN_AST_H
#define SHAWN_AST_H

typedef enum
{
    AST_INTEGER,
    AST_STRING,
    AST_IDENTIFIER,
    AST_BINARY_EXPR,
    AST_ASSIGNMENT,
    AST_VARIABLE_DECLARATION,
    AST_CONSTANT_DECLARATION
} ASTNodeType;

typedef enum
{
    AST_OP_ADD,
    AST_OP_SUBTRACT,
    AST_OP_MULTIPLY,
    AST_OP_DIVIDE
} ASTOperator;

typedef enum
{
    AST_TYPE_INFERRED,
    AST_TYPE_INT,
    AST_TYPE_FLOAT,
    AST_TYPE_BOOL,
    AST_TYPE_CHAR,
    AST_TYPE_STR
} ASTType;

typedef struct ASTNode ASTNode;

struct ASTNode
{
    ASTNodeType type;
    ASTType inferred_type;

    union
    {
        long integer_value;
        char *string_value;

        struct
        {
            char *name;
        } identifier;

        struct
        {
            ASTOperator operator;
            ASTNode *left;
            ASTNode *right;
        } binary;

        struct
        {
            char *name;
            ASTNode *value;
        } assignment;

        struct
        {
            char *name;
            ASTType declared_type;
            ASTNode *value;
        } variable_declaration;

        struct
        {
            char *name;
            ASTType declared_type;
            ASTNode *value;
        } constant_declaration;
    } as;
};

ASTNode *ast_new_integer(long value);
ASTNode *ast_new_string(const char *value);
ASTNode *ast_new_identifier(const char *name);

ASTNode *ast_new_binary(
    ASTOperator operator,
    ASTNode * left,
    ASTNode *right);

ASTNode *ast_new_assignment(
    const char *name,
    ASTNode *value);

ASTNode *ast_new_variable_declaration(
    const char *name,
    ASTType declared_type,
    ASTNode *value);

ASTNode *ast_new_constant_declaration(
    const char *name,
    ASTType declared_type,
    ASTNode *value);

void ast_print(const ASTNode *node);
void ast_free(ASTNode *node);
const char *ast_type_name(ASTType type);
ASTType ast_infer_type(const ASTNode *node);
int ast_evaluate_integer(const ASTNode *node, long *result);

#endif