#include <iostream>
#include <thread>
#include <chrono>   //크로노 지연시간
#include <windows.h> 
using namespace std;

/*
키보드를 입력한 순간부터 0.3초마다(300ms) 동안 입력을 쌓은 후에
↓→a 순으로 입력이 됐다면
"아도겐! =o" 이라고 출력한다.
총 3개의 기술을 만들어보시오.
("asdf↓→a" 처럼 이상한 단어가 섞여있으면 인식시킬것")
	아무때나 esc를 누르면 종료하도록 할것.
	+ 크로노 사용(딜레이)
*/


int main() {
    string inputBuffer;
    bool exit = false;

    cout << "키보드 입력을 모니터링합니다. \n종료하려면 'esc' 키를 누르세요." << endl;

    while (!exit) {
        inputBuffer.clear();

        // 0.3초 동안 입력
        for (int i = 0; i < 30; ++i) {
            this_thread::sleep_for(chrono::milliseconds(300));  // 대기 300ms 0.3초

            for (int key = 8; key <= 255; ++key) {
                if (GetAsyncKeyState(key) & 0x8000) {
                    if (key == VK_ESCAPE) { //API ESC key = VK_ESCAPE
                        exit = true;
                        break;
                    }
                    inputBuffer += static_cast<char>(key);
                }
            }
            //탈출 프로그램 종료
            if (exit)
                break;
        }

        // 입력 버퍼를 문자열로 변환하여 검사
        if (inputBuffer.find("a") != string::npos) {
            cout << "아도겐! =o" <<endl;
        }
    }

    return 0;
}