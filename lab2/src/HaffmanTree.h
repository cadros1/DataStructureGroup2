#ifndef _HAFFMANTREE_H_
#define _HAFFMANTREE_H_

#include <vector>
#include <map>

class HaffmanTree{
    
    public:
    typedef struct Node{
        char data;
        int weight;
        Node* leftSon;
        Node* rightSon;
    }Node;

    private:
    Node* root;
    map<char, int> char_map;

    public:
    std::vector<HaffmanTree::Node> frequenceList;

    HaffmanTree();
    HaffmanTree(string file);
    void sortList(int left,int right);
    void buildTree(std::string filename);
    
};

#endif
