#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

int main() {


	printf("202207010\n");
	printf("임성진님의\n");
	printf("Application\n");
	printf("\n");
	while (1)
	{	
		
		printf("command>");
		char pfj;
		pfj = _getch();
		if (pfj == 27)
			break;

		if (pfj == 112)
		{
			printf("\n나는 과제를 겁나 잘하는 학생이다.\n");
		}
		else if (pfj == 102) {
			printf("\n나는 과제가 너무 즐겁다.\n");
		}
		else if (pfj == 106) {
			printf("\n교수님 과제 더 내주세요.\n");
		}

		else {
			printf("\n다시입력하세요.\n");
		}

	}

	return 0;

}