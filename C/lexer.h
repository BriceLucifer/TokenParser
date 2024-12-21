//
// Created by 23766 on 2024/9/29.
//

#ifndef MONKEY_LEXER_H
#define MONKEY_LEXER_H

#include <stdlib.h>
#include <stdbool.h>
#include "token.h"

typedef struct {
    char * input;
    int position;
    int readPosition;
    char ch;
}Lexer;


// function for lexer
Lexer* new(const char* input) ;
void read_char(Lexer* l);
Token next_token(Lexer *l);
char* read_identifier(Lexer* l);
char* read_number(Lexer* l) ;
void skip_whitespace(Lexer *l);
char peek_char(Lexer *l);

// helper function
Token new_token(TokenType token_type, char ch);
bool is_letter(char ch);
bool is_digit(char byte);


#endif //MONKEY_LEXER_H
