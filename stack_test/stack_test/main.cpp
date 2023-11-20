#include "yuhan_stack.h"
#include <iostream>
using namespace std;

int main(void)
{
	Stack stack;
	int s_size = 0;
	int tmp = 0;
	int button = -1; // 아무 숫자로 초기화
	int value = 0;
	cout << "Stack 사이즈를 입력하세요 : ";

	// 입력된 stack 사이즈가 양수인지 체크
	while (s_size <= 0)
	{
		scanf_s("%d", &tmp);
		if (tmp <= 0)
		{
			cout << "stack_size를 양수로 입력하세요, 현재 입력된 값 ->" << s_size << endl << endl;
			cout << "Stack 사이즈를 입력하세요 : ";
		}
		else s_size = tmp;
	}

	// 스택 생성
	stack.create_stack(s_size);


	cout << endl;
	cout << "1. Stack Push" << endl;
	cout << "2. Stack Pop" << endl;
	cout << "3. Stack Print" << endl;
	cout << "0. Exit program" << endl;
	cout << endl << endl;

	while (button != 0)
	{
		cout << "버튼 선택 : ";
		scanf_s("%d", &button);
		cout << endl << endl;
		switch (button)
		{
		case 1: // 입력한 값 저장
			cout << "저장할 값은 ? : ";
			scanf_s("%d", &value);
			stack.push(value);
			break; // break 필수 안그러면 아래 항목들도 실행

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