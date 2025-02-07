#include "pch.h"
#include <iostream>
#define EXPORT __declspec(dllexport) 

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C" {
    EXPORT void HelloWorld() {
        std::cout << "Hello from Library1!" << std::endl;
    }

    EXPORT int Add(int a, int b) {
        return a + b;
    }
}