#ifndef TREENODE_H
#define TREENODE_H

using namespace std;

class TreeNode {
    public:
        string key;
        vector <string> value;
        TreeNode(string key_node, vector <string> value_node);
        friend ostream& operator<<(ostream &out, TreeNode const& node);
    protected:
    private:
};

#endif // TREENODE_H
