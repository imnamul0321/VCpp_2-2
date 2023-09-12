#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

int main() {

	printf("202207010\n");
	printf("임성진님의\n");
	printf("Application\n");
	printf("\n");
	//char str[17] = "202207010 임성진";
	//cout << str;
	//printf("%s", str);
	char esc;
	while (1)
	{
		esc = _getch();
		{
			if (int(esc) == 27)
				break;
		}
		string pfj;
		cout << "p, j, f 입력 : " << endl;
		cin >> pfj;
		if (pfj == "p")
		{
			printf("나는 과제를 겁나 잘하는 학생이다.\n");
		}
		else if (pfj == "f") {
			printf("나는 과제가 너무 즐겁다.\n");
		}
		else if (pfj == "j") {
			printf("교수님 과제 더 내주세요.\n");
		}
		else if (pfj == "j") {
			printf("교수님 과제 더 내주세요.\n");
		}

		else {
			printf("다시입력하세요.\n");
		}


	}
	return 0;
}
