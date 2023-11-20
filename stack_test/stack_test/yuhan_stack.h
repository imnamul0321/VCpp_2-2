#pragma once
#include <iostream>
using namespace std;

class Stack {
private:
	int stack_size;  // 스택 사이즈
	int stack_count; // 스택에 저장된 데이터의 개수
	int* p_stack;    // 스택으로 사용할 메모리 주소를 가리킬 포인터

public:
	// 메서드 선언
	Stack();
	~Stack();
	void create_stack(int size);
	void push(int value);
	void pop();
	void show_stack();
};

Stack::Stack() // 생성자
{
	// 클래스 변수 초기화
	stack_size = 0;
	stack_count = 0;
	p_stack = NULL;
}

Stack::~Stack() // 소멸자
{
	if (p_stack != NULL) delete[] p_stack; // p_stack이 존재하면 소멸
}

// 스택 생성 -> 스택에 사용할 size를 size 변수로 정의
void Stack::create_stack(int size)
{
	if (p_stack != NULL) delete[] p_stack; // 기존에 사용하던 메모리가 있으면 해당 메모리를 제거한다.
	stack_size = size; // 이 코드를 실행해주는 이유는 class 변수에 값을 넣어주기 위해
	p_stack = new int[stack_size]; // 새로 메모리를 할당한다.
}

// 스택 푸쉬
void Stack::push(int value)
{
	// 스택에 빈 공간이 있을 때 값을 넣는다.
	if (stack_count < stack_size)
	{
		*(p_stack + stack_count) = value; // 스택 메모리 공간에 stack_count index 만큼의 주소값에 값을 넣어 준다.
		stack_count++; // 저장이 되어 스택 count를 증가시킨다.
	}
	else
		cout << "Stack이 가득 찼다" << endl;
}

// pop 구현
void Stack::pop()
{
	if (stack_count == 0) // 저장된 stack이 없으면
	{
		cout << "Stack에 저장된 값들이 없다." << endl;
	}
	else
	{
		cout << "Popped!!" << endl;
		p_stack[stack_count--] = 0; // 마지막 값을 0으로 만들고 stack_count를 감소시킨다.
	}
}


void Stack::show_stack()
{
	if (stack_count == 0) cout << "Stack에 저장된 값들이 없습니다" << endl;

	else
	{
		cout << "Stack에 저장된 값은 아래와 같습니다." << endl;
		for (int i = 0; i < stack_count; i++)
		{
			cout << i << " : " << p_stack[i] << endl;
		}
		cout << "총 " << stack_count << "개의 value가 저장되어 있다." << endl;
	}
}