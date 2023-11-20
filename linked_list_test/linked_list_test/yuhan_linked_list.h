#pragma once
#include <iostream>
using namespace std;

//linked_list
// 
//��� ����ü
struct Node {
	int data;
	struct Node* next;
};
//top �ʱ�ȭ
struct Node* top = NULL;

//push ���
void push(int val) {
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->data = val;
	newnode->next = top;
	top = newnode;
}

//pop���
void pop() {
	if (top == NULL)
		cout << "Stack Underflow" << endl;
	else {
		cout << "The popped element is " << top->data << endl;
		top = top->next;
	}
}

//���
void display() {
	struct Node* ptr;
	if (top == NULL)
		cout << "stack is empty";
	else {
		ptr = top;
		cout << "Stack elements are: ";
		while (ptr != NULL) {
			cout << ptr->data << " ";
			ptr = ptr->next;
		}
	}
	cout << endl;
}