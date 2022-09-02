#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

using namespace std; 

int main() {
    cout << "getting the pid of create.exe" << endl;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(snapshot, &entry)) {
        cout << "worked" << endl;
        while (Process32Next(snapshot, &entry)) {
            cout << entry.szExeFile << " : " << entry.th32ProcessID << endl;
        }

    } else {
        cout << "didn't work" << endl;
    }

}