#include <windows.h>
#include <iostream>
#include <thread>

using namespace std;

int main()
{
    DWORD processId = GetCurrentProcessId();
    DWORD threadId = GetCurrentThreadId();

    cout << "Process ID: " << processId << endl;
    cout << "Thread ID: " << threadId << endl;

    for (int i = 0; i < 1000; ++i)  
    {
        cout << "Iteration: " << i + 1 << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}
