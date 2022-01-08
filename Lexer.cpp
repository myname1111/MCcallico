#include <iostream>
#include "LexerToken.h"
#include "Lexer.h"

using namespace std;

Lexer::Lexer(string text_to_be_analyzed){
    text = text_to_be_analyzed;
}
