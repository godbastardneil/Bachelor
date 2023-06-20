#include <iostream>
#include <ctime>
#include <set>
#include <algorithm>


using namespace std;

typedef set<int, less<int> > set_type;
//--------------------------------������� �1
set_type CWoS (const char &Shop, set_type &ware) // create ware of shop - ����������� ����, ��� ����� � ��������
{
    cout << " ������� " << Shop << endl;
    cout << " ������� 0 - ���� ������ ��� � ��������" << " \n 1 - ���� ����" << endl;
    set_type S;
    int k;
    for (set_type::iterator it = ware.begin(); it != ware.end(); it++)
    {
        do {
            cout << "���� �� � �������� ����� " << *it << "? ";
            cin >> k;
        } while ((k < 0) || (k > 1));
        if (k == 1) { S.insert(*it); }
    }
    return S;
}

void SWoS (const set_type &result) // show ware of shop - ����� ������� ��������
{
    if (result.size() != 0) {
        set_type::iterator it = result.begin();
        cout << *it;
        it++;
        while(it != result.end())
        {
            cout << ", " << *it;
            it++;
        }
    } else { cout << " ����� ������� ���"; }
    cout << endl;
}

set_type EveryShop (set_type &S1, set_type &S2, set_type &S3)
{
    set_type S12;
    set_type result;
    set_intersection(S1.begin(), S1.end(), S2.begin(), S2.end(), inserter(S12, S12.begin()));
    set_intersection(S12.begin(), S12.end(), S3.begin(), S3.end(), inserter(result, result.begin()));
    return result;
}
set_type LeastOne (set_type &S1, set_type &S2, set_type &S3)
{
    set_type result;
    copy(S1.begin(), S1.end(), inserter(result, result.begin()));
    set_difference(S2.begin(), S2.end(), result.begin(), result.end(), inserter(result, result.begin()));
    set_difference(S3.begin(), S3.end(), result.begin(), result.end(), inserter(result, result.begin()));
    return result;
}
set_type OnlyOne (set_type &S1, set_type &S2, set_type &S3)
{
    set_type S12;
    set_type result;
    set_difference(S1.begin(), S1.end(), S2.begin(), S2.end(), inserter(S12, S12.begin()));
    set_difference(S12.begin(), S12.end(), S3.begin(), S3.end(), inserter(result, result.begin()));
    return result;
}
void ex1 ()
{
    set_type ware {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    set_type S1 = CWoS('A', ware);
    set_type S2 = CWoS('B', ware);
    set_type S3 = CWoS('C', ware);

    cout << "������, ������� ��������� � ������ ��������: ";
    SWoS(EveryShop(S1, S2, S3));

    cout << "������, ������� ���� ���� �� � ����� ��������: ";
    SWoS(LeastOne(S1, S2, S3));

    cout << "������, ������� ������� ������ � A: ";
    SWoS(OnlyOne(S1, S2, S3));

    cout << "������, ������� ������� ������ � B: ";
    SWoS(OnlyOne(S2, S1, S3));

    cout << "������, ������� ������� ������ � C: ";
    SWoS(OnlyOne(S3, S1, S2));

    system("pause");
}
//--------------------------------������� �1
//--------------------------------������� �2
void ShowChar (const set<char> &S)
{
    set<char>::iterator it;
    for(it = S.begin(); it != S.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

set<char> CoOW (string &S) // consonants of one word - ��������, ������������� � ����� �����
{
    set<char> result;
    string consonants = "���������������������";
    string::iterator n = S.end();
    int c = 0;
    for (string::iterator i = S.begin(); i != n; i++) {
        char c1 = *i;
        if (consonants.find(c1) != consonants.npos)
        {
            string::iterator j = S.begin();
            while ((*j != ' ') && (j != n)) { j++; }
            while (j != n) {
                char c2 = *j;
                if ((c2 == c1) && (i != j)) { c++; }
                j++;
            }
            if (c == 0) { result.insert(c1); }
        }
        c = 0;
    }
    return result;
}
set<char> VoOW (string &S) // vowel of one word - �������, ������������� � ����� ����� ��� ����
{
    set<char> result;
    string vowel = "���������";
    string::iterator n = S.begin();
    int v = 0;
    string::iterator i = n;
    for (string::iterator i = S.begin(); i != S.end(); i++) {
        char v1 = *i;
        if (vowel.find(v1) != vowel.npos)
        {
            string::iterator j = n;
            while ((*j != ' ') && (j != n)) {
                char v2 = *j;
                if ((v2 == v1) && (i != j)) { v++; }
                j++;
            }
            if (v > 1) { result.insert(v1); }
            n = j++;
        }
        v = 0;
    }
    return result;
}
void string_to_multiset (const string &S, multiset<char> &text)
{
    int n = S.size();
    for (int i=0; i<n; i++) { text.insert(S[i]); }
}
void ex2 ()
{
    string S;
    multiset<char> text;
    cout << "������� ��������� ������� ����� �� ������� �����: ";
    cin.get();
    getline(cin, S);
    string_to_multiset(S, text);
    cout << " ���������� � ���������� ������� ��� ��������� �����, ������� ������ ������ � ���� �����: ";
    ShowChar(CoOW(S));
    cout << " ���������� �������, �������, ������ ���� �� � ���� ����� �� ����� ���� ���: ";
    ShowChar(VoOW(S));
    cout << endl;

}
//--------------------------------������� �2
//--------------------------------������� �3
set_type Set_from_Number(int Number)
{
    set_type S;
    while (Number>0)
    {
        S.insert(Number % 10);
        Number /= 10;
    }
    return S;
}
void ex3 ()
{
    cout << "������ + ����� = ������" << endl;
    set_type M;
    set_type O;
    set_type MO;
    int n = 1;
    for (int i=100000; i<900001; i++) { // ������
        int i1 = i/100000; // ������
        int i2 = (i/10000)%10; // ������/ ������
        int i4 = (i/100)%10; // ������
        int i6 = i%10; // ������
        if ((i6 == 9) && (i2 == i4) && (i1 != 9)) {
            M = Set_from_Number(i);
            if (M.size() == 5) {
                int i3 = (i/1000)%10; // ������
                int i5 = (i/10)%10; // ������
                for (int j=10000; j<100000; j++) { // �����
                    int j2 = (j/1000)%10; // �����
                    if ((i3 == 8) && (i3 == j2)) {
                        int j1 = j/10000; // �����
                        int j3 = (j/100)%10; // �����
                        int j5 = j%10; // �����
                        if ((i6 == j1) && (i6 == j3) && (i6 == j5)) {
                            int j4 = (j/10)%10; // �����
                            O = Set_from_Number(j);
                            MO.clear();
                            set_intersection (M.begin(), M.end(), O.begin(), O.end(), inserter(MO, MO.begin()));
                            if (O.size() == 3 && MO.size() == 2) {
                                int ij = i + j; // ������
                                if ((ij/100000 == i1+1) && (ij%10 == (ij/10)%10) && (j5 != (ij/100)%10) && (j4 != (ij/100)%10) && (i5 != (ij/100)%10) && (j5 != (ij/1000)%10) && (j4 != (ij/1000)%10) && (i5 != (ij/1000)%10)) {
                                    MO = Set_from_Number(ij);
                                    int ij1 = ij/100000;
                                    if ((MO.size() == 5) && (ij1 == i1+1) && (ij1 != i5) && (ij1 != j4)) {
                                        cout << n << ". " << i << " + " << j <<  " = " << ij << endl;
                                        n++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
//--------------------------------������� �3

void Menu ()
{
    cout << "������� �1. � ���� ��������� ������� ��������� ������ �� ���������� ������. ����������, ����� ������ ��������� � ������ ��������, ����� ������ ���� ������ � ����� ��������, � ����� ������ ���� ���� �� � ����� ��������." << endl;
    cout << "������� �2. ��� ����� �� ������� �����. ���������� � ���������� ������� ��� ��������� �����, ������� ������ ������ � ���� �����, � ��� �������, �������, ������ ���� �� � ���� ����� �� ����� ���� ���." << endl;
    cout << "������� �3. ���������� �����:  ������ + ����� = ������ (12 �������)." << endl;
    cout << "0. �����." << endl;
}
int main()
{
    srand(time(0));
    system("chcp 1251 > nul");
    cout << " ������������ ������ �13, �����-11, ������� �8, �������� �����" << endl;
    int m = 4;
    while (m != 0)
    {
        Menu();
        do {
            cout << "����: ";
            cin >> m;
        } while ((m < 0) || (m > 3));
        if (m != 0)
        {
            switch (m)
            {
            case 1:
                ex1();
                break;
            case 2:
                ex2();
                break;
            case 3: { ex3(); }
            }
        }
    }
    return 0;
}
