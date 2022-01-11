#include <iostream>
#include <vector>
#include "LexerToken.h"
#include "TreeNode.h"

using namespace std;

TreeNode::TreeNode(string key_node, vector <LexerToken> value_node) {
    TreeNode::key = key_node;
    TreeNode::value = value_node;
}

ostream& operator<<(ostream &out, TreeNode const& node){
    out << node.key << " : {";
    for (int i = 0;i < node.value.size();i++)
        out << node.value.at(i) << ", ";
    out << "}";
    return out;
}
