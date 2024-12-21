#include "lexer.h"
#include "token.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// helper function
Token new_token(TokenType token_type, char ch) {
    char *literal = (char*) malloc(sizeof(char)*2);
    if (literal != NULL) {
        literal[0] = ch;
        literal[1] = '\0';
    }
    Token tok = {.Type = token_type, .Literal = literal};
    return tok;
}

bool is_letter(char ch){
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}

bool is_digit(char ch) {
    return ch >= '0' && ch <= '9';
}

Lexer* new(const char* input) {
    Lexer* l = (Lexer*)malloc(sizeof(Lexer));
    if (l != NULL) {
        l->input = _strdup(input);
        l->position = 0;
        l->readPosition = 0;
        l->ch = '\0';
    }
    // 忘记这一步了 啊啊啊
    read_char(l);
    return l;
}

char* read_number(Lexer *l) {
    int position = l->position;
    while (is_digit(l->ch)) {
        read_char(l);
    }
    int num = l->position - position;
    char *s = (char*) malloc(sizeof(char) * (num + 1));
    if (s != NULL) {
        strncpy(s, l->input + position, num);
        s[num] = '\0';
    }
    return s;
}

char* read_identifier(Lexer *l){
    int position = l->position;
    while(is_letter(l->ch)) {
        read_char(l);
    }
    int num = l->position - position;
    char *s = (char*) malloc(sizeof(char) * (num + 1));
    if (s != NULL) {
        strncpy(s, l->input + position, num);
        s[num] = '\0';
    }
    return s;
}

void read_char(Lexer* l) {
    if (l->readPosition >= strlen(l->input)) {
        l->ch = '\0';
    } else {
        l->ch = l->input[l->readPosition];
    }
    l->position = l->readPosition;
    l->readPosition += 1;
}

char peek_char(Lexer *l) {
    if (l->readPosition >= strlen(l->input)) {
        return '\0';
    } else {
        return l->input[l->readPosition];
    }
}

void skip_whitespace(Lexer *l) {
    while( l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r' ){
        read_char(l);
    }
}

Token next_token(Lexer *l) {
    Token tok;
    skip_whitespace(l);
    switch (l->ch) {
        case '=':
            if (peek_char(l) == '='){
                char ch = l->ch;
                read_char(l);
                char s[3] = {ch, l->ch, '\0'};
                tok.Type = EQ; tok.Literal = strdup(s);
            } else {
                tok = new_token(ASSIGN, l->ch);
            }
            break;
        case '-':
            tok = new_token(MINUS, l->ch);
            break;
        case '!':
            if (peek_char(l) == '=') {
                char ch = l->ch;
                read_char(l);
                char s[3] = {ch, l->ch, '\0'};
                tok.Type = NOT_EQ; tok.Literal = strdup(s);
            } else {
                tok = new_token(BANG, l->ch);
            }
            break;
        case '/':
            tok = new_token(SLASH, l->ch);
            break;
        case '*':
            tok = new_token(ASTERISK, l->ch);
            break;
        case '<':
            tok = new_token(LT, l->ch);
            break;
        case '>':
            tok = new_token(GT, l->ch);
            break;
        case ';':
            tok = new_token(SEMICOLON, l->ch);
            break;
        case '(':
            tok = new_token(LPAREN, l->ch);
            break;
        case ')':
            tok = new_token(RPAREN, l->ch);
            break;
        case ',':
            tok = new_token(COMMA, l->ch);
            break;
        case '+':
            tok = new_token(PLUS, l->ch);
            break;
        case '{':
            tok = new_token(LBRACE, l->ch);
            break;
        case '}':
            tok = new_token(RBRACE, l->ch);
            break;
        case '\0':
            tok.Literal = NULL;
            tok.Type = EOF_T;
            break;
        default:
            if (is_letter(l->ch)) {
                tok.Literal = read_identifier(l);
                tok.Type = lookup_indent(tok.Literal);
                return tok;
            } else if (is_digit(l->ch)) {
                tok.Literal = read_number(l);
                tok.Type = INT;
                return tok;
            } else {
                tok = new_token(ILLEGAL, l->ch);
            }
    }
    read_char(l);
    return tok;
}

