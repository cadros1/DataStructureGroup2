#include <iostream>
#include <fstream>
#include <vector>

#include "haffmanCode.h"
#include "HaffmanTree.h"

int main(){
    HaffmanTree* tree;

    while(true){
        std::cout<<"=============================欢迎使用haffman编码器=============================\n";
        std::cout<<"1.统计文件中各字符频率并输出\n";
        std::cout<<"2.将原始文本编码并输出\n";
        std::cout<<"3.将编码后的文本解码并输出\n";
        std::cout<<"4.退出\n\n";
        std::cout<<"请输入选项代码: ";
        int choice;
        std::cin>>choice;
        switch(choice){
            case 1:
                tree=new HaffmanTree();
                calculateWeightFromFile(&(*tree).frequenceList,askForFileName());
                outputFrequenceList(&(*tree).frequenceList);
                break;
            case 4:
                exit(0);
                break;
            default:
                std::cout<<"选项错误！！！";
                exit(0);
                break;
        }
        std::cout<<"\n\n";
    }
}

void calculateWeightFromFile(std::vector<HaffmanTree::Node>* frequenceList,std::string fileName){
    std::ifstream file(fileName,std::ios::in);
    char c;
    while(file.peek()!=EOF){
        file.get(c);
        bool isExist=false;
        for(int i=0;i<(*frequenceList).size();i++){
            if((*frequenceList)[i].data==c){
                (*frequenceList)[i].weight++;
                isExist=true;
                break;
            }
        }
        if(!isExist){
            (*frequenceList).push_back(HaffmanTree::Node{c,1,nullptr,nullptr});
        }
    }
    file.close();
}

std::string askForFileName(){
    std::string fileName;
    std::cin.ignore(1000,'\n');
    std::cout<<"请输入文件名：";
    std::cin>>fileName;
    return fileName;
}

void outputFrequenceList(std::vector<HaffmanTree::Node>* frequenceList){
    std::cout<<"字符\t频率\n";
    for(auto n:*frequenceList){
        std::cout<<n.data<<"\t"<<n.weight<<"\n";
    }
}