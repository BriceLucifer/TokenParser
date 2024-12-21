#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "token.h"

#include <stdlib.h>

const char *username_get() {
    const char *username;

    // 在 Windows 上，通常使用 %USERNAME%
    // 在 Unix/Linux 上，通常使用 $USER
    username = getenv("USERNAME");
    if (username == NULL) {
        username = getenv("USER");
    }

    // 返回用户名，如果都未设置，则返回 NULL
    return username;
}

void ui(){
    const char* username = username_get();
    // ANSI 转义码设置为黄色
    const char *yellow = "\033[33m";
    // ANSI 转义码重置颜色
    const char *reset = "\033[0m";
    const char *monkey_face =
            "            __,__\n"
            "   .--.  .-\"     \"-.  .--.\n"
            "  / .. \\/  .-. .-.  \\/ .. \\\n"
            " | |  '|  /   Y   \\  |'  | |\n"
            " | \\   \\  \\ 0 | 0 /  /   / |\n"
            "  \\ '- ,\\.-\"\"\"\"\"\"-./, -' /\n"
            "   ''-' /_   ^ ^   _\\ '-''\n"
            "       |  \\._   _./  |\n"
            "       \\   \\ '~' /   /\n"
            "        '._ '-=-' _.'\n"
            "           '-----'\n" ;
    printf("%s%s%s",yellow,monkey_face,reset);
    printf("Hello! %s, Welcome to the REPL! Type 'exit' to quit.\n",username);
}

void start_repl() {
    char input[1024];

    ui();
    while (1) {
        printf(">>> ");
        fgets(input, sizeof(input), stdin);

        // 去除换行符
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            break;
        }

        Lexer* lexer = new(input);
        Token tok = {.Type = NULL, .Literal = NULL};

        do {
            tok = next_token(lexer);
            printf("Token Type: %s, Literal: %s\n", tok.Type, tok.Literal ? tok.Literal : "NULL");
            free(tok.Literal);  // 释放分配的内存
        } while (strcmp(tok.Type, EOF_T));

        free(lexer->input);  // 释放输入字符串
        free(lexer);         // 释放词法分析器结构
    }
}
