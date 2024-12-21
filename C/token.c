//
// Created by 23766 on 2024/9/29.
//
#include "token.h"
#include <string.h>

extern const Keyword KEYWORDS[] = {
        {"fn", FUNCTION},
        {"let", LET},
        {"true", TRUE},
        {"false", FALSE},
        {"if", IF},
        {"else", ELSE},
        {"return", RETURN},
};

extern const int NUM_KEYS = sizeof(KEYWORDS) / sizeof(KEYWORDS[0]);


TokenType lookup_indent(const char* keyword) {
    for (int i = 0 ; i < NUM_KEYS; i++) {
        if (strcmp(keyword,KEYWORDS[i].keyword) == 0) {
            return KEYWORDS[i].type;
        }
    }
    return ILLEGAL;
}