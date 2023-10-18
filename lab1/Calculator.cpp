#include<iostream>
#include<stack>
using namespace std;

int isp(const char op);
int osp(const char op);
void handleOperator(const char inputOp);
void handleExit();

stack<double> numStack;
stack<char> opStack;

//author 高洪森
int main(){
    cout<<"\n===================欢迎使用计算器==================="<<endl;
    cout<<"\n在下方输入您的表达式并以\"=\"结尾，程序将自动为此表达式求值"<<endl;
    cout<<"注意，仅接受整数与+ - * / % ^ &七种运算符，空格将被忽略，其余符号将导致错误"<<endl;

    for(;;){
        cout<<"\n请输入您的表达式：";
        for(;;){
            char expression;
            cin>>expression;
            if(expression>='0'&&expression<='9'){
                cin.putback(expression);
                double number;
                cin>>number;
                numStack.push(number);
            }
            else if(expression=='+'||expression=='-'||expression=='*'||expression=='/'||expression=='%'||expression=='^'||expression=='&'||expression=='='){
                handleOperator(expression);
            }
            else{
                cout<<"\n检查到非法字符，计算中止。您希望重新开始输入吗？(Y/N)： ";
                numStack=stack<double>();
                opStack=stack<char>();
                handleExit();
                break;
            }
            //！！！仅在handleOperator未完成时使用。当handleOperator中定义了'='的处理后，应删除掉此条if语句
            if(expression=='='){
                cout<<"计算结果为："<<numStack.top()<<endl;
                cout<<"\n您希望继续使用计算器吗？(Y/N)： ";
                numStack=stack<double>();
                opStack=stack<char>();
                handleExit();
                break;
            }
            if(cin.peek()=='\n'){
                cout<<"\n未检查到结束符\'=\'，计算中止。您希望重新开始输入吗？(Y/N)：";
                numStack=stack<double>();
                opStack=stack<char>();
                handleExit();
                break;
            }
        }
    }
}

/*当计算结束时处理是否退出

author 高洪森*/
void handleExit(){
    char answer;
    cin>>answer;
    if(answer=='Y'||answer=='y')
        return;
    else if(answer=='N'||answer=='n'){
        cout<<"感谢您的使用。";
        exit(1);
    }
    else{
        cout<<"输入错误，程序已退出。";
        exit(0);
    }
}

/*根据输入的操作符进行不同的处理

author 高洪森*/
void handleOperator(const char inputOp){
    if(opStack.empty()){
        opStack.push(inputOp);
        return;
    }
    else if(isp(opStack.top())<osp(inputOp)){
        opStack.push(inputOp);
        return;
    }
    else if(isp(opStack.top())>osp(inputOp)){
        double num2=numStack.top();
        numStack.pop();
        double num1=numStack.top();
        numStack.pop();
        switch(opStack.top()){
            case '+':
                numStack.push(num1+num2);
                break;
            case '-':
                //TODO
            case '*':
                //TODO
            case '/':
                //TODO
            case '%':
                //TODO
            case '^':
                //TODO
            case '&':
                //TODO
            case '=':
                return;
            default:
                //TODO
                //这里随便写，因为前面已经校验过了，理论上不会执行到这里
                break;
        }
        opStack.pop();
        handleOperator(inputOp);
    }
    else if(isp(opStack.top())==osp(inputOp)){
        opStack.pop();
        return;
    }
}

/*返回操作符的栈内优先级

author 高洪森*/
int isp(const char op){
    switch(op){
        case '+':
            return 3;
        case '-':
            return 3;
        case '*':
            return 5;
        case '/':
            return 5;
        case '%':
            return 5;
        case '(':
            return 1;
        case ')':
            return 8;
        case '^':
            return 7;
        case '&':
            return 7;
        case '=':
            return 0;
        default:
            return 0;
    }
}

/*返回该操作符的栈外优先级
author 高洪森*/
int osp(const char op){
    switch(op){
        case '+':
            return 2;
        case '-':
            return 2;
        case '*':
            return 4;
        case '/':
            return 4;
        case '%':
            return 4;
        case '(':
            return 8;
        case ')':
            return 1;
        case '^':
            return 6;
        case '&':
            return 6;
        case '=':
            return 0;
        default:
            return 0;
    }
}
