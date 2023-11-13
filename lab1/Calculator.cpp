#include<iostream>
#include<stack>
#include<math.h>
#include<cmath>

#include"Calculator.h"

using namespace std;

stack<double> numStack;
stack<char> opStack;

int main(){
    cout<<"\n===================欢迎使用计算器==================="<<endl;
    cout<<"\n在下方输入您的表达式并以\"=\"结尾，程序将自动为此表达式求值"<<endl;
    cout<<"注意，仅接受整数与+ - * / % ^ &七种运算符，空格将被忽略，其余符号将导致错误"<<endl;

    for(;;){
        cout<<"\n请输入您的表达式：";
	    char expression='a';
        char lastPre=expression;
        bool isNum = false;
        for(;;lastPre=expression){
            //judge_last_isNum(lastPre, isNum);
            cin>>expression;
            if(expression>='0'&&expression<='9'){
                cin.putback(expression);
                double number;
                cin>>number;
                numStack.push(number);
            }
            else if(expression=='+'||expression=='-'||expression=='*'||expression=='/'
                    ||expression=='%'||expression=='^'||expression=='&'||expression=='='
                    ||expression=='('||expression==')'){
                //何旭瑞
		        if((lastPre <'0'|| lastPre>'9')&&expression!='-'&&expression!='('&&lastPre!=')'){
			        unknownExpressionException();
                    break;
                }
                if(expression=='-') {
                    judge_last_isNum(lastPre, isNum);
                    if (isNum == false && lastPre != ')'){
                        numStack.push(0);
                    }
                    if (isNum == false && !(lastPre == 'a' || lastPre == '(') && lastPre != ')'){
                        unknownExpressionException();
                        break;
                    }
                }
                if(! handleOperator(expression, isNum)) {
                    unknownExpressionException();
                    break;
                }
            }
            else{
                unknownExpressionException();
                break;
            }
            if(expression=='='){
                if(cin.peek()!='\n'){
                    unknownExpressionException();
                    break;
                }
                if(numStack.size()!=1){
                    unknownExpressionException();
                    break;
                }
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

/**
 * @brief 当需要报错的时候调用此函数，询问用户是否重新输入
 * @author 高洪森
 */
void unknownExpressionException(){
    cout<<"\n检查到不正确表达式，计算中止。您希望重新开始输入吗？(Y/N)： ";
    numStack=stack<double>();
    opStack=stack<char>();
    handleExit();
    return;
}

/**
 * @brief 结束一次计算时，调用方首先应打印出结束语句并询问用户是否再次计算，然后再调用此函数
 * @author 高洪森
 */
void handleExit(){
    char answer;

    cin.ignore(1000,'\n');
    cin>>answer;
    cin.ignore(1000,'\n');
    if(answer=='Y'||answer=='y'){
        return;
    }
    else if(answer=='N'||answer=='n'){
        cout<<"感谢您的使用。";
        exit(1);
    }
    else{
        cout<<"输入错误，程序已退出。";
        exit(0);
    }
}

/**
 * @brief 从栈中取出两个数，分别赋值给num1和num2
 * @param num1 用于接收第一个数的指针
 * @param num2 用于接收第二个数的指针
 * @author 高洪森
 */
void getTwoNumbers(double *num1,double *num2){
    *num2=numStack.top();
    numStack.pop();
    *num1=numStack.top();
    numStack.pop();
}

/**
 * @brief 处理读取到的运算符
 * @author 高洪森
 */
bool handleOperator(const char inputOp, bool isNum){
    if(opStack.empty()){
        opStack.push(inputOp);
        return true;
    }
    else if(isp(opStack.top())<osp(inputOp)){
        opStack.push(inputOp);
        return true;
    }
    else if(isp(opStack.top())>osp(inputOp)){
        double num1,num2;
        char opInStack=opStack.top();
        opStack.pop();
        switch(opInStack){
            case '+':
                getTwoNumbers(&num1,&num2);
                numStack.push(num1+num2);
                break;
            case '-':
                getTwoNumbers(&num1,&num2);
                numStack.push(num1-num2);
                break;
            case '*':
                getTwoNumbers(&num1,&num2);
                numStack.push(num1*num2);
                break;
            case '/':
                getTwoNumbers(&num1,&num2);
                numStack.push(num1/num2);
                break;
            case '%':
                getTwoNumbers(&num1,&num2);
                numStack.push(fmod(num1,num2));
                break;
            case '^':
                getTwoNumbers(&num1,&num2);
                numStack.push(pow(num1, num2));
                break;
            case '&':
                getTwoNumbers(&num1,&num2);
                if ((num1 < 0) && (notNegRootCond(num2))){   
                    return false;
                }
                numStack.push(RootOf(num1, num2));
                break;
            case '(':
                return true;
            case ')':
                return true;
            case '=':
                return true;
            default:
                //这里无所谓，因为前面已经校验过了，理论上不会执行到这里
                break;
        }
        handleOperator(inputOp, isNum);
        return true;
    }
    else if(isp(opStack.top())==osp(inputOp)){
        opStack.pop();
        return true;
    }
    return false;
}

/**
 * @brief 返回给定运算符的栈内优先级
 * @param op 运算符
 * @author 高洪森
*/
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

/**
 * @brief 返回给定运算符的栈外优先级
 * @param op 运算符
 * @author 高洪森
 */
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

/**
 * @brief 返回num1开num2次方根
 * @param num1 底数
 * @param num2 指数
 * @author 董庆宇
 */
double RootOf(double num1, double num2) {
    double guess = 2.0;

    while (fabs(num1 - pow(guess, num2)) > 0.000000001){
        double pre = guess;
        guess = guess - f(guess, num2, num1) / df(guess, num2);
        if (pre == guess){
            return guess;
        }
        
    }

    return guess;
} 

/**
 * @brief RootOf辅助函数
 * @author 董庆宇
 */
double f(double x, double power, double num) {
    return pow(x, power) - num;
}

/**
 * @brief RootOf辅助函数
 * @author 董庆宇
 */
double df(double x, double power) {
    return power * pow(x, (power-1));
}

/**
 * @brief 返回num次方是否可开负数的根
 * @author 董庆宇
 */
bool notNegRootCond(double num) {
    double numerator = 1;
    int denominator = num;

    while (numerator - (int)numerator > 0.000001){
        numerator *= 10;
        denominator *= 10;
    }
    while ((int)numerator % 2 == 0 && denominator % 2 == 0){
        numerator /= 2;
        denominator /= 2;
    }

    if (denominator % 2 == 0){
        return true;
    }
    return false;
}

/**
 * @brief 判断上一字符是否为数字
 * @author 高洪森
*/
void judge_last_isNum(const char lastpre, bool& isNum) {
    if(lastpre>='0' && lastpre<='9') {
        isNum = true;
    }
    else {
        isNum = false;
    }
}