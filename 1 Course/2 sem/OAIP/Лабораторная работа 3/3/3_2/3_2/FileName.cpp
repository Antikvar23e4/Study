#include <iostream>
#define SIZE 5
using namespace std;

FILE* OpenFile(const char* filename, const char* mode = "r")
{
    FILE* file = nullptr;
    if (fopen_s(&file, filename, mode) || file == nullptr)
    {
        perror("Cannot open file!");
        exit(EXIT_FAILURE);
    }
    return file;
}


int* GetElementsFromFile(FILE* file, int& size)
{
    size = 0;
    int* elements = nullptr;

    while (!feof(file))
    {
        int* _elements = new int[++size];
        for (int i = 0; i < size - 1; i++)
            _elements[i] = elements[i];
        fscanf_s(file, "%d", &_elements[size - 1]);
        elements = _elements;
    }
    return elements;
}

void PrintArray(int* array, int n)
{
    for (int i = 0; i < n; i++)
        cout << array[i] << ' ';
}

int main()
{
    setlocale(LC_ALL, "");

    int size = 0;

    FILE* fileA = OpenFile("fileA.txt");
    int* a = GetElementsFromFile(fileA, size);
    cout << "\nInput Array A:" << endl;
    PrintArray(a, size);
    fclose(fileA);

    FILE* fileB = OpenFile("fileB.txt");
    int* b = GetElementsFromFile(fileB, size);
    cout << "\nInput Array B:" << endl;
    PrintArray(b, size);
    fclose(fileB);

    FILE* fileC = OpenFile("fileC.txt");
    int* c = GetElementsFromFile(fileC, size);
    cout << "\n Input Array C:" << endl;
    PrintArray(c, size);
    fclose(fileC);

    FILE* fileD = OpenFile("fileD.txt", "w");
    cout << "\nOutput Array D:" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << a[i] << " " << b[i] << " " << c[i] << " ";
        fprintf_s(fileD, "%d %d %d ", a[i], b[i], c[i]);
    }
    fclose(fileD);


    return 0;
}
