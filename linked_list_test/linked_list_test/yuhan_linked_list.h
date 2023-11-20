#pragma once
#include <iostream>
using namespace std;

//linked_list
// 
//노드 구조체
struct Node {
	int data;
	struct Node* next;
};
//top 초기화
struct Node* top = NULL;

//push 기능
void push(int val) {
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->data = val;
	newnode->next = top;
	top = newnode;
}

//pop기능
void pop() {
	if (top == NULL)
		cout << "Stack Underflow" << endl;
	else {
		cout << "The popped element is " << top->data << endl;
		top = top->next;
	}
}

//출력
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