#pragma once
#include <iostream>
using namespace std;
class y_stack {

public:
	y_stack();
	~y_stack();

	void create_stack(int size);
	void push(int vlaue);
	void pop();
	void top();


private:
	int* data; //���ÿ� �޸� ������
	int stack_size; //���� ������
	int stack_count; // ����� ������ ����
};

//������
y_stack::y_stack() {
	//�ʱ�ȭ
	stack_size = 0;
	stack_count = 0;
	data = NULL;
}

//�Ҹ���
y_stack::~y_stack() {
	if (data != NULL) {
		//data ���� ===> ����
		delete[] data;
	}
}

void y_stack::create_stack(int size) {
	if (data != NULL) {
		//data ���� ===> ����
		delete[] data;
		stack_size = size;
		data = new int[stack_size];
	}
}

void y_stack::push(int value) {
	//����� ������
	if (stack_count < stack_size) {
		//���� �ε��� ����ŭ ���ؼ� value�ֱ�
		*(data + stack_count) = value;
		//count 1 ����
		stack_count++;

	}
	else {
		cout << "stack ���� ��" << endl;
	}
}

void y_stack::pop() {
	//����� stack������
	if (stack_count == 0) {
		cout << "stack�� ����� �� ����" << endl;
	}
	else {
		cout << "pop��" << endl;
		//������ �� 0���� ����� stack_count ����
		data[stack_count--] = 0;

	}
}

void y_stack::top() {
	if (stack_count == 0) {
		cout << "stack�� ����� �� ����" << endl;
	}
	else {
		cout << "top�� �� " << endl;
		for (int i = 0; i < stack_count; i++) {
			cout << " = " << data[i - 1] << endl;
		}
	}

}