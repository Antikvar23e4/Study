#include <iostream> 
#include <unordered_map> 
#include <string> 
#include <random> 

using namespace std;

struct Group {
    string man;
};

// ��������� ��������� ����� ��� ������ ���-������� 
default_random_engine generator;
uniform_int_distribution<int> distribution(0, 3);

// ������ ���-������� ���  ����������� 
int p[] = { 73856093, 83492791, 98323467, 123456789 };

int hash_function(int key) {
    int h = 0;
    int index = distribution(generator); // �������� ��������� ���-������� 

    // ��������� ���-�������� 
    h = ((key * p[index]) % 1000000007) % 100;

    return h;
}

int main() {
    setlocale(LC_CTYPE, "russian");
    unordered_map<int, Group> group;

    // ��������� �������� � ���-������� 
    group[1] = { "10" };
    group[2] = { "15" };
    group[3] = { "20" };

    // �������� �������� �������� ���-������� 
    group[2] = { "25" };

    // ����� �������� � ���-������� 
    int group_number;
    cout << "������� ����� ������ ��� ������: ";
    cin >> group_number;

    if (group.find(group_number) != group.end()) {
        cout << "������ " << group_number << " �������� " << group[group_number].man << " ��������� " << endl;
    }
    else {
        cout << "������ " << group_number << " �� �������." << endl;
    }

    // ���������� ������ �������� � ���-������� 
    int new_group_number;
    string new_man;
    cout << "������� ����� ����� ������: ";
    cin >> new_group_number;
    cout << "������� ���-�� ��������� � ������ " << new_group_number << ": ";
    cin >> new_man;
    group[new_group_number] = { new_man };

    // ����� ���� ��������� ���-������� 
    cout << "������� ������: " << endl;
    for (auto it = group.begin(); it != group.end(); ++it) {
        cout << "������ �������� " << it->first << " ������� " << it->second.man << endl;
    }

    return 0;
}