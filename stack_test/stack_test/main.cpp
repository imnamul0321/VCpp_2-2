#include "yuhan_stack.h"
#include <iostream>
using namespace std;


int main(void) {

	y_stack y_stack;
	//�ʱ�ȭ
	int s_size = 0;
	int tmp = 0;
	int button = -1; //�ʱ�ȭ�� ���
	int value = 0;

	cout << "stcak ������ �Է� : " << endl;

	while (s_size <= 0)
	{
		scanf_s("%d", &tmp);
		if (tmp <= 0) {

			cout << "stack�� ����� �Է��ؾ� �մϴ�" << endl;
			cout << "���� �Էµ� ��" << s_size << endl;
			cout << "stcak ������ �Է� : " << endl;
		}
		else s_size = tmp;
	}


	//���û���
	y_stack.create_stack(s_size);

	cout << "1. push" << endl;
	cout << "2. pop" << endl;
	cout << "3. top" << endl;
	cout << "0. exit" << endl;
	cout << endl << endl;

	while (button !=0 )
	{
		cout << "��ư ���� : ";
		scanf_s("%d", &button);
		cout << endl << endl;

		switch (button)
		{
		case 1: //�Է� �� ����
			cout << "������ ����? : ";
			scanf_s("%d", &value);
			y_stack.push(value);

			break;

		case 2:
			y_stack.pop();
			break;
			
		case 3:
			y_stack.top();
			break;

		}
	}
	return 0;

}

