# Detecta o sistema operacional
ifeq ($(OS),Windows_NT)
    TARGET = bin/pardal.exe
    RM = del /Q /F
    RMDIR = rmdir /S /Q
    MKDIR = if not exist bin mkdir bin
    FIXPATH = $(subst /,\,$1)
else
    TARGET = bin/pardal
    RM = rm -f
    RMDIR = rm -rf
    MKDIR = mkdir -p bin
    FIXPATH = $1
endif

# Compilador e Flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Fontes e Objetos
SRC = src/main.c src/lexer.c src/parser.c src/ast.c
OBJ = $(SRC:.c=.o)

# Regra Principal (make)
all: $(TARGET)

# Linkagem do Executável
$(TARGET): $(OBJ)
	@$(MKDIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Compilação Individual dos arquivos .c para .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para compilar e rodar o teste automaticamente (make run)
run: all
	./$(TARGET) tests/Main.pd

# Limpeza dos arquivos compilados (make clean)
clean:
	$(RM) src\*.o 2>nul || true
	$(RMDIR) bin 2>nul || true

.PHONY: all run clean