#include "HaffmanTree.h"

/**
 * @brief HaffmanTree的构造函数
 * @param file 指向一个fstream对象的指针
 * @author 高洪森
*/
HaffmanTree::HaffmanTree(std::fstream* file,int choice){
    std::fstream f;
    f.open("output.bin", std::ios::in|std::ios::binary);
    switch(choice){
        case 1:
            this->calculateWeightFromFile(file);
            this->constructHaffmantree();
            this->encodeFromRoot(this->root,"");
            mapInit();
            encodeFile(file); 
            decodeFile(&f);
            break;
        case 2:
            //TODO
            break;
        default:
            throw "无效选项！";
            break;
    }

}

/**
 * @brief 从文件中读取字符并统计频率
 * @param file 一个fstream对象的指针
 * @author 高洪森
 */
void HaffmanTree::calculateWeightFromFile(std::fstream* file){
    if(!file->is_open()){
        throw "文件打开失败！可能是路径错误或文件不存在。";
    }
    file->seekg(0);
    char c;
    while(file->peek()!=EOF){
        file->get(c);
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

/**
 * @brief 输出字符统计数据至文件
 *       数据包括字符、频率及其哈夫曼编码，按频率从小到大排列
 * @author 
 */
void HaffmanTree::outputNodeListToFile(){
    //要求：将编码数据输出至..\resources\haffmanCode.txt
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
 * @brief 通过后序遍历释放哈夫曼树的内存
 *        释放后不要调用任何成员！！！
 * @author 杨峥
*/
void HaffmanTree::freeNode(HaffmanTree::Node* root){
    if(root == nullptr){
        return;
    }
    freeNode(root->leftSon);
    freeNode(root->rightSon);
    delete root;
}

/**
 * @brief 释放哈夫曼树的内存
 * @author 杨峥
 */
void HaffmanTree::free(){
    freeNode(this->root);
    delete this;
}


/**
 * @brief 对文件按获得的编码集进行编码
 * @author 董庆宇
*/
void HaffmanTree::encodeFile(std::fstream* file){
    //TODO
    file->seekg(0);
    std::vector<std::vector<char>> my_buffer;
    my_buffer.push_back(std::vector<char>(8));
    int buffer_count = 0;
    int bit_count = 0;
    char c;
    while (file->peek() != EOF)
    {
        file->get(c);
        std::string c_huffcode = char_map[c];
        for (int i = 0; i < c_huffcode.size(); i++)
        {
            my_buffer.at(buffer_count)[bit_count] = c_huffcode.at(i);
            bits_writtern_in++;
            if(bit_count == 7) {
                buffer_count++;
                my_buffer.push_back(std::vector<char>(8));
            }
            bit_count = (bit_count + 1) % 8;
        }
    }
    writeBitsToFile(my_buffer);
}

/**
 * @brief 对文件进行解码
 * @author 董庆宇
*/
void HaffmanTree::decodeFile(std::fstream* file){
    std::ofstream outfile("decode.txt", std::ios::out);
    if (! outfile.is_open())
    {
        throw "文件打开失败！可能是路径错误或文件不存在。";
    }
    else{
        std::string guess, read_in;
        char c;
        int total_bits = 0;
        while (!file->eof())
        {
            c = file->get();
            read_in.append(get8BIts(c));
            while(true)
            {
                guess.append(1, read_in.at(0));
                total_bits++;
                read_in.erase(0, 1);
                if (code_map.find(guess) != code_map.end())
                {
                    outfile.write((char*)&code_map[guess], 1);
                    guess.clear();
                    if (total_bits == bits_writtern_in) return;
                }
                if(read_in.size() == 0) break;
            }
        }
    }
    outfile.close();
}

/**
 * @brief 初始化字符到编码对应的map
 * @author 董庆宇
*/
void HaffmanTree::mapInit() {
    for (int i = 0; i < nodeList.size(); i++)
    {
        char the_char = nodeList[i]->data;
        std::string huff_code = nodeList[i]->code;
        char_map[the_char] = huff_code;
        code_map[huff_code] = the_char;
    }
}

/**
 * @brief 将bits写入文件，encodeFile的辅助函数
 * @author 董庆宇
*/
void HaffmanTree::writeBitsToFile(std::vector<std::vector<char>> my_buffer) {
    std::ofstream outfile("output.bin", std::ios::out | std::ios::binary);
    if (! outfile.is_open())
    {
        throw "文件打开失败！可能是路径错误或文件不存在。";
    }
    else{
        for(std::vector single_buff : my_buffer) {
            unsigned char set_bit = 1, my_8bits = 0;
            set_bit <<= 7;
            for (int i = 0; i < 8; i++) {
                if(single_buff[i] == '1') {
                    my_8bits |= set_bit;
                }
                set_bit >>= 1;
            }
            outfile.write((char *)&my_8bits, 1);
        }
    }
    outfile.close();
}

/**
 * @brief 将一个char转为string类的8bits
 * @author 董庆宇
*/
std::string HaffmanTree::get8BIts(char c) {
    char result[8];
    unsigned char compare_bit = 1;
    compare_bit <<= 7;
    for (size_t i = 0; i < 8; i++)
    {
        unsigned char before = c;
        unsigned char after = c | compare_bit;
        if (before == after) result[i] = '1';
        else result[i] = '0';
        compare_bit >>= 1;
    }
    std::string a(result);
    return a;
}
