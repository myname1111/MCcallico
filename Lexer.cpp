#include <iostream>
#include <vector>
#include "IllegalCharError.h"
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

bool Lexer::is_alphabet(char in_char){
    return (int(in_char) > 64 && int(in_char) < 91) | (int(in_char) > 96 && int(in_char) < 123);
}

void Lexer::make_number(){
    string num_str = "";

    while (Lexer::current_char != '\0' && isdigit(Lexer::current_char)){
        num_str += Lexer::current_char;
        Lexer::advance();
    }
    Lexer::tokens.push_back(LexerToken("INT", num_str));

}

void Lexer::make_name(){
    string name_str = "";

    while ((Lexer::is_alphabet(Lexer::current_char) | isdigit(Lexer::current_char) | Lexer::current_char == '_') && Lexer::current_char != '\0'){
        name_str += Lexer::current_char;
        Lexer::advance();
    }
    Lexer::tokens.push_back(LexerToken("NAME", name_str));

}

void Lexer::make_token(){
    while (Lexer::current_char != '\0'){
        if (Lexer::current_char == ' ' | Lexer::current_char == '\t' | Lexer::current_char == '\n'){ //ignored chars
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
        else if (Lexer::current_char == '='){
            Lexer::tokens.push_back(LexerToken("EQUALS", "="));
            Lexer::advance();
        }
        else if (Lexer::current_char == ';'){
            Lexer::tokens.push_back(LexerToken("SEMICOLON", ";"));
            Lexer::advance();
        }
        else if (isdigit(Lexer::current_char)){
            Lexer::make_number();
        }
        else if (Lexer::is_alphabet(Lexer::current_char) | Lexer::current_char == '_'){
            Lexer::make_name();
        }
        else {
            Lexer::error = IllegalCharError(Lexer::current_char);
            cout << Lexer::error.as_string() << " At position " <<  Lexer::pos << endl;
            Lexer::advance();
        }
    }
}
