#pragma once
#include "TStack.h"
#include <string.h>
#define MaxLen 201 //������ �����, �� �����, ����� 200; ���� ������� ��������� ��� ����� ��������� ������ '\�'
//---
class TParser
{
	char inf[MaxLen];				//������ ��� ���������� �����
	char postf[MaxLen];				//������ ��� ����������� �����	
	TStack<double> st_double;
	TStack<char> st_char;			//���� ����� ������� ���
	bool IsOperation(char ch) {		//���� �� ��� ��������������?
		if ((ch == '+') || (ch == '-') || (ch == '*') || (ch == '/')) {
			return true;
		}
		else return false;
	}
//----
	bool IsNumber(char ch) {		//����� �� ���?
		if ((!IsOperation(ch)) && (ch != '(') && (ch != ')'))
			return true;
		else
			return false;
	}
//----
	int priority(char ch) {			//������ ���������� ��������� ���������� �����
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
		if (s == NULL) inf[0] = '\0';
		else strcpy(inf, s);
	}
//----
	~TParser() {
		delete[] inf;
		delete[] postf;
	}
//----
	int BracketDetector(char *str) {		//������� �� ��� ������ � ������, ���������� �� ������������
		TStack <char> stack(10);
		int i = 0;
		while (str[i] != '\0') {
			if (str[i] == '(')
				stack.Push('(');
			if (str[i] == ')') {
				if (stack.IsEmpty())
					return 0;
				stack.PoP();
			}
			i++;
		}
		if (!stack.IsEmpty())
			return 0;
		return 1;
	}
//----
	void TakeString(char *s) {		//������� ��������� � ��������� ��������
		if (!BracketDetector(s))	//���������� ������ �����������
			throw !BracketDetector(s);		
		else
			if (s == NULL) inf[0] = '\0';
			else strcpy(inf, s);
	}
//----
	void inftopost() {				//���� �������� ��������� � �������� �� �������
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
						char tmp = st_char.PoP();
						while (tmp != '(') {
							postf[j++] = tmp;
							tmp = st_char.PoP();
						}
					}
					else
						if (IsOperation(inf[i])){
							char tmp = st_char.PoP();
							while (priority(tmp) >= priority(inf[i])) {
								postf[j++] = tmp;
								tmp = st_char.PoP();
							}
							st_char.Push(tmp);
							st_char.Push(inf[i]);
						}
			i++;
		}
		return;
	}
};

