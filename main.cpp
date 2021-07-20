
#include <iostream>
#include <Windows.h>

#define IOCTL_BUGCHECK CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2100, METHOD_BUFFERED, FILE_ANY_ACCESS)

int main(char argc, char** argv)
{
    DWORD bytesReturned = 0;
    ULONG input = strtoul(argv[1], NULL, 16);

    printf("Transferring: %s\n", argv[1]);
     
    HANDLE device = CreateFileW(L"\\\\.\\BugcheckerSymlink",
        GENERIC_ALL, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, 0);

    if (device == INVALID_HANDLE_VALUE)
    {
        printf("Error opening device handle: 0x%x\n", GetLastError());
        return 0;
    }

    BOOL status = DeviceIoControl(device, IOCTL_BUGCHECK, (LPVOID)&input, sizeof(input), NULL, NULL, &bytesReturned, (LPOVERLAPPED)NULL);
    CloseHandle(device);
}
