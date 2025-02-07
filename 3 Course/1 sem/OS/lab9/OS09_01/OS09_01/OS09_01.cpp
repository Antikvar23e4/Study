#include <windows.h>
#include <iostream>
using namespace std;

#define FILE_PATH L"D:\\University\\1sem\\ОС\\lab9\\text.txt"

string getFileName(wchar_t* filePath)
{
    wstring ws(filePath);
    string filename(ws.begin(), ws.end());
    const size_t last_slash_idx = filename.find_last_of("\\/");
    if (string::npos != last_slash_idx)
        filename.erase(0, last_slash_idx + 1);
    return filename;
}

LPCWSTR getFileType(HANDLE file)
{
    switch (GetFileType(file))
    {
    case FILE_TYPE_UNKNOWN:
        return L"FILE_TYPE_UNKNOWN";
    case FILE_TYPE_DISK:
        return L"FILE_TYPE_DISK";
    case FILE_TYPE_CHAR:
        return L"FILE_TYPE_CHAR";
    case FILE_TYPE_PIPE:
        return L"FILE_TYPE_PIPE";
    case FILE_TYPE_REMOTE:
        return L"FILE_TYPE_REMOTE";
    default:
        return L"[ERROR]:Не удалось определить тип файла";
    }
}

void processFileInfo(HANDLE file, LPWSTR path)
{
    SYSTEMTIME currentTime;
    BY_HANDLE_FILE_INFORMATION fileInfo;
    BOOL fResult = GetFileInformationByHandle(file, &fileInfo);
    if (fResult)
    {
        cout << "Название файла:\t" << getFileName(path) <<endl;
        wcout << L"Тип файла:\t" << getFileType(file);
        cout << "\nРазмер файла:\t" << fileInfo.nFileSizeLow << " bytes";
        FileTimeToSystemTime(&fileInfo.ftCreationTime, &currentTime);
        cout << "\nПоследнее изменение:\t" << currentTime.wDay << '.' << currentTime.wMonth << '.' << currentTime.wYear << " "
            << currentTime.wHour << ':' << currentTime.wMinute << ':' << currentTime.wSecond;
        FileTimeToSystemTime(&fileInfo.ftLastWriteTime, &currentTime);
        cout << "\nСоздан:\t" << currentTime.wDay << '.' << currentTime.wMonth << '.' << currentTime.wYear << " "
            << currentTime.wHour << ':' << currentTime.wMinute << ':' << currentTime.wSecond;
    }
    else
    {
        cerr << "Ошибка получения информации о файле" << endl;
    }
}

BOOL printFileInfo(LPWSTR path)
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

    processFileInfo(file, path);
    CloseHandle(file);
    return TRUE;
}

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
    BOOL succes = ReadFile(
        file,
        buf,
        sizeof(buf) - 1,
        &numOfBytes,
        NULL);
    if (!succes)
    {
        cerr << "Ошибка при чтении файла" << endl;
    }
    else
    {
        buf[numOfBytes] = '\0';
        cout << "\n\n\tСодержимое файла (" << numOfBytes << " байт)\n"
            << buf << '\n';
    }

    CloseHandle(file);
    return TRUE;
}

int main()
{
    setlocale(LC_ALL, "ru");
    LPWSTR path = (LPWSTR)FILE_PATH;
    cout << "";

    printFileInfo(path);
    cout << "";

    printFileTxt(path);
    cout << "";
    system("pause");
    return 0;
}
