#include <cmath>
#include <stack>
#include <string>
#include<iostream>
using namespace std;

stack<char> oper;
stack<double> number;  
 
int getIndex(char op) //建矩阵序号
{
	int index = 0;
	switch (op) {
	case '+':
		index = 0;
		break;
	case '-':
		index = 1;
		break;
	case '*':
		index = 2;
		break;
	case '/':
		index = 3;
		break;
	case '(':
		index = 4;
		break;
	case ')':
		index = 5;
		break;

	case '=':
		index = 6;
		break;
	default:
		break;
	}
	return index;
}

int getPrior(char op1, char op2) { //建立判断优先级的矩阵	
	int Prior[7][7] = {
		      {1,1,-1,-1,-1,1,1},
			  {1,1,-1,-1,-1,1,1},
			  {1,1,1,1,-1,1,1},
			  {1,1,1,1,-1,1,1},
			  {-1,-1,-1,-1,-1,0,2},
			  {1,1,1,1,2,1,1},
			  {-1,-1,-1,-1,-1,2,0},
	};  

	int index1 = getIndex(op1);
	int index2 = getIndex(op2);
	return Prior[index2][index1];
}

bool Operate(double num1, double num2, char op, double &temp) { //单步计算
	switch (op) {
	case '+':
		temp = num1 + num2;
		break;
	case '-':
		temp = num1 - num2;
		break;

	case '*':
		temp = num1 * num2;
		break;

	case '/':
		if (num2 == 0) {
			std::cout << "Invalid expression" << endl;
			return false;
		}
		else
			temp = num1 / num2;
		break;
	default:
		break;
   }
	return true;
}

double calculateAnswer(char exp[]) { //计算整体表达式
	int decimal = 0;
	int a = 0, b;
	double num1, num2;
	double temp_ans;
	double digit = 0;
	double result;
	oper.push('=');//栈底标识

	while (exp[a] != '=' || oper.top() != '=') { 
		if ((isdigit(exp[a])) || exp[a] == '.') { 
			digit = 0;  
			decimal = 0; 
			if (exp[a] == '.')
				decimal = 10;
			else
				digit = exp[a] - 48;
			     b = a + 1;

			while (isdigit(exp[b])||exp[b]=='.') {
				if (exp[b] == '.') {//小数的处理
					decimal = 10;
					b++;
					continue;
				}

				if (!decimal)  
					digit = digit * 10 + (exp[b] - 48);
				else {
					digit = digit + 1.0 * (exp[b] - 48) / decimal;  
					decimal *= 10;  
				}

				b++;
			}
			a = b; 
			number.push(digit);
		}

		else if (!isdigit(exp[a])&&exp[a]!='.') { 
			
			if (exp[0]=='-'||exp[a] == '('&&exp[a + 1] == '-') {
				digit = 0;
				number.push(digit);
			}

			switch (getPrior(exp[a], oper.top())) { //优先级比较
			case -1:
				oper.push(exp[a++]);
				break;
			case 0:
				oper.pop();
				a++;
				break;
			case 1:
				char op = oper.top(); 
				oper.pop();
				num2 = number.top();  
				number.pop();
				num1 = number.top();
				number.pop();
				if (Operate(num1, num2, op, temp_ans)) 
					number.push(temp_ans);  
				else
					return false;  
				break;
			}
		}
	}
	result = number.top(); 
	return result;
}

int main()
{
	int a, b;
	char input[200];
	char expression[200];
	double final_result;
	while (cin >> input) {                       
		for (a = 0, b = 0; input[a] != 0; a++) {   
			if (input[a] == ' ')
				continue;
			expression[b++] = input[a];
		}
		
		expression[b++] = '=';
		expression[b] = '\n';
		final_result = calculateAnswer(expression);
		std::cout << final_result << endl;
	}
	return 0;
}
