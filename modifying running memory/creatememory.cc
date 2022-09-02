#include <iostream>
#include <unistd.h>
#include <windows.h>

using namespace std;

int main() {
    int* newHeapMemory = new int;
    *newHeapMemory = 5;
    cout << "Program PID: " << GetCurrentProcessId() << endl;
    cout << "Integer memory created at: " << newHeapMemory << endl;
    cout << "Printing value of address: " << *newHeapMemory << endl;
    cout << *newHeapMemory << endl;
    int i = *newHeapMemory; 
    while (true) {
        if (*newHeapMemory != i) {
            cout << "Memory value changed" << endl;
            cout << newHeapMemory << ": " << *newHeapMemory << endl;
            i = *newHeapMemory;
        }
    }
    int input;
    cin >> input;
    cout << "Printing value of address: " << *newHeapMemory << endl;
}