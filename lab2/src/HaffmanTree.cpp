#include "HaffmanTree.h"

HaffmanTree::HaffmanTree(std::string filename){
    this->calculateWeightFromFile(filename);
    this->constructHaffmantree();
    this->encodeFromRoot(this->root,"");
}

/**
 * @brief 从文件中读取字符并统计频率
 * @param tree Haffmantree变量的指针
 * @param fileName 文件名
 * @author 高洪森
 */
void HaffmanTree::calculateWeightFromFile(std::string fileName){
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
        for(int i=0;i<this->nodeList.size();i++){
            if(this->nodeList[i]->data==c){
                this->nodeList[i]->weight++;
                isExist=true;
                break;
            }
        }
        if(!isExist){
            this->nodeList.push_back(new HaffmanTree::Node{c,1,"",nullptr,nullptr});
        }
    }
    file.close();
}

/**
 * @brief 对频率列表按权重从小到大进行快速排序
 * @param left 排序起始位置
 * @param right 排序结束位置
 * @author 高洪森
 */
void HaffmanTree::sortList(int left,int right){
    if(left>=right){
        this->isSorted=true;
        return;
    }

    int base;
    if(this->nodeList[left]->weight>=this->nodeList[right]->weight){    //取左值右值中值的中间值为基准值
        if(this->nodeList[left]->weight>=this->nodeList[(left+right)/2]->weight){
            if(this->nodeList[right]->weight>=this->nodeList[(left+right)/2]->weight){
                base=right;
            }else{
                base=(left+right)/2;
            }
        }else{
            base=left;
        }
    }else if(this->nodeList[right]->weight>=this->nodeList[(left+right)/2]->weight){
        if(this->nodeList[left]->weight>=this->nodeList[(left+right)/2]->weight){
            base=left;
        }else{
            base=(left+right)/2;
        }
    }else{
        base=right;
    }
    Node* baseNode=this->nodeList[base];
    std::swap(this->nodeList[base],this->nodeList[left]);     //将基准值放到最左边

    int i=left;
    int j=right;
    while(i<j){
        for(;i<j;j--){
            if(this->nodeList[j]->weight<baseNode->weight){
                this->nodeList[i]=this->nodeList[j];
                break;
            }
        }
        for(;i<j;i++){
            if(this->nodeList[i]->weight>baseNode->weight){
                this->nodeList[j]=this->nodeList[i];
                break;
            }
        }
    }
    this->nodeList[i]=baseNode;
    sortList(left,i-1);
    sortList(i+1,right);
}

/**
 * @brief 输出字符统计数据至控制台
 *        数据包括字符、频率及其哈夫曼编码，按频率从小到大排列
 * @author 高洪森
 */
void HaffmanTree::outputNodeListToConsole(){
    std::cout<<"字符\t频率\t编码\n";
    for(auto n:this->nodeList){
        std::cout<<n->data<<'\t'<<n->weight<<'\t'<<n->code<<'\n';
    }
}

void HaffmanTree::outputNodeListToFile(std::string filename){
    //要求：将编码数据输出至..\resources\haffmanCode.txt
    //文本要体现编码自哪个文件
    //TODO


}

/**
 * @brief 根据已排序的频度集构建哈夫曼树
 * @author 高洪森
 */
void HaffmanTree::constructHaffmantree(){
    if(this->isSorted==false){
        this->sortList(0,this->nodeList.size()-1);
        this->isSorted=true;
    }

    std::vector<Node*> list=this->nodeList;

    while(list.size()>1){
        Node* newNode=new Node;
        newNode->leftSon=list[0];
        newNode->rightSon=list[1];
        newNode->weight=list[0]->weight+list[1]->weight;
        list.erase(list.begin(),list.begin()+2);
        if(list.size()==0){      //如果组合后的新节点为唯一节点，则在插入后直接退出循环
            list.push_back(newNode);
            break;
        }
        bool isInsert=false;
        for(std::vector<HaffmanTree::Node*>::iterator i=list.begin();i!=list.end();i++){
            if((*i)->weight>=newNode->weight){     //将新节点插入到合适位置以保持列表有序，便于插入
                list.insert(i,newNode);
                isInsert=true;
                break;
            }
        }
        if(!isInsert){      //如果遍历结束后还未插入，说明所有节点权重都小于新节点，将新节点插入到列表末尾
            list.push_back(newNode);
        }
    }

    this->root=list[0];
    encodeFromRoot(this->root,"");
}

/**
 * @brief 根据构建好的哈夫曼树进行编码
 * @author 高洪森
*/
void HaffmanTree::encodeFromRoot(Node* root,std::string code){
    if(root->leftSon==nullptr&&root->rightSon==nullptr){
        root->code=code;
        return;
    }else{
        if(root->leftSon!=nullptr){
            encodeFromRoot(root->leftSon,code+"0");
        }
        if(root->rightSon!=nullptr){
            encodeFromRoot(root->rightSon,code+"1");
        }
    }
}

/**
 * @brief 释放哈夫曼树的内存
 *        释放后不要调用任何成员！！！
 * @author 高洪森
*/
void HaffmanTree::free(){
    for(int i=0;i<this->nodeList.size();i++){
        delete(this->nodeList[i]);
    }
    delete(this);
}