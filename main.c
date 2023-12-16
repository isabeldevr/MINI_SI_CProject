#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokens.h"
#include "ast.h"
#include "parser.h"
#include "lexer.h"
#include "interpreter.h"

int main() {
    FILE *fp;
    fp = fopen("code.mini_si", "r");
    if (fp == NULL) {
        printf("ERROR RUNNING FILE\n");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *contents = (char *) malloc(file_size * sizeof(char));
    if (contents == NULL) {
        printf("Memory allocation error for contents\n");
        fclose(fp);
        return 1;
    }

    // Read file contents into the 'contents' buffer
    fread(contents, sizeof(char), file_size, fp);

    Token *token_list = (Token *) malloc(file_size * sizeof(Token));
    if (token_list == NULL) {
        printf("Memory allocation error for tokens\n");
        free(contents);
        fclose(fp);
        return 1;
    }

    Lexer lexer;
    int num_tokens = 0;
    initializeLexer(&lexer, contents);
    // Parse the file and get the list of tokens and the number of tokens
    advanceLexer(&lexer, &token_list, &num_tokens); // (ADLT) Chnage name of "advanceLexer()" to "ParseWithLexer()"

    // Generate the AST
    ASTNode *root = parseTokensIntoAST(token_list, num_tokens);

    // Print the AST tree
    //printAST(root, 0);

    // interpreter(root);
    interpreter(root);

    // Free the memory
    free(lexer.word);
    free(contents);
    free(token_list);
    fclose(fp);

    return 0;
}

/* TO DO LIST
* Make the interpreter return errors if syntax incorrect
* General error handling
* If we want nested commands we have to change tree structure
* Expand command list
*/
