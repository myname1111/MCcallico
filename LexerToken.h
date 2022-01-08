#ifndef LEXERTOKEN_H
#define LEXERTOKEN_H
using namespace std;


class LexerToken {
    public:
        string name;
        string value;
        LexerToken(string token_name, string token_value);
        LexerToken();
        friend ostream& operator<<(ostream &out, LexerToken const& tok);
    protected:
    private:
};

#endif // LEXERTOKEN_H
