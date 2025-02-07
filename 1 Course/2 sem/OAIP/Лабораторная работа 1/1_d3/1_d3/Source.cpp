#include <iostream>
using namespace std;
#define SIZE 6

struct TravelPackages {
    char name[10];
    char location[10];
    char medicalProfile[10];
    int kolich;
};

void Copy(TravelPackages& pest, TravelPackages bust);
void output(const TravelPackages users[]);
void search(const TravelPackages users[]);

int main()
{
    setlocale(LC_CTYPE, "rus");
    TravelPackages sanatorium[SIZE];
    for (int i = 0; i < SIZE; i++) {
        cout << "Санаторий номер " << i + 1 << ":" << endl;
        cout << "Название: ";   cin >> sanatorium[i].name;
        cout << "Расположение: ";   cin >> sanatorium[i].location;
        cout << "Мед профиль: ";   cin >> sanatorium[i].medicalProfile;
        cout << "Количество путёвок: ";   cin >> sanatorium[i].kolich;
        cout << endl;
    }

    TravelPackages buf;
    for (int i = 0; i < SIZE - 1; i++)
        for (int k = 0; k < SIZE - 1; k++)
            if (strcmp(sanatorium[k].medicalProfile, sanatorium[k + 1].medicalProfile) > 0) {
                Copy(buf, sanatorium[k]);
                Copy(sanatorium[k], sanatorium[k + 1]);
                Copy(sanatorium[k + 1], buf);
            }

    for (int i = 0; i < SIZE - 1; i++)
        for (int k = 0; k < SIZE - 1; k++)
            if (strcmp(sanatorium[k].medicalProfile, sanatorium[k + 1].medicalProfile) == 0 && strcmp(sanatorium[k].name, sanatorium[k + 1].name) > 0) {
                Copy(buf, sanatorium[k]);
                Copy(sanatorium[k], sanatorium[k + 1]);
                Copy(sanatorium[k + 1], buf);
            }

    output(sanatorium);
    search(sanatorium);
}

void Copy(TravelPackages& pest, TravelPackages bust) {
    int temp;
    strcpy_s(pest.medicalProfile, bust.medicalProfile);
    strcpy_s(pest.location, bust.location);
    strcpy_s(pest.name, bust.name);
    temp = pest.kolich;
    pest.kolich = bust.kolich;
    bust.kolich = temp;
}

void output(const TravelPackages users[]) {
    cout << "\nНазвание\tРасположение\tМед профиль\tКоличество путёвок";
    for (int i = 0; i < SIZE; i++) {
        cout << "\n------------------------------------------------------------------" << endl;
        cout << users[i].name << "\t\t" << users[i].location << "\t\t" << users[i].medicalProfile << "\t\t" << users[i].kolich;
    }
}

void search(const TravelPackages users[]) {
    int kolich;
    bool f = false;
    cout << "\n\nВведите количество путёвок "; cin >> kolich;
    for (int i = 0; i < SIZE; i++) {
        if (users[i].kolich == kolich) {
            f = true;
            cout << "\n\nНазвание\tРасположение\tМед профиль\tКоличество путёвок";
            cout << "\n------------------------------------------------------------------" << endl;
            cout << users[i].name << "\t\t" << users[i].location << "\t\t" << users[i].medicalProfile << "\t\t" << users[i].kolich;
        }
    }

    if (f == false) {
        cout << "Санатория с указанным вами кол-вом путёвок нет";
    }
}