//
// Created by Isabel De Valenzuela on 16/12/23.
//

#include "parser.h"
#include "ast.h"

char* tokenNames[] = {
        "PRINT",
        "SET",
        "ADD",
        "ISEQUAL",
        "IFGREATERTHAN",
        "IFLESSTHAN",
        "MULTIPLY",
        "DIVIDE",
        "SUBTRACT",
        "COMPLAIN",
        "UNKNOWN",
        "MESSAGE",
        "ARGUMENT"
};
// Function to parse tokens into an AST
ASTNode* parseTokensIntoAST(Token* token_list, int num_tokens) {
    // Create the root node
    Token root_token = {UNKNOWN, UNKNOWN_TYPE, NULL};
    ASTNode* root = newASTNode(root_token, ROOT);

    // Keep track of the current parent node
    ASTNode* currentParent = root;

    ASTNode *newNode;
    for (int i = 0; i < num_tokens; ++i) {
        // Depending on the type of the token, add it to the AST
        switch (token_list[i].type) {
            case COMMAND:
                // Create a new node for the current token
                newNode = newASTNode(token_list[i], CHILD);
                // Add the new node as a child of the root
                addChildNode(root, newNode);
                // The new node is now the current parent for ARGUMENT and MESSAGE_TYPE tokens
                currentParent = newNode;
                break;
            case MESSAGE_TYPE:
                // Create a new node for the new token
                newNode = newASTNode(token_list[i], CHILD);
                // Add the new node as a child of the current parent
                addChildNode(currentParent, newNode);
                break;
            case ARGUMENT_TYPE:
                // If the token value contains a comma, split it into multiple tokens
                if (strchr(token_list[i].value, ',') != NULL) {
                    char* value = strtok(token_list[i].value, ",");
                    size_t numTokens = sizeof(tokenNames) / sizeof(tokenNames[0]);
                    for (int j = 0; j < numTokens; j++) {
                        if (strcmp(value, tokenNames[j]) == 0) {
                            break;
                        }
                    }
                    while (value != NULL) {
                        Token newToken = {ARGUMENT, ARGUMENT_TYPE, value};
                        newNode = newASTNode(newToken, CHILD);
                        addChildNode(currentParent, newNode);
                        value = strtok(NULL, ",");
                    }
                } else {
                    // Create a new token with the correct type
                    Token newToken = {ARGUMENT, ARGUMENT_TYPE, token_list[i].value};
                    // Create a new node for the new token
                    newNode = newASTNode(newToken, CHILD);
                    // Add the new node as a child of the current parent
                    addChildNode(currentParent, newNode);
                }
                break;
            default:
                // For unknown types, just add the new node as a child of the root
                newNode = newASTNode(token_list[i], CHILD);
                addChildNode(root, newNode);
                break;
        }
    }
    return root;
}
