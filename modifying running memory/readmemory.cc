#include <iostream>
#include <stdio.h>
#include <Windows.h>

using namespace std;

int main() {

    DWORD pid = 18880;
    LONGLONG addr = 0x8000290c0;
    int* buffer = (int*)malloc(4);
    SIZE_T bytesRead = 4;

    HANDLE victimProcess;
    if (!(victimProcess = OpenProcess(PROCESS_VM_READ, false, pid))) {
        cout << "Error opening process" << endl;
        OpenProcess(PROCESS_VM_READ, false, pid);
        cout << GetLastError() << endl;
    } else {

        if (!ReadProcessMemory(victimProcess, (LPCVOID)addr, (LPVOID)buffer, 4, NULL)) {
            cout << "error reading process";
            ReadProcessMemory(victimProcess, (LPCVOID)addr, (LPVOID)buffer, 4, NULL);
            cout << GetLastError() << endl;
        } else {
            while (true) {
                ReadProcessMemory(victimProcess, (LPCVOID)addr, (LPVOID)buffer, 4, NULL);
                cout << *buffer << endl;
            }
            cout << "Reading data from " << 1200 << " at " << "0x8000290c0" << ": " << *buffer << endl;
        }
    }
    int input; 
    cin >> input;
}