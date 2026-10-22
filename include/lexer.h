#ifndef SHAWN_LEXERH
#define SHAWN_LEXERH
#include <stddef.h>


typedef enum {
    TOKEN_INVALID,
    TOKEN_EOF,
    TOKEN_IDENTIFIER,
    TOKEN_INTEGER,
    TOKEN_STRING,

    /* Palavras reservadas para declarações e tipos. */
    TOKEN_SET,
    TOKEN_LOCK,
    TOKEN_TYPE_INT,
    TOKEN_TYPE_FLOAT,
    TOKEN_TYPE_BOOL,
    TOKEN_TYPE_CHAR,
    TOKEN_TYPE_STR,

    /* Operadores e pontuação. */
    TOKEN_ASSIGN,
    TOKEN_COLON,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_SEMICOLON
} TokenType;


typedef struct {
    TokenType type; 
    const char *literal;
    size_t length;
    size_t line;
    size_t column;
} Token;

typedef struct {
    const char *source;
    size_t start;
    size_t current;
    size_t line;
    size_t column;
    size_t start_line; 
    size_t start_column; 
} Lexer;

void lexer_init(Lexer *lexer, const char *source);
Token lexer_next_token(Lexer *lexer);

#endif