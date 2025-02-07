//������� ������, ���������� �������. ����� ������, ������ ���������� � ����������, ������� ���� ������ � ����������.

#include <iostream>
#include <fstream>

using namespace std;

struct list
{
	char symbol;
	list* next;
};

void insert(list*& p, char value); //���������� ������� � ������ ������
void printList(list* p);       //����� ������ 
void toFile(list*& p);         //������ � ����
void fromFile(list*& p);       //���������� �� �����
float del(list*& p, float value);
void search(list*& p);
int IsEmpty(list*);
void menu(void); //����� ���� 



int main()
{
	setlocale(LC_CTYPE, "Russian");
	list* first = nullptr;
	int choice; char value; char prev;
	menu();    // ������� ���� 
	cout << " ? ";
	cin >> choice;
	while (choice != 7)
	{
		switch (choice)
		{
		case 1:  	cout << "������� ������ ";
			cin >> value;
			insert(first, value);
			printList(first);
			break;
		case 2: printList(first);
			break;
		case 3: if (!IsEmpty(first)) // ������� ����� �� ������
		{
			cout << "������� ��������� ������ �� ������ ";
			cin >> value;
			if (del(first, value))
			{
				cout << "������ ������ " << value << endl;
				printList(first);
			}
			else
				cout << "������ �� ������" << endl;
		}
			  else
			cout << "������ ����" << endl;
			break;
		case 4:
			search(first);
			break;
		case 5:    toFile(first);
			break;
		case 6:    fromFile(first);
			break;
		default:   cout << "������������ �����" << endl;
			menu(); break;
		}
		cout << "?  ";
		cin >> choice;
	}
	return 0;
}

void insert(list*& p, char value) //���������� ������� � ������ ������
{
	list* newP = new list;
	if (newP != NULL)     //���� �� �����?  
	{
		newP->symbol = value;
		newP->next = p;
		p = newP;
	}
	else
		cout << "�������� ���������� �� ���������" << endl;
}

void printList(list* p)  //����� ������ 
{
	if (p == NULL)
		cout << "������ ����" << endl;
	else
	{
		cout << "������:" << endl;
		while (p != NULL)
		{
			cout << "-->" << p->symbol;
			p = p->next;
		}
		cout << "-->NULL" << endl;
	}
}

void toFile(list*& p)
{
	list* temp = p;
	list buf;
	ofstream frm("text.txt");
	if (frm.fail())
	{
		cout << "\n ������ �������� �����";
		exit(1);
	}
	while (temp)
	{
		buf = *temp;
		frm.write((char*)&buf, sizeof(list));
		temp = temp->next;
	}
	frm.close();
	cout << "������ ������� � ���� text.txt\n";
}

void fromFile(list*& p)          //���������� �� �����
{
	list buf, * first = nullptr;
	ifstream frm("text.txt");
	if (frm.fail())
	{
		cout << "\n ������ �������� �����";
		exit(1);
	}
	frm.read((char*)&buf, sizeof(list));
	while (!frm.eof())
	{
		insert(first, buf.symbol);
		cout << "-->" << buf.symbol;
		frm.read((char*)&buf, sizeof(list));
	}
	cout << "-->NULL" << endl;
	frm.close();
	p = first;
	cout << "\n������ ������ �� ����� text.txt\n";
}

float del(list*& p, float value)  // �������� ����� 
{
	list* previous, * current, * temp;
	if (value == p->symbol)
	{
		temp = p;
		p = p->next;    // ����������� ���� 
		delete temp;      //���������� ������������� ���� 
		return value;
	}
	else
	{
		previous = p;
		current = p->next;
		while (current != NULL && current->symbol != value)
		{
			previous = current;
			current = current->next; // ������� � ���������� 
		}
		if (current != NULL)
		{
			temp = current;
			previous->next = current->next;
			free(temp);
			return value;
		}
	}
	return 0;
}

void search(list*& p)
{
	char s, real, s1, s2;
	cout << "������� ������" << endl;
	cin >> s;
	if (p == NULL) cout << "������ ����" << endl;
	else
	{
		while (p != NULL)
		{
			real = p->symbol;
			p = p->next;
			if (p != NULL) {

				if (p->symbol == s) {
					s1 = s; s2 = real;
				};
			}

		}
		if (s1 == 0) cout << "����� ��������� ���";
		cout << "���������|���������� �������� : " << s1 << "|" << s2 << endl;
	}
}

int IsEmpty(list* p) //������  ������? (1-��, 0-���) 
{
	return p == NULL;
}


void menu(void)     //����� ���� 
{
	cout << "�������� �����:" << endl;
	cout << " 1 - ���� �������" << endl;
	cout << " 2 - ����� ������" << endl;
	cout << " 3 - �������� ������� �� ������" << endl;
	cout << " 4 - ����� �������" << endl;
	cout << " 5 - ������ ������ � ����" << endl;
	cout << " 6 - ������ ������ �� �����" << endl;
	cout << " 7 - �����" << endl;
}

