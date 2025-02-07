//������ ���������� ������� �� �����(��������� ������� ������).������ �� ����� ������ �������� ���������.���� ������ i, j ����� �� ����� ����� �������, �� ������� ������� A[i, j] ����� 1, ����� 0.
//���������� ������� ������ �� ��� ������ ���, ����� ���������� ��� ������� ����� �� ��������������� ����� ���� �����������.
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int poisk(vector<int>& groups, vector<vector<int>>& adjacencyMatrix, int currentIndex, int currentGroup, int groupCount) {
    if (currentIndex == groups.size()) {
        return groupCount;
    }

    int newGroupCount = INT_MAX;
    for (int i = currentGroup; i <= groupCount + 1; i++) {
        groups[currentIndex] = i;

        int groupCountCurrent = 0;
        for (int j = 0; j < groups.size(); j++) {
            if (adjacencyMatrix[currentIndex][j] == 1 && groups[currentIndex] != groups[j]) {
                groupCountCurrent++;
            }
        }

        int smallestGroupCount = poisk(groups, adjacencyMatrix, currentIndex + 1, i, max(groupCount, i));

        if (groupCountCurrent + smallestGroupCount < newGroupCount) {
            newGroupCount = groupCountCurrent + smallestGroupCount;
        }
    }

    return newGroupCount;
}

int main() {
    setlocale(LC_CTYPE, "rus");
    vector<vector<int>> adjacencyMatrix = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };
    int numCountries = adjacencyMatrix.size();
    vector<int> groups(numCountries, 0);
    int smallestGroupCount = poisk(groups, adjacencyMatrix, 0, 1, 1);
    cout << "������ �����:" << endl;
    for (int i = 0; i < numCountries; i++) {
        cout << "������ " << i + 1 << ": ������ " << groups[i] << endl;
    }
    cout << "���������� ��� ������� ����� �� ��������������� �����: " << smallestGroupCount << endl;

    return 0;
}