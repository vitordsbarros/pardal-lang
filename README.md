# Pardal Programming Language

Pardal is a purely object-oriented, interpreted programming language implemented in C. It is designed to combine the clean structure of languages like Java and C# with a modern, low-boilerplate syntax.

---

## Core Principles

* **Public by Default:** Class declarations and methods are implicitly public. Modifiers like `private` or `protected` are only required when access restriction is necessary.
* **Class and File Alignment:** The primary class declared within a file must strictly match the filename (e.g., `Main.pd` must declare `class Main`).
* **Flexible Entry Point:** The interpreter searches for the `main` method as the entry point. It supports signatures with CLI arguments (`void main(String args)`) or without arguments (`void main()`).
* **Native UTF-8 Encoding:** Full native support for UTF-8 character encoding across both the C runtime and source file interpretation.
* **Modular Architecture:** Clean separation into Lexer, Parser, Abstract Syntax Tree (AST), and Interpreter modules.

---

## Syntax Overview

### `Main.pd`

```java
class Main {

    void sayHello() {
        printl("Hello from a class method!");
    }

    void main(String args) {
        printl("Hello, World! Pardal interpreter running successfully.");
    }
}
```

---

## Project Structure

```text
pardal-lang/
├── bin/               # Compiled executable directory
├── include/           # Header files
│   ├── ast.h          # Abstract Syntax Tree structures and visibility types
│   ├── lexer.h        # Token definitions
│   └── parser.h       # Parser definitions
├── src/               # Implementation source files
│   ├── ast.c          # AST node creation and execution logic
│   ├── lexer.c        # Lexical analyzer (Tokenizer)
│   ├── main.c         # CLI interface, UTF-8 setup, and file loader
│   └── parser.c       # Recursive descent parser
├── tests/             # Test suite
│   └── Main.pd        # Default entry-point test file
├── build.sh           # Native build script for Unix/MinGW environments
├── Makefile           # Multi-platform build automation
└── README.md          # Project documentation
```

---

## Building and Running

### Prerequisites

* **GCC Compiler** — MinGW-w64 on Windows or standard GCC on Linux/macOS
* **Bash terminal environment** — Git Bash, WSL, or native Linux terminal

### 1. Clone the Repository

```bash
git clone https://github.com/vitordsbarros/pardal-lang.git
cd pardal-lang
```

### 2. Compile and Execute

Using the automated build script:

```bash
bash build.sh
```

### 3. Manual Compilation with GCC

```bash
mkdir -p bin

gcc -Wall -Wextra \
    -Iinclude \
    src/main.c \
    src/lexer.c \
    src/parser.c \
    src/ast.c \
    -o bin/pardal.exe

./bin/pardal.exe tests/Main.pd
```

---

## Technical Roadmap

* [x] **Phase 1:** Lexer, Parser, AST, and CLI file validation
* [x] **Phase 2:** Public-by-default class structure and UTF-8 output encoding
* [x] **Phase 3:** Entry point separation and optional CLI parameter handling
* [ ] **Phase 4:** Support for multiple method declarations within a single class
* [ ] **Phase 5:** Primitive types, variable declarations, and Symbol Table
* [ ] **Phase 6:** Expression parsing and arithmetic operations
* [ ] **Phase 7:** Control flow (`if`, `else`, `while`)
* [ ] **Phase 8:** Object instantiation (`new`), attributes, and instance calls
