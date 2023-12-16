#include "ast.h"

// Function to create a new AST Node
ASTNode* newASTNode(Token token, TreeNodeType nodeType) {
    ASTNode* node = (ASTNode*)calloc(1, sizeof(ASTNode));
    node->token = token;
    node->type = nodeType;
    node->nextNode = NULL;
    node->childNodes = NULL; // Initially, there are no child nodes
    node->numChildNodes = 0; // Initially, there are no child nodes
    return node;
}

// Function to add a child node to a parent node
void addChildNode(ASTNode* parentNode, ASTNode* childNode) {
    parentNode->numChildNodes++;
    parentNode->childNodes = realloc(parentNode->childNodes, parentNode->numChildNodes * sizeof(ASTNode*));
    if (parentNode->childNodes == NULL) {
        printf("Memory allocation error for child nodes\n");
        exit(1);
    }
    parentNode->childNodes[parentNode->numChildNodes - 1] = childNode;
}

// Function to print the AST tree
void printAST(ASTNode* node, int depth) {
    // Array of token names
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
            "ARGUMENT"  // Added ARGUMENT
    };

    // Array of token types
    char* tokenTypes[] = {
            "COMMAND",
            "MESSAGE_TYPE",
            "ARGUMENT_TYPE",
            "UNKNOWN_TYPE"

    };

    // Array of tree node types
    char* NodeTypes[] = {
            "ROOT",
            "CHILD"
            // Add more node types as needed
    };

    // Print the current node
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    printf("Node Type: %s, Token Name: %s, Token Type: %s, Value: %s\n",
           NodeTypes[node->type],
           tokenNames[node->token.name],
           tokenTypes[node->token.type],
           node->token.value);

    // Print all child nodes
    for (int i = 0; i < node->numChildNodes; i++) {
        printAST(node->childNodes[i], depth + 1);
    }
}
// Function to free the AST when done transversing
void freeAST(ASTNode* root) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < root->numChildNodes; i++) {
        freeAST(root->childNodes[i]);
    }
    free(root->childNodes);
    free(root);
}
