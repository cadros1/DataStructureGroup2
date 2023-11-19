#include "HaffmanTree.h"

/**
 * @brief 对频率列表按权重从小到大进行排序
 * @param left 排序起始位置
 * @param right 排序结束位置
 * @author 高洪森
 */
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