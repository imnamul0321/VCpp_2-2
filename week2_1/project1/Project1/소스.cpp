#include <iostream>
#include <cctype>   // isalpha 알파벳 확인함수
#include <cstdio>   // getchar 아스키 코드로 한 문자 입력받는 함수
using namespace std;

int main() {
	// 스플래쉬 이미지 출력
	cout << " 202207010 " << endl;
	cout << " 임성진" << endl;
	cout << " VC++" << endl;

	while (1) {
		// 커맨드 입력받기
		cout << "command> ";
		char command = getchar(); //getchar 인가 _getch 인가 잘 모르겠다

		// 엔터 키 입력 처리
		if (command == '\n') {
			continue;
		}

		// q, w, e, r 커맨드 처리
		if (command == 'q') {
			cout << "qwer 화이팅" << endl;
		}
		else if (command == 'w') {
			cout << "과제 너무 좋다" << endl;
		}
		else if (command == 'e') {
			cout << "담주부턴 과제량 3배다" << endl;
		}
		else if (command == 'r') {
			cout << "행복합니다." << endl;
		}
		else if (command == 27) {  // 27은 ESC 키의 ASCII 코드
			cout << "프로그램을 종료합니다." << endl;
			break;
		}
		else {
			cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
		}
	}

	return 0;
}