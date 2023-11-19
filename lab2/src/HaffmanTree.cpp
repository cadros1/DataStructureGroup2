#include "HaffmanTree.h"

/**
 * @brief 对频率列表按权重从小到大进行快速排序
 * @param left 排序起始位置
 * @param right 排序结束位置
 * @author 高洪森
 */
void HaffmanTree::sortList(int left,int right){
    if(left>=right){
        return;
    }

    int base;
    if(this->frequenceList[left].weight>=this->frequenceList[right].weight){    //取左值右值中值的中间值为基准值
        if(this->frequenceList[left].weight>=this->frequenceList[(left+right)/2].weight){
            if(this->frequenceList[right].weight>=this->frequenceList[(left+right)/2].weight){
                base=right;
            }else{
                base=(left+right)/2;
            }
        }else{
            base=left;
        }
    }else if(this->frequenceList[right].weight>=this->frequenceList[(left+right)/2].weight){
        if(this->frequenceList[left].weight>=this->frequenceList[(left+right)/2].weight){
            base=left;
        }else{
            base=(left+right)/2;
        }
    }else{
        base=right;
    }
    Node baseNode=this->frequenceList[base];
    std::swap(this->frequenceList[base],this->frequenceList[left]);     //将基准值放到最左边

    int i=left;
    int j=right;
    while(i<j){
        for(;i<j;j--){
            if(this->frequenceList[j].weight<baseNode.weight){
                this->frequenceList[i]=this->frequenceList[j];
                break;
            }
        }
        for(;i<j;i++){
            if(this->frequenceList[i].weight>baseNode.weight){
                this->frequenceList[j]=this->frequenceList[i];
                break;
            }
        }
    }
    this->frequenceList[i]=baseNode;
    sortList(left,i-1);
    sortList(i+1,right);
}