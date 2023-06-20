#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>

using namespace std;
//------------------------------------------------------������� �1
struct Stack
{
    int info;
    Stack* next = nullptr;
};
typedef Stack* PStack;

void push (const int &NewInfo, PStack &Head)
{
    PStack t = new Stack;
    t -> info = NewInfo;
    t -> next = Head;
    Head = t;
}
void pushKaKey (const int &k, PStack &Head)
{
    int input;
    for (int i=0; i<k; i++) {
        cout << " ������� �������� " << i+1 << ": ";
        cin >> input;
        push(input, Head);
    }
}
void pushKaFile (const int &k, PStack &Head)
{
    int input;
    ifstream inf;
    inf.open ("input.txt");
    for (int i=0; i<k; i++)
    {
        inf >> input;
        push(input, Head);
    }
    inf.close();
}
void pushKaRand (const int &k, PStack &Head, const int &minim, const int &maxim)
{
    int input;
    int znam = maxim - minim + 1;
    for (int i=0; i<k; i++)
    {
        input = minim + rand()%(znam);
        push(input, Head);
    }
}

void PrintStack (const PStack &Head)
{
    if(Head) {
        PStack t = Head;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << t->info << endl;
        t = t->next;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        while (t) {
            cout << "         "<< t->info << endl;
            t = t->next;
        }
    } else { cout << " ���� ����"; }
    cout << endl;
}

void Copyd (const int &db, const int &de, PStack &Head1, PStack &Head2)
{
    PStack t = Head1;
    while (t) {
        int s = t->info;
        if ((s >= db) && (s <= de)) { push(s, Head2); }
        t = t->next;
    }
}

void Init (const int &k, PStack &Head)
{
    int m_init;
    cout << " ��� �� ������ ������ �������� ��������: \n  1. ���� \n  2. ���������� \n  3. �������� " << endl;
    do {
        cin >> m_init;
    } while ((m_init < 1) && (m_init > 3));
    switch (m_init)
    {
    case 1: { // ����
            pushKaFile(k, Head);
        break; }
    case 2: { // ����������
            pushKaKey(k, Head);
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
            pushKaRand(k, Head, minim, maxim);
        }
    }
}
//------------------------------------------------------������� �1
//------------------------------------------------------������� �2
struct Queue
{
    int info;
    Queue* next = nullptr;
};
typedef Queue* PQueue;

void CreareQueue (const int &NewInfo, PQueue &Head, PQueue &Tail)
{
    PQueue q = new Queue;
    q->info = NewInfo;
    q->next = nullptr;
    Head = q;
    Tail = q;
}
void push (const int &NewInfo, PQueue &Tail)
{
    PQueue q = new Queue;
    q->info = NewInfo;
    q->next = nullptr;
    Tail->next = q;
    Tail = q;
}
void pushKaKey (const int &k, PQueue &Head, PQueue &Tail)
{
    int input;
    cout << " ������� �������� 1: ";
    cin >> input;
    CreareQueue(input, Head, Tail);
    for (int i=1; i<k; i++) {
        cout << " ������� �������� " << i+1 << ": ";
        cin >> input;
        push(input, Tail);
    }
}
void pushKaFile (const int &k, PQueue &Head, PQueue &Tail)
{
    int input;
    ifstream inf;
    inf.open ("input.txt");
    inf >> input;
    CreareQueue(input, Head, Tail);
    for (int i=1; i<k; i++)
    {
        inf >> input;
        push(input, Tail);
    }
    inf.close();
}
void pushKaRand (const int &k, PQueue &Head, PQueue &Tail, const int &minim, const int &maxim)
{
    int input;
    int znam = maxim - minim + 1;
    input = minim + rand()%(znam);
    CreareQueue(input, Head, Tail);
    for (int i=1; i<k; i++)
    {
        input = minim + rand()%(znam);
        push(input, Tail);
    }
}

void pop (PQueue &Head)
{
    if (Head) {
        PQueue q = Head;
        Head =  Head->next;
        delete q;
    }
}

void PrintQueue (const PQueue &Head, const PQueue &Tail)
{
    if(Head) {
        PQueue q = Head;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << q->info ;
        q = q->next;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        while (q) {
            if (q == Tail) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY); }
            cout << " " << q->info;
            q = q->next;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    } else { cout << " ���� ����"; }
    cout << endl;
}
void Takefromt (PQueue &Tail, PQueue &tHead)
{
    while (tHead) {
        push(tHead->info, Tail);
        pop(tHead);
    }
}
void Moved (const int &db, const int &de, const int &k, PQueue &Head, PQueue &Tail)
{
    PQueue tHead = nullptr;
    PQueue tTail = nullptr;
    int i = 0;
    int j = 0;
    while (Head && (i != k)) {
        int s = Head->info;
        if ((s >= db) && (s <= de))
        {
            push(s, Tail);
        } else {
            if(j!=0) {
                push(s, tTail);
            } else { CreareQueue(s, tHead, tTail); }
            j++;
        }
        pop(Head);
        i++;
    }
    Takefromt(Tail, tHead);
}

void Init (const int &k, PQueue &Head, PQueue &Tail)
{
    int m_init;
    cout << " ��� �� ������ ������ �������� ��������: \n  1. ���� \n  2. ���������� \n  3. �������� " << endl;
    do {
        cin >> m_init;
    } while ((m_init < 1) && (m_init > 3));
    switch (m_init)
    {
    case 1: { // ����
            pushKaFile(k, Head, Tail);
        break; }
    case 2: { // ����������
            pushKaKey(k, Head, Tail);
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
            pushKaRand(k, Head, Tail, minim, maxim);
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
            PStack Head1 = nullptr;
            Init(k, Head1);
            cout << " ���� 1: ";
            PrintStack(Head1);
            do {
                cout << " ������� �������� ������ ���������: ";
                cin >> db;
                cout << " ������� �������� ����� ���������: ";
                cin >> de;
            } while (db >= de);
            PStack Head2 = nullptr;
            Copyd(db, de, Head1, Head2);
            cout << " ���� 1: ";
            PrintStack(Head1);
            cout << " ���� 2: ";
            PrintStack(Head2);
        break; }
    case 2: {
            PQueue Head = nullptr;
            PQueue Tail = nullptr;
            Init(k, Head, Tail);
            cout << " �������: ";
            PrintQueue(Head, Tail);
            do {
                cout << " ������� �������� ������ ���������: ";
                cin >> db;
                cout << " ������� �������� ����� ���������: ";
                cin >> de;
            } while (db >= de);
            Moved(db, de, k, Head, Tail);
            cout << " �������: ";
            PrintQueue(Head, Tail);
        }
    }
    return 0;
}

