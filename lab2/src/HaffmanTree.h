#ifndef _HAFFMANTREE_H_
#define _HAFFMANTREE_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

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
    HaffmanTree(std::fstream* file,int choice);
    void outputNodeListToConsole();
    void outputNodeListToFile();

    void freeNode(HaffmanTree::Node* root);
    void free();
    

    private:
    bool isSorted=false;
    Node* root;
    std::map<char, std::string> char_map;
    std::map<std::string, char> code_map;
    int bits_writtern_in = 0;

    void encodeFile(std::fstream* file);
    void decodeFile(std::fstream* file);
    void calculateWeightFromFile(std::fstream* file);
    void sortList(int left,int right);
    void constructHaffmantree();
    void encodeFromRoot(Node* root,std::string code);
    void mapInit();
    void mapInit(std::string file);
    void writeBitsToFile(std::vector<std::vector<char>> my_buffer);
    std::string get8BIts(char c);
    void outputMapToFile();
};

#endif
