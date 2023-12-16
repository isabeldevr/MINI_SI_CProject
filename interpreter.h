//
// Created by Isabel De Valenzuela on 16/12/23.
//

#ifndef MINISI_INTERPRETER_H
#define MINISI_INTERPRETER_H

#include "ast.h"


typedef struct {
    char name[50];
    int value;
} Variable;

void perform_complain();
void perform_print(char* arguments[]);
void perform_set(char* arguments[]);
void perform_add(char* arguments[]);
void perform_isequal(char* arguments[]);
void perform_ifgreaterthan(char* arguments[]);
void perform_iflessthan(char* arguments[]);
void perform_multiply(char* arguments[]);
void perform_divide(char* arguments[]);
void perform_subtract(char* arguments[]);
void freeAST(ASTNode* root);

void processNode(ASTNode* node, char *arguments[]);
void interpreter(ASTNode* root);
char * trim_whitespace(char *str);

#endif //MINISI_INTERPRETER_H
