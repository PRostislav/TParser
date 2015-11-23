#pragma once

template <class T>
class TStack
{
	int MaxSize;					//Максимальный размер стека
	int Index;						//Индекс верхнего элемента
	T *mas;							//Указатель на массив элементов
public:
//-----
	TStack(int len = 25){			//Конструктор
		if (len <= 0) throw len;
		MaxSize = len;
		Index = -1;
		mas = new T[MaxSize];	
	}
//-----
	~TStack() { delete[] mas; }		//Деструктор
	TStack(const TStack& stack){	//Конструктор копирования
		MaxSize = stack.MaxSize;
		Index = stack.Index;
		mas = new T[MaxSize];
		for (int i = 0; i <= Index; i++)
			mas[i] = stack.mas[i];
	}
//-----
	bool IsEmpty(){					//Проверка на пустоту
		return (Index == -1);
	}
//-----
	bool IsFull(){					//Проверка на полноту
		return (Index == MaxSize - 1);
	}
//-----
	T Top(){						//Что лежат вверху стека
		if (Index < 0) throw Index;
		return mas[Index];
	}
//-----
	T Pop(){						//Вытащить элемент из стека
		if (Index < 0) throw Index;
		return mas[Index--];
	}
//-----
	void Push(const T Elem){		//Положить элемент в стек
		if (Index == MaxSize - 1) throw Index;
		mas[++Index] = Elem;
		return;
	}
//-----
	TStack operator=(const TStack& stack){//Оператор =
		MaxSize = stack.MaxSize;
		Index = stack.Index;
		mas = new T[MaxSize];
		for (int i = 0; i <= Index; i++)
			mas[i] = stack.mas[i];
		return *this;
	}
//-----
	int BracketDetector(char *str){		//Закрыты ли все скобки в строке, полученной от пользователя
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

