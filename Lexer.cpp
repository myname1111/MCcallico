#include <iostream>
#include <vector>
#include "IllegalCharError.h"
#include "LexerToken.h"
#include "Lexer.h"

using namespace std;

/*
Tokens:
    ADD
    SUB
    MUL
    DIV
    LPAREN
    RPAREN
    INT
    NAME
    EQUALS
    SEMICOLON
*/

Lexer::Lexer(string text_to_be_analyzed){
    Lexer::text = text_to_be_analyzed;
    Lexer::pos = -1;
    Lexer::advance();
}

void Lexer::advance(){
    Lexer::pos++;
    Lexer::current_char = Lexer::pos < Lexer::text.length() ? Lexer::text[Lexer::pos] : '\0';
}

void Lexer::make_number(){
    string num_str = "";

    while (Lexer::current_char != '\0' && isdigit(Lexer::current_char)){
        num_str += Lexer::current_char;
        Lexer::advance();
    }
    Lexer::tokens.push_back(LexerToken("INT", num_str));

}

void Lexer::make_token(){
    while (Lexer::current_char != '\0'){
        if (Lexer::current_char == ' ' | Lexer::current_char == '\t'){ //ignored chars
            Lexer::advance();
        }
        else if (Lexer::current_char == '+'){
            Lexer::tokens.push_back(LexerToken("ADD", "+"));
            Lexer::advance();
        }
        else if (Lexer::current_char == '-'){
            Lexer::tokens.push_back(LexerToken("SUB", "-"));
            Lexer::advance();
        }
        else if (Lexer::current_char == '*'){
            Lexer::tokens.push_back(LexerToken("MUL", "*"));
            Lexer::advance();
        }
        else if (Lexer::current_char == '/'){
            Lexer::tokens.push_back(LexerToken("DIV", "/"));
            Lexer::advance();
        }
        else if (Lexer::current_char == '('){
            Lexer::tokens.push_back(LexerToken("LPAREN", "("));
            Lexer::advance();
        }
        else if (Lexer::current_char == ')'){
            Lexer::tokens.push_back(LexerToken("RPAREN", ")"));
            Lexer::advance();
        }
        else if (isdigit(Lexer::current_char)){
            Lexer::make_number();
        }
        else {
            Lexer::error = IllegalCharError(Lexer::current_char);
        }
    }
}
