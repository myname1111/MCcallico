#ifndef LEXER_H
#define LEXER_H
using namespace std;

class Lexer {
    public:
        string text;
        LexerToken tokens[1000];
        Lexer(string text_to_be_analyzed);
    protected:

    private:
};

#endif // LEXER_H
