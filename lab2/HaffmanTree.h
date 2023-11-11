#ifndef _HAFFMANTREE_H_
#define _HAFFMANTREE_H_

#include <vector>

class HaffmanTree{
    public:
    typedef struct Node{
        char data;
        int weight;
        Node* leftSon;
        Node* rightSon;
    }Node;
    std::vector<HaffmanTree::Node> frequenceList;

    private:
    Node* root;
};

#endif
