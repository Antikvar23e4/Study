#include <Windows.h>
#include <iostream>
DWORD WINAPI threadProc(LPVOID);
int main()
{
	HANDLE hThread;
	DWORD dwThreadId;
	for (int Count = 0; Count < 1000000; Count++)
	{
		hThread = CreateThread(
			NULL, 0, threadProc, NULL, CREATE_SUSPENDED, &dwThreadId);
		if (hThread == INVALID_HANDLE_VALUE || hThread == NULL) {
			printf("CreateThread failed (error %d) after %d threads\n",
				GetLastError(), Count);
			break;
		}
		ResumeThread(hThread);
		CloseHandle(hThread);
		if (Count % 1000 == 0)
			printf("%d\n", Count);
	}
	printf("Thread Main exited\n");
	return 0;
}
DWORD WINAPI threadProc(LPVOID args)
{
	Sleep(600000);
	return 0;
}