#ifndef _HAFFMANTREE_H_
#define _HAFFMANTREE_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/**
 * @brief 哈夫曼树
 * 在创建时请调用new来创建，并在生命周期结束后手动调用HaffmanTree::free()来完全释放内存
 * @author 高洪森
*/
class HaffmanTree{
    public:
    typedef struct Node{
        char data;
        int weight;
        std::string code;
        Node* leftSon;
        Node* rightSon;
    }Node;
    std::vector<HaffmanTree::Node*> nodeList;

    HaffmanTree(std::string filename);
    void calculateWeightFromFile(std::string fileName);
    void sortList(int left,int right);
    void constructHaffmantree();
    void outputNodeListToConsole();
    void outputNodeListToFile(std::string filename);
    void free();
    

    private:
    bool isSorted=false;
    Node* root;
    
    void encodeFromRoot(Node* root,std::string code);
};

#endif
