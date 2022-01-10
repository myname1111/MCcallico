#include <iostream>
#include <vector>
#include "TreeNode.h"
#include "Tree.h"

using namespace std;

Tree::Tree(string key_node, vector <TreeNode> value_node) {
    Tree::key = key_node;
    Tree::value_node_leaf = value_node;
}

Tree::Tree(string key_node, vector <Tree> value_node) {
    Tree::key = key_node;
    Tree::value_node = value_node;
}
