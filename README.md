# Shawn

**An experimental interpreted programming language written in C.**

Shawn is a programming language project built from scratch in C. Its goal is to develop a small interpreter with its own syntax, parser, abstract syntax tree, semantic analysis, and symbol table.

> **Status: Early development.** Shawn is not ready for production use. Syntax and features may change as development progresses.

## Current Features

- Lexical analysis and tokenization.
- Parsing of supported statements and arithmetic expressions.
- Abstract Syntax Tree (AST) construction and memory management.
- Arithmetic expression evaluation for integers.
- Operator precedence for supported arithmetic expressions.
- Variable and constant declarations.
- Type inference and basic semantic checks.
- Symbol table with integer value storage.
- Protection against duplicate declarations and modification of constants.
- Automated test builds using a Makefile.

## Example Syntax

A variable declaration:

```shawn
set int: idade = 22;
```

A constant declaration:

```shawn
lock str: nome = "Shawn";
```

A declaration with inferred type:

```shawn
set idade = 22;
```

These examples illustrate the intended syntax for supported declarations. Full program execution and support for every listed type are still under development.

## Requirements

- GCC
- MSYS2/MinGW on Windows, or a compatible C development environment.
- `mingw32-make` on the current Windows setup, or `make` on systems where it is available.

## Build

Clone the repository and enter its directory:

```bash
git clone https://github.com/vitordsbarros/shawn-lang.git
cd shawnLang
```

Build the interpreter:

```bash
mingw32-make all
```

The build target is `build/shawn`.

## Run Tests

```bash
mingw32-make test
```

The test targets cover parser and semantic behavior, symbol table operations, and integer expression evaluation.

Remove generated build files:

```bash
mingw32-make clean
```

## Project Structure

```text
shawnLang/
├── include/   # Header files
├── src/       # Interpreter components
├── tests/     # Test programs
├── build/     # Generated binaries (not tracked by Git)
├── main.c     # Program entry point
├── Makefile   # Build and test targets
├── LICENSE
├── README.md
└── CHANGELOG.md
```

## Roadmap

- [ ] Complete assignment validation and execution.
- [ ] Integrate parsing, semantic analysis, and execution into a complete interpreter flow.
- [ ] Expand runtime support for additional data types.
- [ ] Improve syntax, semantic, and runtime error reporting.
- [ ] Expand automated tests and documentation.

## Contributing

Shawn is an experimental project under active development. Bug reports, suggestions, and contributions are welcome. Please open an issue before making substantial changes.

## License

Shawn is distributed under the MIT License. See [LICENSE](LICENSE) for details.
