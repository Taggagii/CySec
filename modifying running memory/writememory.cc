#include <iostream>
#include <stdio.h>
#include <Windows.h>

using namespace std;

int main() {

    DWORD pid = 2800;
    LONGLONG addr = 0x800029130;
    int Writebuffer = 69696;
    SIZE_T bytesRead = 4;


    HANDLE victimProcess;
    if (!(victimProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION, false, pid))) {
        cout << GetLastError() << endl;
        cout << "Error opening process" << endl;
    } else {
        bool worked = WriteProcessMemory(victimProcess, (LPVOID)addr, (LPVOID)&Writebuffer, 4, nullptr);   
        if (!worked) {
            cout << GetLastError() << endl;
            cout << "writing failed" << endl;
        } else {
            cout << "writing succeeded, wrote: " << Writebuffer << endl;
        }
    }
    int input;
    cin >> input;
}