#ifndef TREE_H
#define TREE_H

using namespace std;

class Tree {
    public:
        string key;
        vector <TreeNode> value_node_leaf;
        vector <Tree> value_node;
        Tree(string key_node, vector <TreeNode> value_node);
        Tree(string key_node, vector <Tree> value_node);
    protected:
    private:
};

#endif // TREE_H
