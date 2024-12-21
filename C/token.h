//
// Created by 23766 on 2024/9/29.
//

#ifndef MONKEY_TOKEN_H
#define MONKEY_TOKEN_H

#define TokenType char*

#define ILLEGAL "ILLEGAL"
#define EOF_T "EOF"

#define IDENT "IDENT"
#define INT "INT"

#define ASSIGN "="
#define PLUS "+"
#define MINUS "-"
#define BANG "!"
#define ASTERISK "*"
#define SLASH "/"

#define LT "<"
#define GT ">"

#define COMMA ","
#define SEMICOLON ";"

#define LPAREN "("
#define RPAREN ")"
#define LBRACE "{"
#define RBRACE "}"

#define FUNCTION "FUNCTION"
#define LET "LET"
#define TRUE "TRUE"
#define FALSE "FALSE"
#define IF "IF"
#define ELSE "ELSE"
#define RETURN "RETURN"

#define EQ "=="
#define NOT_EQ "!="

typedef struct {
    TokenType Type;
    char* Literal;
} Token;

typedef struct {
    const char* keyword;
    TokenType type;
} Keyword;

extern const Keyword KEYWORDS[];

extern const int NUM_KEYS ;
TokenType lookup_indent(const char* keyword) ;

#endif //MONKEY_TOKEN_H
