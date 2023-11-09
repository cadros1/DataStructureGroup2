#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_


bool handleOperator(const char inputOp, bool isNum);
void handleExit();
double RootOf(double num1, double num2); 
double f(double x, double power, double num);
double df(double x, double power);
bool notNegRootCond(double num);
void getTwoNumbers(double *num1,double *num2);
void unknownExpressionException();
void judge_last_isNum(const char lastpre, bool& isNum);//
int isp(const char op);
int osp(const char op);


#endif