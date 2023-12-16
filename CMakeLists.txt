cmake_minimum_required(VERSION 3.26)
project(minisi C)

set(CMAKE_C_STANDARD 11)

add_executable(minisi main.c
        ast.c
        ast.h
        parser.c
        parser.h
        lexer.c
        lexer.h
        tokens.c
        lexer.h
        interpreter.c
        interpreter.h)
