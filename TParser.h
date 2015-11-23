#pragma once
#include "TStack.h"
#include <string.h>
#include <cstdlib>
#define MaxLen 201 //Строка будет, по факту, длины 200; один элемент необходим для знака окончания строки '\о'
//---
class TParser
{
	char inf[MaxLen];				//Массив для префиксной формы
	char postf[MaxLen];				//Массив для постфиксной формы	
	TStack<double> st_double;			
	TStack<char> st_char;			//Надо будет чистить его
	bool IsOperation(char ch) {		//Знак ли это арифметический?
		if ((ch == '+') || (ch == '-') || (ch == '*') || (ch == '/')) {
			return true;
		}
		else 
			return false;
	}
//----
	bool IsNumber(char ch) {		//Число ли это?
		if ((!IsOperation(ch)) && (ch != '(') && (ch != ')'))
			return true;
		else
			return false;
	}
//----
	int Priority(char ch) {			//Умение определять приоритет принимаего знака
		int prior = 0;
		switch (ch){
			case '(': prior = 0;
			case ')': prior = 0; break;
			case '+':;
			case '-': prior = 1; break;
			case '*':;
			case '/': prior = 2; break;
			default: prior = -1;
			break;
		}
		return prior;
	}
//----
public: 
	TParser(char *s = NULL) : st_double(100), st_char(100) {
		if (s == NULL) 
			inf[0] = '\0';
		else 
			strcpy(inf, s);
	}
//----
	~TParser() {
		delete[] inf;
		delete[] postf;
	}
//----
	int BracketDetector(char *str) {		//Закрыты ли все скобки в строке, полученной от пользователя
		TStack <char> stack(MaxLen);
		int i = 0;
		while (str[i] != '\0') {
			if (str[i] == '(')
				stack.Push('(');
			if (str[i] == ')') {
				if ( stack.IsEmpty() )
					return 0;
				stack.Pop();
			}
			i++;
		}
		if (!stack.IsEmpty())
			return 0;
		return 1;
	}
//----
	void TakeString(char *s) {		//Занести выражение в инфиксном варианте
		if (!BracketDetector(s))	//Количество скобок проверяется
			throw !BracketDetector(s);		
		else
			if (s == NULL) inf[0] = '\0';
			else strcpy(inf, s);
	}
//----
	void inftopost() {				//Сама операция трансфера в постфикс из инфекса
		int i = 0;
		int j = 0;
		st_char.Push('=');
		while (inf[i] != '\0') {
			if (IsNumber(inf[i])) {
				postf[j++] = inf[i];
			}
			else 
			if (inf[i] == '(') {
				st_char.Push('(');
			}
			else
			if (inf[i] == ')') {
				char tmp = st_char.Pop();
				while (tmp != '(') {
					postf[j++] = tmp;
					tmp = st_char.Pop();
				}
			}
			else
			if (IsOperation(inf[i])) {
				char tmp = st_char.Pop();
				while (Priority(tmp) >= Priority(inf[i])) {
					postf[j++] = tmp;
					tmp = st_char.Pop();
				}
				st_char.Push(tmp);
				st_char.Push(inf[i]);
			}
			i++;
					}
		return;
	}
	//----
	double CalcPostf() {
		int i = 0;					//Счетчик
		st_double.clear();
		while ((postf[i] != '\0') && (postf[i] != '=')) {
			if (IsNumber(postf[i]))
				st_double.Push(postf[i] - '0');
			if (IsOperation(postf[i])) {
				double op2 = st_double.Pop();
				double op1 = st_double.Pop();
				switch (postf[i]) {
				case '+':st_double.Push(op1 + op2);
					break;
				case '-':st_double.Push(op1 - op2);
					break;
				case '*':st_double.Push(op1*op2);
					break;
				case '/':st_double.Push(op1 / op2);
					break;
				default:
					throw - 1;
				}
			}
			i++;
		}
		return st_double.Pop();
	}
	//----
	double ExNum(char* s, int& len) {
		double tmp = atof(s);
		int i = 0;
		while (IsNumber(s[i]))
			i++;
		len = i;
		return tmp;
	}
	//----
	double CalcP() {
		st_double.clear();
		st_char.clear();
		int i = 0;
		int len = 0;
		st_char.Push('=');
		while (inf[i] != '0') {
			if (IsNumber(inf[i])) {
				double tmp = ExNum(&inf[i], len);
				st_double.Push(tmp);
				i += len - 1;
			}
			else
				if (inf[i] == '(')
					st_char.Push('(');
				else
					if (inf[i] == ')') {
						char tmp = st_char.Pop();
						while (tmp != '(') {
							double op2 = st_double.Pop();
							double op1 = st_double.Pop();
							switch (tmp) {
							case '+':st_double.Push(op1 + op2);
								break;
							case '-':st_double.Push(op1 - op2);
								break;
							case '*':st_double.Push(op1*op2);
								break;
							case '/':st_double.Push(op1 / op2);
								break;
							default:
								throw - 1;
							}
							tmp = st_char.Pop();
						}
					}
					else 
						if (IsOperation(inf[i])) {
							char tmp = st_char.Pop();
							while (Priority(tmp) >= Priority(inf[i])) {
								double op2 = st_double.Pop();
								double op1 = st_double.Pop();
								switch (tmp) {
									case '+':st_double.Push(op1 + op2);
										break;
									case '-':st_double.Push(op1 - op2);
										break;
									case '*':st_double.Push(op1*op2);
										break;
									case '/':st_double.Push(op1 / op2);
										break;
									default:
										throw - 1;
								}
								tmp = st_char.Pop();
							}
							st_char.Push(tmp);
							st_char.Push(inf[i]);
					}
					i++;
		}
		char tmp = st_char.Pop();
		while (tmp != '=') {
			double op2 = st_double.Pop();
			double op1 = st_double.Pop();
			switch (tmp) {
				case '+':st_double.Push(op1 + op2);
					break;
				case '-':st_double.Push(op1 - op2);
					break;
				case '*':st_double.Push(op1*op2);
					break;
				case '/':st_double.Push(op1 / op2);
					break;
				default:
					throw - 1;
			}
			tmp = st_char.Pop();
		}
		return st_double.Pop();
	}
};

