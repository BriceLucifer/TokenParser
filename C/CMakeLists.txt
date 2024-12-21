cmake_minimum_required(VERSION 3.27)
project(Monkey C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Monkey
        token.h
        token.c
        lexer.h
        lexer.c
        repl.h
        repl.c
        main.c
       )
