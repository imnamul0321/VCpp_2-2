#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

int main() {


	printf("202207010\n");
	printf("�Ӽ�������\n");
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
			printf("\n���� ������ �̳� ���ϴ� �л��̴�.\n");
		}
		else if (pfj == 102) {
			printf("\n���� ������ �ʹ� ��̴�.\n");
		}
		else if (pfj == 106) {
			printf("\n������ ���� �� ���ּ���.\n");
		}

		else {
			printf("\n�ٽ��Է��ϼ���.\n");
		}

	}

	return 0;

}