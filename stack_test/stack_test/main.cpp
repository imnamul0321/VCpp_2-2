#include "yuhan_stack.h"
#include <iostream>
using namespace std;


int main(void) {

	y_stack y_stack;
	//초기화
	int s_size = 0;
	int tmp = 0;
	int button = -1; //초기화값 상없
	int value = 0;

	cout << "stcak 사이즈 입력 : " << endl;

	while (s_size <= 0)
	{
		scanf_s("%d", &tmp);
		if (tmp <= 0) {

			cout << "stack은 양수로 입력해야 합니다" << endl;
			cout << "현재 입력된 값" << s_size << endl;
			cout << "stcak 사이즈 입력 : " << endl;
		}
		else s_size = tmp;
	}


	//스택생성
	y_stack.create_stack(s_size);

	cout << "1. push" << endl;
	cout << "2. pop" << endl;
	cout << "3. top" << endl;
	cout << "0. exit" << endl;
	cout << endl << endl;

	while (button !=0 )
	{
		cout << "버튼 선택 : ";
		scanf_s("%d", &button);
		cout << endl << endl;

		switch (button)
		{
		case 1: //입력 값 저장
			cout << "저장할 값은? : ";
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

