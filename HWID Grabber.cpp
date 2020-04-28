#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <intrin.h>

using namespace std;

int main()
{
    cout << "HWID Information" << endl;
    TCHAR volumeName[MAX_PATH + 1] = { 0 };
    TCHAR fileSystemName[MAX_PATH + 1] = { 0 };
    DWORD serialNumber = 0;
    DWORD maxCompotenLen = 0;
    DWORD fileSystemFlags = 0;
    if (GetVolumeInformation(
        _T("C:\\"),
        volumeName,
        ARRAYSIZE(volumeName),
        &serialNumber,
        &maxCompotenLen,
        &fileSystemFlags,
        fileSystemName,
        ARRAYSIZE(fileSystemName)))
    {
        cout << "Send me this: " << serialNumber << endl;
    }
}
