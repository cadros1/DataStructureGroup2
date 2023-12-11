#include "haffmanCode.h"

int main(){
    SetConsoleOutputCP(CP_UTF8);

    HaffmanTree* tree;
    std::cout<<"=============================欢迎使用haffman编码器=============================\n";
    std::cout<<"1.对文件进行编码\n";
    std::cout<<"2.解码文件以获取原始文本\n";
    std::cout<<"3.退出\n";
    while(true){
        std::cout<<"\n请输入选项编号: ";
        int choice;
        std::fstream file;
        std::cin>>choice;
        switch(choice){
            case 1:
                file.open(askForFileName(),std::ios::in|std::ios::out|std::ios::binary);
                try{
                    tree=new HaffmanTree(&file,1);
                    std::cout<<"编码成功！\n1.输出编码数据至控制台\t2.输出编码数据至文件并获取压缩率\n键入选项编号以继续：";
                    std::cin.ignore(1000,'\n');
                    std::cin>>choice;
                    std::cout<<"\n";
                    switch(choice){
                        case 1:
                            tree->outputNodeListToConsole();
                            break;
                        case 2:
                            tree->outputNodeListToFile();
                            break;
//                         case 3:
//                             tree->encodeFile(&file);
//                             tree->outputMapToFile();
                            break;
                        default:
                            std::cout<<"\n无效选项！将默认输出编码数据至控制台\n";
                            tree->outputNodeListToConsole();
                            break;
                    }
                    tree->free();
                }catch(const std::exception& e){
                    std::cout<<e.what()<<"\n";
                }catch(const char* e){
                    std::cout<<e<<"\n";
                }
                break;
            case 2:
                try{
                    file.open(askForFileName(),std::ios::in|std::ios::out|std::ios::binary);
                    tree=new HaffmanTree(&file,2);
                    std::cout<<"解码后文本已输出至../decode.txt，请检查\n";
                    break;
                }catch(const char* e){
                    std::cout<<e<<"\n";
                }catch(const std::exception& e){
                    std::cout<<e.what()<<"\n";
                }
            case 3:
                exit(0);
                break;
            default:
                std::cout<<"选项错误！！！";
                break;
        }
        std::cout<<"\n\n";
    }
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