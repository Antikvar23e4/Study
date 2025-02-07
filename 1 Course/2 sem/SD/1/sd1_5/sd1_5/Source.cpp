//�������� ���������, � ������� ����� ����� ������������ ���� ��������� ���� � ������� ��� �� �����.
#include <iostream>
#include <deque>

using namespace std; 

int main()
{
    int sum ;
    std::deque<int> deq;
    for (int count = 1; count < 4; ++count)
    {
        deq.push_back(count); // ��������� ����� � ����� ����
        deq.push_front(10 - count); // ��������� ����� � ������ ����
    }

    for (int index = 0; index < deq.size(); ++index)
        std::cout << deq[index] << ' ';
    
    sum = deq[0];
    for (int index = 1; index < deq.size(); ++index) sum *= deq[index];
    std::cout << '\n' << sum << '\n';
    return 0;
}

