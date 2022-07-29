#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <winreg.h>
#pragma comment(lib, "advapi32.lib")
HKEY Keyto;

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

LSTATUS Keyt = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SYSTEM\\ControlSet001\\Control\\Lsa\\FipsAlgorithmPolicy", 0, KEY_READ, &Keyto);

int main() {
	std::cout << EnableBackupPrivilege() << std::endl;
	std::cout << Keyt << std::endl;
	std::cout << RegSaveKeyExW(Keyto, L"c:\\Temp\\cut", NULL, 1) << std::endl;
	std::cout << RegCloseKey(Keyto);
	return 0;
}
