#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <fileapi.h>
#define FILE_PATH L"D:\\University\\1sem\\ОС\\lab9\\text.txt"
#define READ_BYTES 1000
using namespace std;

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

BOOL insRowFileTxt(LPWSTR fileName, LPWSTR str, DWORD row)
{
    if ((int)row < -1)
    {
        cout << "Номер строки должен быть натуральным числом.\n";
        return false;
    }

    char filepath[20];
    wcstombs(filepath, fileName, 20);
    char stringToInsert[50];
    wcstombs(stringToInsert, str, 50);
    cout << "\n Вставка строки: " << row << "\n\n";

    try
    {
        HANDLE hf = CreateFileW(fileName, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hf == INVALID_HANDLE_VALUE)
        {
            throw "Ошибка при создании или открытии файла";
        }

        DWORD n = 0;
        char buf[1024];
        BOOL success;

        ZeroMemory(buf, sizeof(buf));
        success = ReadFile(hf, buf, sizeof(buf), &n, NULL);
        if (!success)
        {
            CloseHandle(hf);
            throw "Ошибка при чтении файла";
        }

        CloseHandle(hf);

        HANDLE hAppend = CreateFileW(fileName, GENERIC_WRITE, 0, NULL, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hAppend == INVALID_HANDLE_VALUE)
        {
            throw "Ошибка при создании или открытии файла";
        }

        char editedBuf[1024];
        ZeroMemory(editedBuf, sizeof(editedBuf));

        int line = 1;
        int j = 0;

        if (row == 0) 
        {
            for (int k = 0; k < strlen(stringToInsert); k++)
            {
                editedBuf[j++] = stringToInsert[k];
            }
            editedBuf[j++] = '\r';
            editedBuf[j++] = '\n';
        }

        for (int i = 0; i < n; i++)
        {
            if (line == row)
            {
                for (int k = 0; k < strlen(stringToInsert); k++)
                {
                    editedBuf[j++] = stringToInsert[k];
                }
                editedBuf[j++] = '\r';
                editedBuf[j++] = '\n';
                row = 0; 
            }
            editedBuf[j++] = buf[i];
            if (buf[i] == '\n')
                line++;
        }

        if (row == -1) 
        {
            if (j > 0 && editedBuf[j - 1] != '\n')
            {
                editedBuf[j++] = '\r';
                editedBuf[j++] = '\n';
            }
            for (int k = 0; k < strlen(stringToInsert); k++)
            {
                editedBuf[j++] = stringToInsert[k];
            }

            editedBuf[j++] = '\r';
            editedBuf[j++] = '\n';
        }

        DWORD written;
        success = WriteFile(hAppend, editedBuf, j, &written, NULL);
        if (!success)
        {
            CloseHandle(hAppend);
            throw "Ошибка при записи файла";
        }

        cout << editedBuf << endl;
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
    setlocale(0, "ru");
    LPWSTR file = (LPWSTR)FILE_PATH;

    cout << "\nСодержимое файла ДО изменений:\n";
    printFileTxt(file);

    char str[] = "Новая строка";
    wchar_t wStr[50];
    mbstowcs(wStr, str, strlen(str) + 1);
    LPWSTR strToIns = wStr;

    insRowFileTxt(file, strToIns, 0);   
    insRowFileTxt(file, strToIns, -1);  
    insRowFileTxt(file, strToIns, 5);   
    insRowFileTxt(file, strToIns, 7);   

    cout << "\nСодержимое файла ПОСЛЕ изменений:\n";
    printFileTxt(file);
    return 0;
}
