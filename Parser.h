#ifndef PARSER_H
#define PARSER_H

using namespace std;

class Parser {
    public:
        int pos;
        LexerToken current_token;
        vector <LexerToken> toks;
        Parser(vector <LexerToken> tokens);
        void advance();
        Tree factor();
        void term();
        void expr();
    protected:

    private:
};

#endif // PARSER_H
