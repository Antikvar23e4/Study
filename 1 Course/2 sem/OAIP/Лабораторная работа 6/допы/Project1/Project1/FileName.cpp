// N человек  располагаютс€  по кругу.  Ќачав отсчет от первого, удал€ют каждого k-го, смыка€ круг после удалени€.
// ќпределить пор€док удалени€ людей из круга. »спользовать линейный список.
#include <iostream>

using namespace std;

struct node
{
    int item;
    node* next;

    node(int x, node* t)
    {
        item = x;
        next = t;
    }
};

typedef node* link;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");
    int i, N, k;
    cout << "¬ведите количество человек ";
    cin >> N;
    cout << "¬ведите каждого какого нужно удал€ть ";
    cin >> k;

    cout << endl;

    link t = new node(1, 0);
    t->next = t;

    link x = t;

    for (i = 2; i <= N; i++)
    {
        x = (x->next = new node(i, t));
    }

    while (x != x->next)
    {
        for (i = 1; i < k; i++)
        {
            x = x->next;
        }
        cout << "¬ыбывает: ";
        cout << x->next->item << '\n';
        x->next = x->next->next;
    }
    cout << "ѕоследний оставшийс€: " << x->item << '\n';
    return 0;
}