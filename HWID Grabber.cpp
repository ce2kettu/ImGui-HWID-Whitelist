#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <intrin.h>

using namespace std;

int main()
{
    cout << "HWID Information" << endl;
    DWORD serialNumber = 0;
    if (GetVolumeInformation(
        _T("C:\\"),
        NULL,
        0,
        &serialNumber,
        NULL,
        0,
        NULL,
        0))
    {
        cout << "Send me this: " << serialNumber << endl;
    }
}
