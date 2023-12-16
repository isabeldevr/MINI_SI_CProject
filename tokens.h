#ifndef MINI_SI_TOKENS_H
#define MINI_SI_TOKENS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Names of tokens
typedef enum {
    PRINT,
    SET,
    ADD,
    ISEQUAL,
    IFGREATERTHAN,
    IFLESSTHAN,
    MULTIPLY,
    DIVIDE,
    SUBTRACT,
    COMPLAIN,
    UNKNOWN,
    MESSAGE,
    ARGUMENT
} TokenName;

typedef enum {
    COMMAND,
    MESSAGE_TYPE,
    ARGUMENT_TYPE,
    UNKNOWN_TYPE
} TokenType;

// Token structure
typedef struct {
    TokenName name;
    TokenType type;
    char* value;
} Token;




#endif //MINI_SI_TOKENS_H


