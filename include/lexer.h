#ifndef LEXER_H
#define LEXER_H

/*
 * PardalTokenType:
 * Define todas as categorias de símbolos e palavras reconhecidas pelo Lexer.
 * O prefixo "Pardal" evita conflitos de nomes com bibliotecas do sistema Windows (ex: winnt.h).
 */
typedef enum {
    TOKEN_KEYWORD,    // Palavras reservadas: class, String, void, private, protected
    TOKEN_IDENTIFIER, // Nomes definidos pelo usuário (classes, métodos, variáveis)
    TOKEN_STRING,     // Literais de texto entre aspas ("...")
    TOKEN_LPAREN,     // (
    TOKEN_RPAREN,     // )
    TOKEN_LBRACE,     // {
    TOKEN_RBRACE,     // }
    TOKEN_LBRACKET,   // [
    TOKEN_RBRACKET,   // ]
    TOKEN_SEMICOLON,  // ;
    TOKEN_EOF,        // Indicador de Fim de Arquivo (End Of File)
    TOKEN_UNKNOWN     // Qualquer caractere não reconhecido
} PardalTokenType;

/*
 * Struct Token:
 * Representa a menor unidade com significado no código fonte.
 */
typedef struct {
    PardalTokenType type;
    char value[256];
} Token;

/*
 * Função next_token:
 * Lê o código fonte caractere por caractere e retorna o próximo Token encontrado.
 */
Token next_token(const char **src);

#endif // LEXER_H