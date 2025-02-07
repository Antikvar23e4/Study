#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define FILE_PATH L"D:\\University\\1sem\\ОС\\lab9\\text.txt"

BOOL printFileTxt(LPWSTR path)
{
    HANDLE file = CreateFileW(
        path,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (file == INVALID_HANDLE_VALUE)
    {
        cerr << "Ошибка при открытии файла" << endl;
        return FALSE;
    }

    char buf[1024];
    DWORD numOfBytes = 0;
    ZeroMemory(buf, sizeof(buf));
    BOOL success = ReadFile(
        file,
        buf,
        sizeof(buf) - 1,
        &numOfBytes,
        NULL);
    if (!success)
    {
        cerr << "Ошибка при чтении файла" << endl;
    }
    else
    {
        buf[numOfBytes] = '\0';
        cout << "\nСодержимое файла (" << numOfBytes << " байт)\n"
            << buf << '\n';
    }

    CloseHandle(file);
    return TRUE;
}

BOOL delRowFileTxt(LPWSTR fileName, DWORD row)
{
    cout << "\n Удаление строки: " << row << "\n\n";

    try
    {
        HANDLE hf = CreateFileW(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hf == INVALID_HANDLE_VALUE)
            throw "Ошибка при создании иои открытии файла";

        DWORD n = 0;
        vector<string> lines;
        char buf[1024];
        BOOL success;

        ZeroMemory(buf, sizeof(buf));
        success = ReadFile(hf, buf, sizeof(buf), &n, NULL);
        if (!success)
        {
            CloseHandle(hf);
            throw "Ошибка при чтении файла";
        }

        string currentLine = "";
        for (int i = 0; i < n; i++)
        {
            if (buf[i] == '\n')
            {
                lines.push_back(currentLine);
                currentLine = "";
            }
            else
            {
                currentLine += buf[i];
            }
        }
        if (!currentLine.empty())
            lines.push_back(currentLine); 

        CloseHandle(hf);

        if (row > lines.size())
        {
            throw "Строка не найдена\n";
        }

        lines.erase(lines.begin() + row - 1);  

        HANDLE hAppend = CreateFileW(fileName, GENERIC_WRITE, 0, NULL, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hAppend == INVALID_HANDLE_VALUE)
        {
            throw "Ошибка при открытии файла для записи";
        }

        DWORD written;
        for (const string& line : lines)
        {
            success = WriteFile(hAppend, line.c_str(), line.length(), &written, NULL);
            if (!success)
            {
                CloseHandle(hAppend);
                throw "Ошибка при записи файла";
            }
            success = WriteFile(hAppend, "\n", 1, &written, NULL); 
            if (!success)
            {
                CloseHandle(hAppend);
                throw "Ошибка при записи файла";
            }
        }

        for (const string& line : lines)
        {
            cout << line << endl;
        }

        CloseHandle(hAppend);
        return true;
    }
    catch (const char* result)
    {
        cout << result << " \n";
        return false;
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    LPWSTR file = (LPWSTR)FILE_PATH;

    cout << "Содержимое файла ДО изменений:\n";
    printFileTxt(file);

    delRowFileTxt(file, 1);
    delRowFileTxt(file, 3);
    delRowFileTxt(file, 8);
    delRowFileTxt(file, 10);

    cout << "\nСодержимое файла ПОСЛЕ изменений:\n";
    printFileTxt(file);

    return 0;
}
