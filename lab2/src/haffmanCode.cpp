#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

#include "haffmanCode.h"
#include "HaffmanTree.h"

int main(){
    SetConsoleOutputCP(CP_UTF8);

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
                calculateWeightFromFile(tree,askForFileName());
                tree->sortList(0,tree->frequenceList.size()-1);
                outputFrequenceList(tree);
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

/**
 * @brief 从文件中读取字符并统计频率
 * @param tree Haffmantree变量的指针
 * @param fileName 文件名
 * @author 高洪森
 */
void calculateWeightFromFile(HaffmanTree* tree,std::string fileName){
    std::ifstream file(fileName,std::ios::in);

    if(!file.is_open()){
        std::cout<<"未找到指定文件";
        exit(0);
    }
    char c;
    while(file.peek()!=EOF){
        file.get(c);
        if(c=='\n'||c==' '){
            continue;
        }
        bool isExist=false;
        for(int i=0;i<tree->frequenceList.size();i++){
            if(tree->frequenceList[i].data==c){
                tree->frequenceList[i].weight++;
                isExist=true;
                break;
            }
        }
        if(!isExist){
            tree->frequenceList.push_back(HaffmanTree::Node{c,1,nullptr,nullptr});
        }
    }
    file.close();
}

/**
 * @brief 要求用户输入文件名并读取
 * @author 高洪森
 */
std::string askForFileName(){
    std::string fileName;
    std::cin.ignore(1000,'\n');
    std::cout<<"请输入文件名：";
    std::cin>>fileName;
    return fileName;
}

/**
 * @brief 输出字符频率列表
 * @param tree Haffmantree变量的指针
 * @author 高洪森
 */
void outputFrequenceList(HaffmanTree* tree){
    std::cout<<"字符\t频率\n";
    for(auto n:tree->frequenceList){
        std::cout<<n.data<<"\t"<<n.weight<<"\n";
    }
}