#ifndef MINI_SI_AST_H
#define MINI_SI_AST_H

#include "tokens.h"

typedef enum {
    ROOT,
    CHILD,
} TreeNodeType;


typedef struct {
    Token token;
    TreeNodeType type;
    struct ASTNode* nextNode;
    struct ASTNode** childNodes; // Array of pointers to child nodes
    int numChildNodes; // Number of child nodes
} ASTNode;

ASTNode* newASTNode(Token token, TreeNodeType nodeType);
void addChildNode(ASTNode* parentNode, ASTNode* childNode);
void printAST(ASTNode* node, int depth);
void freeAST(ASTNode* node);


#endif //MINI_SI_AST_H
