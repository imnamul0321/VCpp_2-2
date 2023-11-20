#include "yuhan_linked_list.h"
#include <iostream>
using namespace std;

int main() {
    int ch, val;
    cout << "1) Push in stack" << endl;
    cout << "2) Pop from stack" << endl;
    cout << "3) Display stack" << endl;
    cout << "4) Exit" << endl;
    do {
        cout << "Enter choice: " << endl;
        cin >> ch;
        switch (ch) {
        case 1: {
            cout << "Enter value to be pushed:" << endl;
            cin >> val;
            push(val);
            break;
        }
        case 2: {
            pop();
            break;
        }
        case 3: {
            display();
            break;
        }
        case 4: {
            cout << "Exit" << endl;
            break;
        }
        default: {
            cout << "Invalid Choice" << endl;
        }
        }
    } while (ch != 4);
    return 0;
}