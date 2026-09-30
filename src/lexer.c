#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../include/lexer.h"

Token next_token(const char **src) {
    Token token;
    token.value[0] = '\0';

    // Ignora espaços em branco, tabulações, quebras de linha e caracteres de controle
    while (**src == ' ' || **src == '\t' || **src == '\n' || **src == '\r' || ((unsigned char)**src < 32 && **src != '\0')) {
        (*src)++;
    }

    // Se atingiu o fim do texto
    if (**src == '\0') {
        token.type = TOKEN_EOF;
        strcpy(token.value, "EOF");
        return token;
    }

    char c = **src;
    if (c == '(') { (*src)++; token.type = TOKEN_LPAREN; strcpy(token.value, "("); return token; }
    if (c == ')') { (*src)++; token.type = TOKEN_RPAREN; strcpy(token.value, ")"); return token; }
    if (c == '{') { (*src)++; token.type = TOKEN_LBRACE; strcpy(token.value, "{"); return token; }
    if (c == '}') { (*src)++; token.type = TOKEN_RBRACE; strcpy(token.value, "}"); return token; }
    if (c == '[') { (*src)++; token.type = TOKEN_LBRACKET; strcpy(token.value, "["); return token; }
    if (c == ']') { (*src)++; token.type = TOKEN_RBRACKET; strcpy(token.value, "]"); return token; }
    if (c == ';') { (*src)++; token.type = TOKEN_SEMICOLON; strcpy(token.value, ";"); return token; }

    // Captura de texto entre aspas (String)
    if (c == '"') {
        (*src)++;
        int i = 0;
        while (**src != '"' && **src != '\0') {
            token.value[i++] = **src;
            (*src)++;
        }
        token.value[i] = '\0';
        if (**src == '"') (*src)++;
        token.type = TOKEN_STRING;
        return token;
    }

    // Captura de palavras-chave e identificadores alfanuméricos
    if (isalpha((unsigned char)c) || c == '_') {
        int i = 0;
        while (isalnum((unsigned char)**src) || **src == '_') {
            token.value[i++] = **src;
            (*src)++;
        }
        token.value[i] = '\0';

        // Tabela de palavras reservadas do Pardal
        if (strcmp(token.value, "class") == 0 || 
            strcmp(token.value, "String") == 0 ||
            strcmp(token.value, "void") == 0 ||
            strcmp(token.value, "private") == 0 ||
            strcmp(token.value, "protected") == 0) {
            token.type = TOKEN_KEYWORD;
        } else {
            token.type = TOKEN_IDENTIFIER;
        }
        return token;
    }

    token.type = TOKEN_UNKNOWN;
    token.value[0] = **src;
    token.value[1] = '\0';
    (*src)++;
    return token;
}