#pragma once
#include <iostream>
using namespace std;


//stack
class Stack {
private:
	int stack_size;  // ���� ������
	int stack_count; // ���ÿ� ����� �������� ����
	int* p_stack;    // �������� ����� �޸� �ּҸ� ����ų ������

public:
	// �޼��� ����
	Stack();
	~Stack();
	void create_stack(int size);
	void push(int value);
	void pop();
	void show_stack();
};

Stack::Stack() // ������
{
	// Ŭ���� ���� �ʱ�ȭ
	stack_size = 0;
	stack_count = 0;
	p_stack = NULL;
}

Stack::~Stack() // �Ҹ���
{
	if (p_stack != NULL) delete[] p_stack; // p_stack�� �����ϸ� �Ҹ�
}

// ���� ���� -> ���ÿ� ����� size�� size ������ ����
void Stack::create_stack(int size)
{
	if (p_stack != NULL) delete[] p_stack; // ������ ����ϴ� �޸𸮰� ������ �ش� �޸𸮸� �����Ѵ�.
	stack_size = size; // �� �ڵ带 �������ִ� ������ class ������ ���� �־��ֱ� ����
	p_stack = new int[stack_size]; // ���� �޸𸮸� �Ҵ��Ѵ�.
}

// ���� Ǫ��
void Stack::push(int value)
{
	// ���ÿ� �� ������ ���� �� ���� �ִ´�.
	if (stack_count < stack_size)
	{
		*(p_stack + stack_count) = value; // ���� �޸� ������ stack_count index ��ŭ�� �ּҰ��� ���� �־� �ش�.
		stack_count++; // ������ �Ǿ� ���� count�� ������Ų��.
	}
	else
		cout << "Stack�� ���� á��" << endl;
}

// pop ����
void Stack::pop()
{
	if (stack_count == 0) // ����� stack�� ������
	{
		cout << "Stack�� ����� ������ ����." << endl;
	}
	else
	{
		cout << "Popped!!" << endl;
		p_stack[stack_count--] = 0; // ������ ���� 0���� ����� stack_count�� ���ҽ�Ų��.
	}
}

//���
void Stack::show_stack()
{
	if (stack_count == 0) cout << "Stack�� ����� ������ �����ϴ�" << endl;

	else
	{
		cout << "Stack�� ����� ���� �Ʒ��� �����ϴ�." << endl;
		for (int i = 0; i < stack_count; i++)
		{
			cout << i << " : " << p_stack[i] << endl;
		}
		cout << "�� " << stack_count << "���� value�� ����Ǿ� �ִ�." << endl;
	}
}

