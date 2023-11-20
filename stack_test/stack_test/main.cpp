#include "yuhan_stack.h"
#include <iostream>
using namespace std;

int main(void)
{
	Stack stack;
	int s_size = 0;
	int tmp = 0;
	int button = -1; // �ƹ� ���ڷ� �ʱ�ȭ
	int value = 0;
	cout << "Stack ����� �Է��ϼ��� : ";

	// �Էµ� stack ����� ������� üũ
	while (s_size <= 0)
	{
		scanf_s("%d", &tmp);
		if (tmp <= 0)
		{
			cout << "stack_size�� ����� �Է��ϼ���, ���� �Էµ� �� ->" << s_size << endl << endl;
			cout << "Stack ����� �Է��ϼ��� : ";
		}
		else s_size = tmp;
	}

	// ���� ����
	stack.create_stack(s_size);


	cout << endl;
	cout << "1. Stack Push" << endl;
	cout << "2. Stack Pop" << endl;
	cout << "3. Stack Print" << endl;
	cout << "0. Exit program" << endl;
	cout << endl << endl;

	while (button != 0)
	{
		cout << "��ư ���� : ";
		scanf_s("%d", &button);
		cout << endl << endl;
		switch (button)
		{
		case 1: // �Է��� �� ����
			cout << "������ ���� ? : ";
			scanf_s("%d", &value);
			stack.push(value);
			break; // break �ʼ� �ȱ׷��� �Ʒ� �׸�鵵 ����

		case 2:
			stack.pop();
			break;

		case 3:
			stack.show_stack();
			break;

		}

	}
	return 0;

}