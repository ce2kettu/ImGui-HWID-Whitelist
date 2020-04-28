#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <intrin.h>

using namespace std;

int main()
{
    //HDD Information
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
        //cout << "Volume Name: " << volumeName << endl;
        cout << "Send me this: " << serialNumber << endl;
        //cout << "File System Type: " << fileSystemName << endl;
        //cout << "Max Component Length: " << maxCompotenLen << endl;
    }
    //Second part gets the computer name
    TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName) / sizeof(computerName[0]);
    if (GetComputerName(
        computerName,
        &size))
    {
        //cout << "Computer Name: " << computerName << endl;
    }
    //Third part gets the CPU Hash
    int cpuinfo[4] = { 0, 0, 0, 0 }; //EAX, EBX, ECX, EDX
    __cpuid(cpuinfo, 0);
    char16_t hash = 0;
    char16_t* ptr = (char16_t*)(&cpuinfo[0]);
    for (char32_t i = 0; i < 8; i++)
        hash += ptr[i];
    cout << "Send me this: " << hash << endl;
    system("pause");
    return(0);
}