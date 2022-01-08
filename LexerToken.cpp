#include <iostream>

using namespace std;
#include "LexerToken.h"

LexerToken::LexerToken(string token_name, string token_value){
    LexerToken::name = token_name;
    LexerToken::value = token_value;
}
ostream& operator<<(ostream &out, LexerToken const& tok){
    out << tok.name << " : " << tok.value;
    return out;
}
