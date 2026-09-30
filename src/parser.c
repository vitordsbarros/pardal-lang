#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"

static void advance(Parser *parser) {
    parser->current_token = next_token(&(parser->src));
}

static void expect(Parser *parser, PardalTokenType type, const char *err_msg) {
    if (parser->current_token.type != type) {
        printf("Erro Sintatico [Pardal]: %s (Recebido: '%s')\n", err_msg, parser->current_token.value);
        exit(1);
    }
    advance(parser);
}

void parser_init(Parser *parser, const char *src) {
    parser->src = src;
    advance(parser);
}

ASTNode* parse_program(Parser *parser) {
    AccessModifier class_access = ACCESS_PUBLIC;

    // Modificador de acesso da classe (opcional)
    if (strcmp(parser->current_token.value, "private") == 0) {
        class_access = ACCESS_PRIVATE;
        advance(parser);
    } else if (strcmp(parser->current_token.value, "protected") == 0) {
        class_access = ACCESS_PROTECTED;
        advance(parser);
    }

    expect(parser, TOKEN_KEYWORD, "Esperada palavra-chave 'class'");

    if (parser->current_token.type != TOKEN_IDENTIFIER) {
        printf("Erro Sintatico [Pardal]: Esperado o nome da classe\n");
        exit(1);
    }

    ASTNode *class_node = create_node(NODE_CLASS_DECL);
    class_node->access = class_access;
    strcpy(class_node->name, parser->current_token.value);
    advance(parser);

    expect(parser, TOKEN_LBRACE, "Esperado '{' para abrir a classe");

    // Modificador de acesso do método (opcional)
    AccessModifier method_access = ACCESS_PUBLIC;
    if (strcmp(parser->current_token.value, "private") == 0) {
        method_access = ACCESS_PRIVATE;
        advance(parser);
    } else if (strcmp(parser->current_token.value, "protected") == 0) {
        method_access = ACCESS_PROTECTED;
        advance(parser);
    }

    // Tipo de retorno do método ('void' ou 'String')
    if (strcmp(parser->current_token.value, "void") != 0 && strcmp(parser->current_token.value, "String") != 0) {
        printf("Erro Sintatico [Pardal]: Esperado tipo de retorno 'void' ou 'String'\n");
        exit(1);
    }
    advance(parser);

    // Captura QUALQUER nome de método (dizOla, main, somar, etc.)
    if (parser->current_token.type != TOKEN_IDENTIFIER) {
        printf("Erro Sintatico [Pardal]: Esperado o nome do metodo\n");
        exit(1);
    }

    ASTNode *method_node = create_node(NODE_FUNCTION_DECL);
    method_node->access = method_access;
    strcpy(method_node->name, parser->current_token.value); // Salva o nome real do método
    advance(parser);

    // Validação de parâmetros do método: aceita (String args) ou ()
    expect(parser, TOKEN_LPAREN, "Esperado '(' apos o nome do metodo");

    if (strcmp(parser->current_token.value, "String") == 0) {
        advance(parser); // Consome 'String'

        if (parser->current_token.type != TOKEN_IDENTIFIER) {
            printf("Erro Sintatico [Pardal]: Esperado nome do parametro (ex: args)\n");
            exit(1);
        }
        advance(parser); // Consome nome do parâmetro
    }

    expect(parser, TOKEN_RPAREN, "Esperado ')' apos parametros");
    expect(parser, TOKEN_LBRACE, "Esperado '{' para abrir o metodo");

    // Validação do comando printl
    if (strcmp(parser->current_token.value, "printl") != 0) {
        printf("Erro Sintatico [Pardal]: Comando desconhecido no metodo\n");
        exit(1);
    }
    advance(parser);

    expect(parser, TOKEN_LPAREN, "Esperado '(' apos printl");

    ASTNode *print_node = create_node(NODE_PRINTL);

    if (parser->current_token.type == TOKEN_STRING) {
        strcpy(print_node->string_value, parser->current_token.value);
        advance(parser);
    } else {
        printf("Erro Sintatico [Pardal]: O comando printl exige uma string entre aspas\n");
        exit(1);
    }

    expect(parser, TOKEN_RPAREN, "Esperado ')'");
    expect(parser, TOKEN_SEMICOLON, "Esperado ';'");
    expect(parser, TOKEN_RBRACE, "Esperado '}' para fechar o metodo");
    expect(parser, TOKEN_RBRACE, "Esperado '}' para fechar a classe");

    // Vincula o comando printl como corpo do método
    method_node->body = print_node;

    // Vincula o método como corpo da classe
    class_node->body = method_node;

    return class_node;
}