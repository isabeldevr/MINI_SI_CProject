//
// Created by Isabel De Valenzuela on 16/12/23.
//

#ifndef MINI_SI_PARSER_H
#define MINI_SI_PARSER_H

#include "tokens.h"
#include "ast.h"

ASTNode* parseTokensIntoAST(Token* tokens, int numTokens);


#endif //MINI_SI_PARSER_H
