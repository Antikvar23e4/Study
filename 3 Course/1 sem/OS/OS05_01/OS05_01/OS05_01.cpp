#include <iostream>
#include <windows.h>
#include <bitset>

using namespace std;

int main() {

    setlocale(LC_ALL, "Russian");

    DWORD processId = GetCurrentProcessId();
    cout << "ID текущего процесса: " << processId << endl;

    DWORD threadId = GetCurrentThreadId();
    cout << "ID текущего (main) потока: " << threadId << endl;

    DWORD processPriorityClass = GetPriorityClass(GetCurrentProcess());
    cout << "Приоритетный класс процесса: " << processPriorityClass << endl;

    int threadPriority = GetThreadPriority(GetCurrentThread());
    cout << "Приоритет текущего потока: " << threadPriority << endl;

    DWORD_PTR processAffinityMask, systemAffinityMask;
    GetProcessAffinityMask(GetCurrentProcess(), &processAffinityMask, &systemAffinityMask);
    cout << "Маска доступных процессоров: " << bitset<64>(processAffinityMask) << endl;

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    cout << "Количество доступных процессоров: " << sysInfo.dwNumberOfProcessors << endl;

    DWORD_PTR currentProcessor = GetCurrentProcessorNumber();
    cout << "Процессор, назначенный текущему потоку: " << currentProcessor << endl;

    return 0;
}
