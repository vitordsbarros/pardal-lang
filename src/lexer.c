#include "lexer.h"

void lexer_init(Lexer *lexer, const char *source)
{
    lexer->source = source;

    lexer->start = 0;
    lexer->current = 0;

    lexer->line = 1;
    lexer->column = 1;

    lexer->start_line = 1;
    lexer->start_column = 1;
}

static char lexer_peek(const Lexer *lexer)
{
    return lexer->source[lexer->current];
}

static char lexer_advance(Lexer *lexer)
{
    char c = lexer->source[lexer->current];

    if (c == '\0')
    {
        return '\0';
    }

    lexer->current++;

    if (c == '\n')
    {
        lexer->line++;
        lexer->column = 1;
    }
    else
    {
        lexer->column++;
    }

    return c;
}

static void lexer_skip_whitespace(Lexer *lexer)
{
    char c = lexer_peek(lexer);

    while (c == ' ' ||
           c == '\t' ||
           c == '\n' ||
           c == '\r' ||
           c == '\f' ||
           c == '\v')
    {

        lexer_advance(lexer);
        c = lexer_peek(lexer);
    }
}

static Token lexer_make_token(Lexer *lexer, TokenType type)
{
    Token token;

    token.type = type;
    token.literal = lexer->source + lexer->start;
    token.length = lexer->current - lexer->start;
    token.line = lexer->start_line;
    token.column = lexer->start_column;

    return token;
}

static int lexer_is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

static int lexer_is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static int lexer_is_identifier_char(char c)
{
    return lexer_is_alpha(c) || lexer_is_digit(c);
}

static TokenType lexer_keyword_type(const char *start, size_t length)
{
    if (length == 3 && start[0] == 's' &&
        start[1] == 'e' && start[2] == 't')
    {
        return TOKEN_SET;
    }

    if (length == 4 && start[0] == 'l' &&
        start[1] == 'o' && start[2] == 'c' &&
        start[3] == 'k')
    {
        return TOKEN_LOCK;
    }

    if (length == 3 && start[0] == 'i' &&
        start[1] == 'n' && start[2] == 't')
    {
        return TOKEN_TYPE_INT;
    }

    if (length == 5 && start[0] == 'f' &&
        start[1] == 'l' && start[2] == 'o' &&
        start[3] == 'a' && start[4] == 't')
    {
        return TOKEN_TYPE_FLOAT;
    }

    if (length == 4 && start[0] == 'b' &&
        start[1] == 'o' && start[2] == 'o' &&
        start[3] == 'l')
    {
        return TOKEN_TYPE_BOOL;
    }

    if (length == 4 && start[0] == 'c' &&
        start[1] == 'h' && start[2] == 'a' &&
        start[3] == 'r')
    {
        return TOKEN_TYPE_CHAR;
    }

    if (length == 3 && start[0] == 's' &&
        start[1] == 't' && start[2] == 'r')
    {
        return TOKEN_TYPE_STR;
    }

    return TOKEN_IDENTIFIER;
}

Token lexer_next_token(Lexer *lexer)
{
    lexer_skip_whitespace(lexer);

    lexer->start = lexer->current;
    lexer->start_line = lexer->line;
    lexer->start_column = lexer->column;

    char c = lexer_peek(lexer);

    if (c == '\0')
    {
        return lexer_make_token(lexer, TOKEN_EOF);
    }

    if (lexer_is_alpha(c))
    {
        lexer_advance(lexer);

        while (lexer_is_identifier_char(lexer_peek(lexer)))
        {
            lexer_advance(lexer);
        }

        return lexer_make_token(
            lexer,
            lexer_keyword_type(
                lexer->source + lexer->start,
                lexer->current - lexer->start));
    }

    if (lexer_is_digit(c))
    {
        lexer_advance(lexer);

        while (lexer_is_digit(lexer_peek(lexer)))
        {
            lexer_advance(lexer);
        }

        return lexer_make_token(lexer, TOKEN_INTEGER);
    }

    if (c == '"')
    {
        lexer_advance(lexer);

        while (lexer_peek(lexer) != '"' &&
               lexer_peek(lexer) != '\0')
        {
            lexer_advance(lexer);
        }

        if (lexer_peek(lexer) == '\0')
        {
            return lexer_make_token(lexer, TOKEN_INVALID);
        }

        lexer_advance(lexer);
        return lexer_make_token(lexer, TOKEN_STRING);
    }

    switch (c)
    {
    case '=':
        lexer_advance(lexer);
        return lexer_make_token(lexer, TOKEN_ASSIGN);

    case ':':
        lexer_advance(lexer);
        return lexer_make_token(lexer, TOKEN_COLON);

    case ';':
        lexer_advance(lexer);
        return lexer_make_token(lexer, TOKEN_SEMICOLON);

    case '+':
        lexer_advance(lexer);
        return lexer_make_token(lexer, TOKEN_PLUS);

    case '-':
        lexer_advance(lexer);
        return lexer_make_token(lexer, TOKEN_MINUS);

    case '*':
        lexer_advance(lexer);
        return lexer_make_token(lexer, TOKEN_MULTIPLY);

    case '/':
        lexer_advance(lexer);
        return lexer_make_token(lexer, TOKEN_DIVIDE);

    case '(':
        lexer_advance(lexer);
        return lexer_make_token(lexer, TOKEN_LPAREN);

    case ')':
        lexer_advance(lexer);
        return lexer_make_token(lexer, TOKEN_RPAREN);

    default:
        lexer_advance(lexer);
        return lexer_make_token(lexer, TOKEN_INVALID);
    }
}