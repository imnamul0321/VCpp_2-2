#include <iostream>
#include <cctype>   // isalpha ���ĺ� Ȯ���Լ�
#include <cstdio>   // getchar �ƽ�Ű �ڵ�� �� ���� �Է¹޴� �Լ�
using namespace std;

int main() {
	// ���÷��� �̹��� ���
	cout << " 202207010 " << endl;
	cout << " �Ӽ���" << endl;
	cout << " VC++" << endl;

	while (1) {
		// Ŀ�ǵ� �Է¹ޱ�
		cout << "command> ";
		char command = getchar(); //getchar �ΰ� _getch �ΰ� �� �𸣰ڴ�

		// ���� Ű �Է� ó��
		if (command == '\n') {
			continue;
		}

		// q, w, e, r Ŀ�ǵ� ó��
		if (command == 'q') {
			cout << "qwer ȭ����" << endl;
		}
		else if (command == 'w') {
			cout << "���� �ʹ� ����" << endl;
		}
		else if (command == 'e') {
			cout << "���ֺ��� ������ 3���" << endl;
		}
		else if (command == 'r') {
			cout << "�ູ�մϴ�." << endl;
		}
		else if (command == 27) {  // 27�� ESC Ű�� ASCII �ڵ�
			cout << "���α׷��� �����մϴ�." << endl;
			break;
		}
		else {
			cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
		}
	}

	return 0;
}