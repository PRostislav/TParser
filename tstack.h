#pragma once

template <class T>
class TStack
{
	int MaxSize;					//������������ ������ �����
	int Index;						//������ �������� ��������
	T *mas;							//��������� �� ������ ���������
public:
//-----
	TStack(int len = 25){			//�����������
		if (len <= 0) throw len;
		MaxSize = len;
		Index = -1;
		mas = new T[MaxSize];	
	}
//-----
	~TStack() { delete[] mas; }		//����������
	TStack(const TStack& stack){	//����������� �����������
		MaxSize = stack.MaxSize;
		Index = stack.Index;
		mas = new T[MaxSize];
		for (int i = 0; i <= Index; i++)
			mas[i] = stack.mas[i];
	}
//-----
	bool IsEmpty(){					//�������� �� �������
		return (Index == -1);
	}
//-----
	bool IsFull(){					//�������� �� �������
		return (Index == MaxSize - 1);
	}
//-----
	T Top(){						//��� ����� ������ �����
		if (Index < 0) throw Index;
		return mas[Index];
	}
//-----
	T Pop(){						//�������� ������� �� �����
		if (Index < 0) throw Index;
		return mas[Index--];
	}
//-----
	void Push(const T Elem){		//�������� ������� � ����
		if (Index == MaxSize - 1) throw Index;
		mas[++Index] = Elem;
		return;
	}
//-----
	TStack operator=(const TStack& stack){//�������� =
		MaxSize = stack.MaxSize;
		Index = stack.Index;
		mas = new T[MaxSize];
		for (int i = 0; i <= Index; i++)
			mas[i] = stack.mas[i];
		return *this;
	}
//-----
	int BracketDetector(char *str){		//������� �� ��� ������ � ������, ���������� �� ������������
		TStack <char> stack(10);
		int i = 0;
		while (str[i] != '\0'){
			if (str[i] == '(')
				stack.Push('(');
			if (str[i] == ')'){
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
//-----
	void clear() {
		index = -1;
	}
};

