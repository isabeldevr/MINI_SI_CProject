#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tokens.h"
#include "ast.h"
#include "parser.h"
#include "lexer.h"

// Lexer structure

// Function to initialize a Lexer
void initializeLexer(Lexer* lexer, const char* input) {
    strcpy(lexer->contents, input);
    lexer->current_char = input[0];
    lexer->word = malloc(sizeof(char) * 1000);
    lexer->word[0] = '\0';
    lexer->position = 0;
}

// Function to skip the whitespace
void skipWhitespace(Lexer* lexer) { // (ADLT) Change function name to skip_whitespace_tab_newline()
    while (lexer->current_char == '\n' || lexer->current_char == '\t' || lexer->current_char == ' ') {
        lexer->position += 1;
        lexer->current_char = lexer->contents[lexer->position];
    }
}


// Function to get the current token
Token get_token(Lexer* lexer) {
    Token token;
    token.value = NULL;
    // Check the first character of the word for the switch statement then compare the rest
    switch (lexer->word[0]) {
        case 'P':
            if (strcmp(lexer->word, "PRINT") == 0) {
                token.name = PRINT;
                token.type = COMMAND;
                token.value = strdup("Print");
            }
            break;
        case 'S':
            if (strcmp(lexer->word, "SET") == 0) {
                token.name = SET;
                token.type = COMMAND;
                token.value = strdup("Set");
            } else if (strcmp(lexer->word, "SUBTRACT") == 0) {
                token.name = SUBTRACT;
                token.type = COMMAND;
                token.value = strdup("Subtract");
            }
            break;
        case 'A':
            if (strcmp(lexer->word, "ADD") == 0) {
                token.name = ADD;
                token.type = COMMAND;
                token.value = strdup("Add");
            }
            break;
        case 'I':
            if (strcmp(lexer->word, "ISEQUAL") == 0) {
                token.name = ISEQUAL;
                token.type = COMMAND;
                token.value = strdup("IsEqual");
            }
            else if (strcmp(lexer->word, "IFGREATERTHAN") == 0) {
                token.name = IFGREATERTHAN;
                token.type = COMMAND;
                token.value = strdup("IfGreaterThan");
            } else if (strcmp(lexer->word, "IFLESSTHAN") == 0) {
                token.name = IFLESSTHAN;
                token.type = COMMAND;
                token.value = strdup("IfLessThan");
            }
            break;
        case 'M':
            if (strcmp(lexer->word, "MULTIPLY") == 0) {
                token.name = MULTIPLY;
                token.type = COMMAND;
                token.value = strdup("Multiply");
            }
            break;
        case 'D':
            if (strcmp(lexer->word, "DIVIDE") == 0) {
                token.name = DIVIDE;
                token.type = COMMAND;
                token.value = strdup("Divide");
            }
            break;
        case 'C':
            if (strcmp(lexer->word, "COMPLAIN") == 0) {
                token.name = COMPLAIN;
                token.type = COMMAND;
                token.value = strdup("Complain");
            }
            break;
        default:
            token.name = UNKNOWN;
            token.type = UNKNOWN_TYPE;
            token.value = strdup(lexer->word);
            break;
    }
    return token;
}

// AST Node structure

// Function to advance the lexer to the next word
int advanceLexer(Lexer* lexer, Token** token_list, int* num_tokens) {
    while (lexer->position < strlen(lexer->contents)) {
        if (lexer->current_char == ' ' || lexer->current_char == '\t' || lexer->current_char == '\n') {
            skipWhitespace(lexer);
        } else if (lexer->current_char == '(') {
            // Reset the word for the next token
            strcpy(lexer->word, "");
            // Skip the '(' character
            lexer->position++;
            lexer->current_char = lexer->contents[lexer->position];

            // if string
            if (lexer->current_char == '"') {
                lexer->position++;
                lexer->current_char = lexer->contents[lexer->position];

                while (lexer->current_char != '"' && lexer->current_char != '\0') {
                    char char_str[2] = {lexer->current_char, '\0'};
                    strcat(lexer->word, char_str);
                    lexer->position++;
                    lexer->current_char = lexer->contents[lexer->position];
                }

                int position_curr = lexer->position;
                position_curr++;
                char next_char = lexer->contents[position_curr];


                if (lexer->current_char == '"' && next_char == ')') {
                    Token this_token;
                    this_token.name = MESSAGE;
                    this_token.type = MESSAGE_TYPE;
                    this_token.value = strdup(lexer->word);
                    (*token_list)[*num_tokens] = this_token;
                    (*num_tokens)++;
                    (*token_list)[*num_tokens] = this_token;
                    (*num_tokens)++;

                    // Move to the next character after '"'
                    lexer->position++;
                    lexer->position++;
                    lexer->current_char = lexer->contents[lexer->position];

                } else {
                    printf("ERROR: Expected """ "but found EOF\n");
                    return 0;
                }

            } else {
                // Read everything until ')'
                while (lexer->current_char != ')' && lexer->current_char != '\0') {
                    char char_str[2] = {lexer->current_char, '\0'};
                    strcat(lexer->word, char_str);
                    lexer->position++;
                    lexer->current_char = lexer->contents[lexer->position];
                }

                // Find ")"
                if (lexer->current_char == ')') {
                    Token this_token;
                    this_token.name = ARGUMENT;
                    this_token.type = ARGUMENT_TYPE;
                    this_token.value = strdup(lexer->word);
                    (*token_list)[*num_tokens] = this_token;
                    (*num_tokens)++;

                    // Move to the next character after ')'
                    lexer->position++;
                    lexer->position++;
                    lexer->current_char = lexer->contents[lexer->position];

                } else {
                    printf("ERROR: Expected ')' but found EOF\n");
                    return 0;
                }
            }

        } else {
            // Reset the word for the next token
            strcpy(lexer->word, "");

            // Read everything until whitespace or special character
            while (lexer->current_char != ' ' && lexer->current_char != '\t' && lexer->current_char != '\n') {
                char char_str[2] = {lexer->current_char, '\0'};
                strcat(lexer->word, char_str);
                lexer->position++;
                if (lexer->position >= strlen(lexer->contents)) {
                    // Reached the end of the file
                    break;
                }
                lexer->current_char = lexer->contents[lexer->position];
            }
            // Create a token based on the word
            Token this_token = get_token(lexer);
            (*token_list)[*num_tokens] = this_token;
            (*num_tokens)++;
        }
    }
    return 1;
}

