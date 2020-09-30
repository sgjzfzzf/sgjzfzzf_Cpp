/*
作者:sgjzfzzf
时间:2020.09.30
*/
#include<iostream>
using namespace std;

template <class elemType>
class SeqStack {
private:
	elemType* data;
	int maxSize;
	int currentSize;
	void expandSize(int);
public:
	SeqStack();
	~SeqStack();
	void push(elemType);
	elemType pop();
	elemType top() const;
	bool isEmpty();
	bool isFull();
};

template <class elemType>
SeqStack<elemType>::SeqStack() {
	maxSize = 10;
	currentSize = 0;
	data = new elemType[maxSize];
}

template <class elemType>
SeqStack<elemType>::~SeqStack() {
	delete[] data;
}

template <class elemType>
void SeqStack<elemType>::expandSize(int newSize) {
	elemType* tmpdata = data;
	data = new elemType[newSize];
	maxSize = newSize;
	for (int i = 0; i < currentSize; ++i) {
		data[i] = tmpdata[i];
	}
	delete[] tmpdata;
}

template <class elemType>
void SeqStack<elemType>::push(elemType item) {
	if (isFull()) {
		maxSize *= 2;
		expandSize(maxSize);
	}
	data[currentSize] = item;
	++currentSize;
}

template <class elemType>
elemType SeqStack<elemType>::pop() {
	--currentSize;
	return data[currentSize];
}

template <class elemType>
elemType SeqStack<elemType>::top() const {
	return data[currentSize - 1];
}

template <class elemType>
bool SeqStack<elemType>::isEmpty() {
	return currentSize == 0;
}

template <class elemType>
bool SeqStack<elemType>::isFull() {
	return currentSize == maxSize;
}

class Calculator {
private:
	SeqStack<int> numStack;
	SeqStack<char> signStack;
	int cal(int, int, char);
public:
	int calculate(string);
};

int Calculator::cal(int x, int y, char sign) {
	switch (sign) {
	case '+':
		return x + y;
	case '-':
		return x - y;
	case '*':
		return x * y;
	case '/':
		return x / y;
	}
}

int Calculator::calculate(string q) {
	for (int k = 0; k < q.length(); ++k) {
		if (q[k] >= '0' && q[k] <= '9') {
			numStack.push(q[k] - '0');
		}
		else if (q[k] == '(') {
			signStack.push(q[k]);
		}
		else if (q[k] == ')') {
			while (signStack.top() != '(') {
				int right = numStack.pop();
				int left = numStack.pop();
				char sign = signStack.pop();
				numStack.push(cal(left, right, sign));
			}
			signStack.pop();
		}
		else if (q[k] == '*' || q[k] == '/') {
			while (signStack.top() != '(' && signStack.top() != '+' && signStack.top() != '-' && !signStack.isEmpty()) {
				int right = numStack.pop();
				int left = numStack.pop();
				char sign = signStack.pop();
				numStack.push(cal(left, right, sign));
			}
			signStack.push(q[k]);
		}
		else if (q[k] == '+' || q[k] == '-') {
			while (signStack.top() != '(' && !signStack.isEmpty()) {
				int right = numStack.pop();
				int left = numStack.pop();
				char sign = signStack.pop();
				numStack.push(cal(left, right, sign));
			}
			signStack.push(q[k]);
		}
	}
	while (!signStack.isEmpty()) {
		int right = numStack.pop();
		int left = numStack.pop();
		char sign = signStack.pop();
		numStack.push(cal(left, right, sign));
	}
	return numStack.top();
}

int main() {
	Calculator calculator;
	cout << "result is " << calculator.calculate("(1+7)*3+6") << endl;
	return 0;
}
