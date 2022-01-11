#ifndef TREENODE_H
#define TREENODE_H

#include "LexerToken.h"

using namespace std;

class TreeNode {
    public:
        string key;
        vector <LexerToken> value;
        TreeNode(string key_node, vector <LexerToken> value_node);
        friend ostream& operator<<(ostream &out, TreeNode const& node);
    protected:
    private:
};

#endif // TREENODE_H
