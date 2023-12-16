#ifndef MINISI_LEXER_H
#define MINISI_LEXER_H

#include "tokens.h"

typedef struct {
    char contents[100000];
    char current_char;
    char* word;
    int position;
} Lexer;

void initializeLexer(Lexer *lexer, const char *input);
void skipWhitespace(Lexer* lexer);
Token get_token(Lexer* lexer);
int advanceLexer(Lexer* lexer, Token ** token_list, int * num_tokens);



#endif //MINISI_LEXER_H
