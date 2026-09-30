#!/bin/bash

echo "=== Compilando a Linguagem Pardal ==="

# Cria pasta de binários se não existir
mkdir -p bin

# Compila o projeto com o GCC
gcc -Wall -Wextra -Iinclude src/main.c src/lexer.c src/parser.c src/ast.c -o bin/pardal.exe

# Se a compilação teve sucesso, roda o teste oficial
if [ $? -eq 0 ]; then
    echo -e "\n[OK] Compilação concluída com sucesso!\n"
    echo "=== Executando tests/Main.pd ==="
    ./bin/pardal.exe tests/Main.pd
else
    echo -e "\n[ERRO] Falha na compilação do Pardal."
fi