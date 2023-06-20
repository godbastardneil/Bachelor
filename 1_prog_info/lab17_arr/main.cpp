#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>

using namespace std;

//------------------------------------------------------������� �1
void push (int *arr, int &top, const int &NewInfo)
{
    top++;
    arr[top] = NewInfo;
}
void pushKaKey (int *arr, const int &k, int &top)
{
    int input;
    for (int i=0; i<k; i++) {
        cout << " ������� �������� " << i+1 << ": ";
        cin >> input;
        push(arr, top, input);
    }
}
void pushKaFile (int *arr, const int &k, int &top)
{
    int input;
    ifstream inf;
    inf.open ("input.txt");
    for (int i=0; i<k; i++)
    {
        inf >> input;
        push(arr, top, input);
    }
    inf.close();
}
void pushKaRand (int *arr, const int &k, int &top, const int &minim, const int &maxim)
{
    int input;
    int znam = maxim - minim + 1;
    for (int i=0; i<k; i++)
    {
        input = minim + rand()%(znam);
        push(arr, top, input);
    }
}

void PrintStack (const int *arr, int &top)
{
    if(top != -1) {
        int i = top;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << arr[i] << endl;
        i--;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        while (i != -1) {
            cout << "         "<< arr[i] << endl;
            i--;
        }
    } else { cout << " ���� ����"; }
    cout << endl;
}

int Sumd (const int &db, const int &de, const int *arr1, int &top1)
{
    int c = 0;
    int i = top1;
    while (i != -1) {
        int s = arr1[i];
        if ((s >= db) && (s <= de)) { c++; }
        i--;
    }
    return c;
}
void Copyd (const int &db, const int &de, const int *arr1, int &top1, int *arr2, int &top2)
{
    int i = top1;
    while (i != -1) {
        int s = arr1[i];
        if ((s >= db) && (s <= de)) { push(arr2, top2, s); }
        i--;
    }
}

void Init (int *arr, const int &k, int &top)
{
    int m_init;
    cout << " ��� �� ������ ������ �������� ��������: \n  1. ���� \n  2. ���������� \n  3. �������� " << endl;
    do {
        cin >> m_init;
    } while ((m_init < 1) && (m_init > 3));
    switch (m_init)
    {
    case 1: { // ����
            pushKaFile(arr, k, top);
        break; }
    case 2: { // ����������
            pushKaKey(arr, k, top);
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
            pushKaRand(arr, k, top, minim, maxim);
        }
    }
}
//------------------------------------------------------������� �1
//------------------------------------------------------������� �2
void CreareQueue (int *arr, const int &NewInfo, int &head, int &tail)
{
    tail = 0;
    head = 0;
    arr[tail] = NewInfo;
}

void pushKaKey (int *arr, const int &k, int &head, int &tail)
{
    int input;
    cout << " ������� �������� 1: ";
    cin >> input;
    CreareQueue(arr, input, head, tail);
    for (int i=1; i<k; i++) {
        cout << " ������� �������� " << i+1 << ": ";
        cin >> input;
        push(arr, tail, input);
    }
}
void pushKaFile (int *arr, const int &k, int &head, int &tail)
{
    int input;
    ifstream inf;
    inf.open ("input.txt");
    inf >> input;
    CreareQueue(arr, input, head, tail);
    for (int i=1; i<k; i++)
    {
        inf >> input;
        push(arr, tail, input);
    }
    inf.close();
}
void pushKaRand (int *arr, const int &k, int &head, int &tail, const int &minim, const int &maxim)
{
    int input;
    int znam = maxim - minim + 1;
    input = minim + rand()%(znam);
    CreareQueue(arr, input, head, tail);
    for (int i=1; i<k; i++)
    {
        input = minim + rand()%(znam);
        push(arr, tail, input);
    }
}

void PrintQueue (const int *arr, const int &head, const int &tail)
{
    if(head != tail+1) {
        int i = head;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << arr[i];
        i++;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        while (i != tail+1) {
            if (i == tail) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
            cout << " " << arr[i];
            i++;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    } else { cout << " ���� ����"; }
    cout << endl;
}

void pop (int &head, const int &tail)
{
    if (head != tail+1) { head++; }
}

int kolvot (int *arr, int &head, const int &tail, const int &db, const int &de)
{
    int c = 0;
    int i = head;
    while (i != tail+1) {
        int s = arr[i];
        if ((s < db) && (s > de)) { c++; }
        i++;
    }
    return c;
}
void Takefromt (int *arr, int *tarr, int &tail, int &thead, int &ttail)
{
    while (thead != ttail+1) {
        push(arr, tail, tarr[thead]);
        pop(thead, ttail);
    }
}
void Moved (const int &db, const int &de, const int &k, int *arr, int &head, int &tail)
{
    int n = kolvot(arr, head, tail, db, de);
    int *tarr = new int [n];
    int thead = -1;
    int ttail = -1;
    int i = 0;
    int j = 0;
    while ((head != tail+1) && (i != k)) {
        int s = arr[head];
        if ((s >= db) && (s <= de))
        {
            push(arr, tail, s);
        } else {
            if(j!=0) {
                push(tarr, ttail, s);
            } else { CreareQueue(tarr, s, thead, ttail); }
            j++;
        }
        pop(head, tail);
        i++;
    }
    Takefromt(arr, tarr, tail, thead, ttail);
}

void Init (int *arr, const int &k, int &head, int &tail)
{
    int m_init;
    cout << " ��� �� ������ ������ �������� ��������: \n  1. ���� \n  2. ���������� \n  3. �������� " << endl;
    do {
        cin >> m_init;
    } while ((m_init < 1) && (m_init > 3));
    switch (m_init)
    {
    case 1: { // ����
            pushKaFile(arr, k, head, tail);
        break; }
    case 2: { // ����������
            pushKaKey(arr, k, head, tail);
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
            pushKaRand(arr, k, head, tail, minim, maxim);
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
            int *arr1 = new int [k];
            int top1 = -1;
            Init(arr1, k, top1);
            cout << " ���� 1: ";
            PrintStack(arr1, top1);
            do {
                cout << " ������� �������� ������ ���������: ";
                cin >> db;
                cout << " ������� �������� ����� ���������: ";
                cin >> de;
            } while (db >= de);
            int *arr2 = new int [Sumd(db, de, arr1, top1)];
            int top2 = -1;
            Copyd(db, de, arr1, top1, arr2, top2);
            cout << " ���� 1: ";
            PrintStack(arr1, top1);
            cout << " ���� 2: ";
            PrintStack(arr2, top2);
        break; }
    case 2: {
            int *arr = new int [k];
            int head = -1;
            int tail = -1;
            Init(arr, k, head, tail);
            cout << " ���� 1: ";
            PrintQueue(arr, head, tail);
            do {
                cout << " ������� �������� ������ ���������: ";
                cin >> db;
                cout << " ������� �������� ����� ���������: ";
                cin >> de;
            } while (db >= de);
            Moved(db, de, k, arr, head, tail);
            cout << " �������: ";
            PrintQueue(arr, head, tail);
        }
    }
    return 0;
}
