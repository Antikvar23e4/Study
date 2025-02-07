#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <fileapi.h>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>

#define FILE_PATH L"D:\\University\\1sem\\ОС\\lab9\\text.txt"

using namespace std;

BOOL printWatchRowFileTxt(LPWSTR FileName, DWORD mlsec, DWORD duration)
{
    HANDLE hDir = CreateFileW(
        L"D:\\University\\1sem\\ОС\\lab9",
        FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        NULL);

    if (hDir == INVALID_HANDLE_VALUE)
    {
        cerr << "Ошибка при открытии директории" << endl;
        return FALSE;
    }

    char buffer[1024];
    DWORD bytesReturned;
    FILE_NOTIFY_INFORMATION* fni = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(buffer);
    DWORD prevLineCount = 0;

    ifstream file("D:\\University\\1sem\\ОС\\lab9\\text.txt");
    string line;
    size_t currentLineCount = 0;

    while (getline(file, line))
    {
        currentLineCount++;
    }
    file.close();

    prevLineCount = currentLineCount;
    cout << "Начальное количество строк: " << currentLineCount << endl;

    auto startTime = chrono::steady_clock::now();

    while (true)
    {
        auto currentTime = chrono::steady_clock::now();
        auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - startTime).count();
        if (elapsedTime >= duration)
        {
            cout << "Время наблюдения истекло." << endl;
            break;
        }

        if (ReadDirectoryChangesW(hDir, buffer, sizeof(buffer), TRUE, 
            FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_LAST_WRITE, &bytesReturned, NULL, NULL))
        {
            ifstream file("D:\\University\\1sem\\ОС\\lab9\\text.txt");
            currentLineCount = 0;

            while (getline(file, line))
            {
                currentLineCount++;
            }
            file.close();

            if (currentLineCount != prevLineCount)
            {
                cout << "Количество строк было изменено. Текущее количество: " << currentLineCount << endl;
                prevLineCount = currentLineCount;
            }
        }
        else
        {
            cerr << "Ошибка при чтении изменений директории." << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(mlsec));
    }

    CloseHandle(hDir);
    return TRUE;
}

int main()
{
    setlocale(LC_ALL, "ru");
    LPWSTR fileName = (LPWSTR)FILE_PATH;

    DWORD duration = 2000; 
    if (printWatchRowFileTxt(fileName, 2000, duration))
    {
        cout << "Наблюдение завершено успешно.\n";
    }
    else
    {
        cout << "Произошла ошибка во время наблюдения.\n";
    }
    return 0;
}
