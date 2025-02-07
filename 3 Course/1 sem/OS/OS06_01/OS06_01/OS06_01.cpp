#include <iostream>
#include <thread>
#include <windows.h>

using namespace std;

volatile DWORD sync_flag = 0; // переменная для синхронизации

void Thread1() {
    cout << "Поток 1: Начало работы...\n";
    Sleep(1000);  

    __asm {
        lock bts sync_flag, 0; Установить бит 0
    }
    __asm {
    WaitLoop1:
        test sync_flag, 1; Проверить бит
            jnz WaitLoop1; Если бит  не установлен
    }
    __asm {
        lock btr sync_flag, 0; Сбросить бит 0
    }

    cout << "Поток 1 завершен.\n";
}

void Thread2() {
    cout << "Поток 2: Начало работы...\n";
    Sleep(1000);  

    __asm {
    WaitLoop2:
        test sync_flag, 1; Проверить бит 
            jz WaitLoop2; Если бит  установлен
    }
    __asm {
        lock bts sync_flag, 0; Установить бит 0
        lock btr sync_flag, 0; Сбросить бит 0
    }

    cout << "Поток 2 завершен.\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    thread t1(Thread1);
    thread t2(Thread2);

    t1.join();
    t2.join();

    return 0;
}
