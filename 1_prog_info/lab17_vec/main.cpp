#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <windows.h>

using namespace std;

//------------------------------------------------------������� �1
void push (vector<int> &vec, int &top, const int &NewInfo)
{
    top++;
    vec.push_back(NewInfo);
}
void pushKaKey (vector<int> &vec, const int &k, int &top)
{
    int input;
    for (int i=0; i<k; i++) {
        cout << " ������� �������� " << i+1 << ": ";
        cin >> input;
        push(vec, top, input);
    }
}
void pushKaFile (vector<int> &vec, const int &k, int &top)
{
    int input;
    ifstream inf;
    inf.open ("input.txt");
    for (int i=0; i<k; i++)
    {
        inf >> input;
        push(vec, top, input);
    }
    inf.close();
}
void pushKaRand (vector<int> &vec, const int &k, int &top, const int &minim, const int &maxim)
{
    int input;
    int znam = maxim - minim + 1;
    for (int i=0; i<k; i++)
    {
        input = minim + rand()%(znam);
        push(vec, top, input);
    }
}

void PrintStack (const vector<int> &vec, int &top)
{
    if(top != -1) {
        int i = top;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << vec[i] << endl;
        i--;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        while (i != -1) {
            cout << "         "<< vec[i] << endl;
            i--;
        }
    } else { cout << " ���� ����"; }
    cout << endl;
}

void Copyd (const int &db, const int &de, vector<int> &vec1, int &top1, vector<int> &vec2, int &top2)
{
    int i = top1;
    while (i != -1) {
        int s = vec1[i];
        if ((s >= db) && (s <= de)) { push(vec2, top2, s); }
        i--;
    }
}

void Init (vector<int> &vec, const int &k, int &top)
{
    int m_init;
    cout << " ��� �� ������ ������ �������� ��������: \n  1. ���� \n  2. ���������� \n  3. �������� " << endl;
    do {
        cin >> m_init;
    } while ((m_init < 1) && (m_init > 3));
    switch (m_init)
    {
    case 1: { // ����
            pushKaFile(vec, k, top);
        break; }
    case 2: { // ����������
            pushKaKey(vec, k, top);
        break; }
    case 3: { // ��������
            int maxim, minim;
            do {
                do {
                    cout << " ������� ����������� �������� [ -32767; 32767]: ";
                    cin >> minim;
                } while ( (minim < -32767) || (minim > 32767) );
                do {
                    cout << " ������� ������������ �������� [ -32767; 32767]: ";
                    cin >> maxim;
                } while ( (maxim < -32767) || (maxim > 32767) );
            } while (minim >= maxim);
            pushKaRand(vec, k, top, minim, maxim);
        }
    }
}
//------------------------------------------------------������� �1
//------------------------------------------------------������� �2
void CreareQueue (vector<int> &vec, const int &NewInfo, int &head, int &tail)
{
    tail = 0;
    head = 0;
    vec.push_back(NewInfo);
}

void pushKaKey (vector<int> &vec, const int &k, int &head, int &tail)
{
    int input;
    cout << " ������� �������� 1: ";
    cin >> input;
    CreareQueue(vec, input, head, tail);
    for (int i=1; i<k; i++) {
        cout << " ������� �������� " << i+1 << ": ";
        cin >> input;
        push(vec, tail, input);
    }
}
void pushKaFile (vector<int> &vec, const int &k, int &head, int &tail)
{
    int input;
    ifstream inf;
    inf.open ("input.txt");
    inf >> input;
    CreareQueue(vec, input, head, tail);
    for (int i=1; i<k; i++)
    {
        inf >> input;
        push(vec, tail, input);
    }
    inf.close();
}
void pushKaRand (vector<int> &vec, const int &k, int &head, int &tail, const int &minim, const int &maxim)
{
    int input;
    int znam = maxim - minim + 1;
    input = minim + rand()%(znam);
    CreareQueue(vec, input, head, tail);
    for (int i=1; i<k; i++)
    {
        input = minim + rand()%(znam);
        push(vec, tail, input);
    }
}

void PrintQueue (const vector<int> &vec, const int &head, const int &tail)
{
    if(head != tail+1) {
        int i = head;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << vec[i];
        i++;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        while (i != tail+1) {
            if (i == tail) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
            cout << " " << vec[i];
            i++;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    } else { cout << " ���� ����"; }
    cout << endl;
}

void pop (vector<int> &vec, int &tail)
{
    if (tail != -1)
    {
        vec.erase(vec.begin());
        tail--;
    }
}

void Takefromt (vector<int> &vec, vector<int> &tvec, int &tail, int &thead, int &ttail)
{
    while (thead != ttail+1) {
        push(vec, tail, tvec[thead]);
        pop(tvec, ttail);
    }
}
void Moved (const int &db, const int &de, const int &k, vector<int> &vec, int &head, int &tail)
{
    vector<int> tvec;
    int thead = -1;
    int ttail = -1;
    int i = 0;
    int j = 0;
    while ((head != tail+1) && (i != k)) {
        int s = vec[head];
        if ((s >= db) && (s <= de))
        {
            push(vec, tail, s);
        } else {
            if(j!=0) {
                push(tvec, ttail, s);
            } else { CreareQueue(tvec, s, thead, ttail); }
            j++;
        }
        pop(vec, tail);
        i++;
    }
    Takefromt(vec, tvec, tail, thead, ttail);
}

void Init (vector<int> &vec, const int &k, int &head, int &tail)
{
    int m_init;
    cout << " ��� �� ������ ������ �������� ��������: \n  1. ���� \n  2. ���������� \n  3. �������� " << endl;
    do {
        cin >> m_init;
    } while ((m_init < 1) && (m_init > 3));
    switch (m_init)
    {
    case 1: { // ����
            pushKaFile(vec, k, head, tail);
        break; }
    case 2: { // ����������
            pushKaKey(vec, k, head, tail);
        break; }
    case 3: { // ��������
            int maxim, minim;
            do {
                do {
                    cout << " ������� ����������� �������� [ -32767; 32767]: ";
                    cin >> minim;
                } while ( (minim < -32767) || (minim > 32767) );
                do {
                    cout << " ������� ������������ �������� [ -32767; 32767]: ";
                    cin >> maxim;
                } while ( (maxim < -32767) || (maxim > 32767) );
            } while (minim >= maxim);
            pushKaRand(vec, k, head, tail, minim, maxim);
        }
    }
}
//------------------------------------------------------������� �2

int main()
{
   	srand((unsigned)time(0));
    system("chcp 1251 > nul");
    int k;
    int ex;
    cout << "�������� �������: \n1. ������� �1 \n ������� ���� �� �����. ��������� � ������ ���� ��� �������� �� ���������, ������������� ���������� ���������. " << endl;
    cout << "2. ������� �2 \n ������� ������� �� �����. ��� ����� �� ���������� ��������� ����������� � ������ �������. " << endl;
    do {
        cout << " ����: ";
        cin >> ex;
    } while ((ex < 1) || (ex > 2));
    do {
        cout << " ������� ���������� ��������� ��� ������������: ";
        cin >> k;
    } while (k <= 0);
    int db; // ������ ���������
    int de; // ����� ���������
    switch (ex)
    {
    case 1: {
            vector <int> vec1;
            int top1 = -1;
            Init(vec1, k, top1);
            cout << " ���� 1: ";
            PrintStack(vec1, top1);
            do {
                cout << " ������� �������� ������ ���������: ";
                cin >> db;
                cout << " ������� �������� ����� ���������: ";
                cin >> de;
            } while (db >= de);
            vector <int> vec2;
            int top2 = -1;
            Copyd(db, de, vec1, top1, vec2, top2);
            cout << " ���� 1: ";
            PrintStack(vec1, top1);
            cout << " ���� 2: ";
            PrintStack(vec2, top2);
        break; }
    case 2: {
            vector <int> vec;
            int head = -1;
            int tail = -1;
            Init(vec, k, head, tail);
            cout << " ���� 1: ";
            PrintQueue(vec, head, tail);
            do {
                cout << " ������� �������� ������ ���������: ";
                cin >> db;
                cout << " ������� �������� ����� ���������: ";
                cin >> de;
            } while (db >= de);
            Moved(db, de, k, vec, head, tail);
            cout << " �������: ";
            PrintQueue(vec, head, tail);
        }
    }
    return 0;
}
