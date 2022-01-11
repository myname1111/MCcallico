#include <iostream>
#include <vector>
#include "Tree.h"
#include "TreeNode.h"
#include "Lexer.h"
#include "LexerToken.h"
#include "Parser.h"

using namespace std;

Parser::Parser(vector <LexerToken> tokens) {
    Parser::toks = tokens;
}

void Parser::advance(){
    Parser::pos++;
    if (Parser::pos < Parser::toks.size()){
        Parser::current_token = Parser::toks.at(Parser::pos);
    }
}

Tree Parser::factor(){
    if (Parser::current_token.name == "INT"){
        Parser::advance();
        vector<LexerToken> node;
        node[0] = Parser::current_token;
        return Tree("Factor", vector<TreeNode> {TreeNode("Factor", node)});
    }
}

void Parser::term(){}

void Parser::expr(){}
