#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "LexerToken.h"
#include "IllegalCharError.h"
using namespace std;

class Lexer {
    public:
        string text;
        std::vector<LexerToken> tokens;
        IllegalCharError error;
        int pos;
        char current_char;
        Lexer(string text_to_be_analyzed);
        void advance();
        bool is_alphabet(char in_char);
        void make_token();
        void make_number();
        void make_name();
    protected:

    private:
};

#endif // LEXER_H
