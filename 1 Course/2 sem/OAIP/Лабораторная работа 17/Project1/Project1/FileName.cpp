#include <iostream> 
#include <unordered_map> 
#include <string> 
#include <random> 

using namespace std;

struct Group {
    string man;
};

// Генератор случайных чисел для выбора хеш-функции 
default_random_engine generator;
uniform_int_distribution<int> distribution(0, 3);

// Массив хеш-функций для  хеширования 
int p[] = { 73856093, 83492791, 98323467, 123456789 };

int hash_function(int key) {
    int h = 0;
    int index = distribution(generator); // выбираем случайную хеш-функцию 

    // Вычисляем хеш-значение 
    h = ((key * p[index]) % 1000000007) % 100;

    return h;
}

int main() {
    setlocale(LC_CTYPE, "russian");
    unordered_map<int, Group> group;

    // Добавляем элементы в хеш-таблицу 
    group[1] = { "10" };
    group[2] = { "15" };
    group[3] = { "20" };

    // Изменяем значение элемента хеш-таблицы 
    group[2] = { "25" };

    // Поиск элемента в хеш-таблице 
    int group_number;
    cout << "Введите номер группы для поиска: ";
    cin >> group_number;

    if (group.find(group_number) != group.end()) {
        cout << "Группа " << group_number << " содержит " << group[group_number].man << " студентов " << endl;
    }
    else {
        cout << "Группа " << group_number << " не найдена." << endl;
    }

    // Добавление нового элемента в хеш-таблицу 
    int new_group_number;
    string new_man;
    cout << "Введите номер новой группы: ";
    cin >> new_group_number;
    cout << "Введите кол-во студентов в группе " << new_group_number << ": ";
    cin >> new_man;
    group[new_group_number] = { new_man };

    // Вывод всех элементов хеш-таблицы 
    cout << "Текущие группы: " << endl;
    for (auto it = group.begin(); it != group.end(); ++it) {
        cout << "Группа содержит " << it->first << " человек " << it->second.man << endl;
    }

    return 0;
}