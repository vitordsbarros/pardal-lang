/*
 * Pardal Programming Language Interpreter
 * Developed by Vitor
 *
 * Copyright (c) 2026 Vitor. All rights reserved.
 * Licensed under the MIT License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "../include/parser.h"
#include "../include/ast.h"

void print_version(void) {
    printf("Pardal Language v0.2.0 (Built with C11)\n");
    printf("Created and maintained by Vitor.\n");
}

void print_about(void) {
    printf("--------------------------------------------------\n");
    printf("  Pardal Programming Language\n");
    printf("  Purely Object-Oriented, Interpreted in C\n");
    printf("  Designed & Engineered by Vitor\n");
    printf("--------------------------------------------------\n");
}

int has_pd_extension(const char *filename) {
    const char *dot = strrchr(filename, '.');
    return (dot && strcmp(dot, ".pd") == 0);
}

char* read_file(const char *filename) {
    FILE *file = fopen(filename, "rb"); // Leitura binária preserva codificação UTF-8 nativa
    if (!file) {
        printf("Erro [Pardal]: Nao foi possivel abrir o arquivo '%s'\n", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(length + 1);
    if (!buffer) {
        printf("Erro [Pardal]: Falha de memoria ao carregar o arquivo.\n");
        exit(1);
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

int main(int argc, char *argv[]) {
    // Configura o locale do C e o terminal Windows para UTF-8 (Code Page 65001)
    setlocale(LC_ALL, ".UTF-8");

#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    // Tratamento das marcas pessoais e ajuda via linha de comando
    if (argc >= 2) {
        if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
            print_version();
            return 0;
        }
        if (strcmp(argv[1], "--about") == 0) {
            print_about();
            return 0;
        }
    }

    if (argc < 2) {
        printf("Uso: pardal <arquivo.pd>\n");
        printf("Para mais opcoes: pardal --version ou pardal --about\n");
        return 1;
    }

    if (!has_pd_extension(argv[1])) {
        printf("Erro [Pardal]: O arquivo informado deve ter a extensao '.pd'\n");
        return 1;
    }

    char *source_code = read_file(argv[1]);

    Parser parser;
    parser_init(&parser, source_code);

    ASTNode *program_ast = parse_program(&parser);

    // Extrai o nome do arquivo sem caminho ou extensão (ex: "tests/Main.pd" -> "Main")
    char expected_class_name[256];
    const char *filename_only = strrchr(argv[1], '/');
    if (!filename_only) filename_only = strrchr(argv[1], '\\');
    filename_only = (filename_only == NULL) ? argv[1] : filename_only + 1;

    strcpy(expected_class_name, filename_only);
    char *dot = strrchr(expected_class_name, '.');
    if (dot) *dot = '\0';

    // Validação estrita: Nome da Classe principal == Nome do Arquivo .pd
    if (strcmp(program_ast->name, expected_class_name) != 0) {
        printf("Erro [Pardal]: O nome da classe '%s' deve ser identico ao nome do arquivo '%s.pd'\n",
               program_ast->name, expected_class_name);
        free_ast(program_ast);
        free(source_code);
        return 1;
    }

    // Executa a árvore de sintaxe abstrata
    execute_ast(program_ast);

    free_ast(program_ast);
    free(source_code);

    return 0;
}