#include <iostream>
#include <thread>
#include <chrono>   //ũ�γ� �����ð�
#include <windows.h> 
using namespace std;

/*
Ű���带 �Է��� �������� 0.3�ʸ���(300ms) ���� �Է��� ���� �Ŀ�
���a ������ �Է��� �ƴٸ�
"�Ƶ���! =o" �̶�� ����Ѵ�.
�� 3���� ����� �����ÿ�.
("asdf���a" ó�� �̻��� �ܾ ���������� �νĽ�ų��")
	�ƹ����� esc�� ������ �����ϵ��� �Ұ�.
	+ ũ�γ� ���(������)
*/


int main() {
    string inputBuffer;
    bool exit = false;

    cout << "Ű���� �Է��� ����͸��մϴ�. \n�����Ϸ��� 'esc' Ű�� ��������." << endl;

    while (!exit) {
        inputBuffer.clear();

        // 0.3�� ���� �Է�
        for (int i = 0; i < 30; ++i) {
            this_thread::sleep_for(chrono::milliseconds(300));  // ��� 300ms 0.3��

            for (int key = 8; key <= 255; ++key) {
                if (GetAsyncKeyState(key) & 0x8000) {
                    if (key == VK_ESCAPE) { //API ESC key = VK_ESCAPE
                        exit = true;
                        break;
                    }
                    inputBuffer += static_cast<char>(key);
                }
            }
            //Ż�� ���α׷� ����
            if (exit)
                break;
        }

        // �Է� ���۸� ���ڿ��� ��ȯ�Ͽ� �˻�
        if (inputBuffer.find("a") != string::npos) {
            cout << "�Ƶ���! =o" <<endl;
        }
    }

    return 0;
}