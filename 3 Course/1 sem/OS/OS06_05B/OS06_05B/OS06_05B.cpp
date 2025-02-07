#include <iostream>
#include <Windows.h>
using namespace std;
int main()
{
	int pid = GetCurrentProcessId();
	HANDLE event = NULL;
	event = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"OS06_06");

	if (event == NULL) {
		cout << "Error opening event.\n";
		return 1;
	}

	WaitForSingleObject(event, INFINITE);
	for (int i = 1; i <= 90; ++i)
	{
		printf("[OS06_06B]\t%d\tPID = %d\n", i, pid);
		Sleep(100);
	}

	if (event) CloseHandle(event);
}
