#include "HaffmanTree.h"

void HaffmanTree::sortList(int left,int right){
    if(left>=right){
        return;
    }

    Node base=this->frequenceList[left];
    int i=left;
    int j=right;
    Node temp;
    while(i<j){
        for(;i<j;j--){
            if(this->frequenceList[j].weight<base.weight){
                std::swap(this->frequenceList[i],this->frequenceList[j]);
                break;
            }
        }
        for(;i<j;i++){
            if(this->frequenceList[i].weight>base.weight){
                std::swap(this->frequenceList[i],this->frequenceList[j]);
                break;
            }
        }
    }

    sortList(left,i-1);
    sortList(i+1,right);
}