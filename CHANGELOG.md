# Changelog

All notable changes to Shawn are documented in this file.

The project is in early development. Version numbers and features may change as the interpreter evolves.

## [Unreleased]

### Planned
- Complete variable assignment validation and execution.
- Integrate parsing, semantic analysis, and runtime execution.
- Expand type support and runtime behavior.
- Improve error reporting and test coverage.

## [0.1.0] - 2026-10-22

### Added
- Initial C project structure.
- Lexer and token definitions.
- Parser for supported statements and arithmetic expressions.
- Abstract Syntax Tree (AST) structures and memory management.
- Integer arithmetic expression evaluation.
- Basic semantic analysis for variable and constant declarations.
- Symbol table with integer value storage.
- Duplicate declaration checks.
- Protection against modifying constants through the symbol table API.
- Makefile targets for building the interpreter and running tests.
- Initial automated tests for parsing, symbol table behavior, and integer expression evaluation.

### Notes
- This is an early development milestone, not a stable release.
- Assignment execution and complete interpreter integration remain in progress.
- Support for all declared data types is not yet complete.
