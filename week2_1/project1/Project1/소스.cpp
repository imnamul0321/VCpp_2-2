#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

int main() {

	printf("202207010\n");
	printf("�Ӽ�������\n");
	printf("Application\n");
	printf("\n");
	//char str[17] = "202207010 �Ӽ���";
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
		cout << "p, j, f �Է� : " << endl;
		cin >> pfj;
		if (pfj == "p")
		{
			printf("���� ������ �̳� ���ϴ� �л��̴�.\n");
		}
		else if (pfj == "f") {
			printf("���� ������ �ʹ� ��̴�.\n");
		}
		else if (pfj == "j") {
			printf("������ ���� �� ���ּ���.\n");
		}
		else if (pfj == "j") {
			printf("������ ���� �� ���ּ���.\n");
		}

		else {
			printf("�ٽ��Է��ϼ���.\n");
		}


	}
	return 0;
}
