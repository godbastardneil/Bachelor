#include <iostream>
#include <fstream>

using namespace std;

struct Node
{
    bool male; // 1 - женщина, 0 - мужчина
    int age;
    int education; // 0 - начальное, 1 - среднее, 2 - высшее
    bool answer; // 1 - ДА, 0 - НЕТ
    Node *next;
};
typedef Node *PNode;

void PrintList (PNode &Head)
{
    PNode q = Head;
    cout << " Люди: ";
    int i = 1;
    while (q) {
        cout << i << ". "<< q->male << " " << q->age << " " << q->education << " " << q->answer << endl;
        q = q->next;
        i++;
    }
    cout << i-1 << " людей" << endl;
}

void push (bool &m, int &a, int &e, bool &ans, PNode &Head)
{
    PNode t = new Node;
    t->male = m;
    t->age = a;
    t->education = e;
    t->answer = ans;
    t->next = Head;
    Head = t;
}
void ReadFile (PNode &Head)
{
    bool m;
    int a;
    int e;
    bool ans;
    ifstream inf;
    inf.open ("input.txt");
    while (inf) {
        inf >> m;
        inf >> a;
        inf >> e;
        inf >> ans;
        push(m, a, e, ans, Head);
    }
    inf.close();
}

void MakeGroup (PNode &Head, PNode &AHead, PNode &BHead, PNode &CHead)
{
    PNode q = Head;
    while (q) {
        bool m = q->male;
        int a = q->age;
        int e = q->education;
        bool ans = q->answer;
        if (m) {
            if (a < 30) {
                if (e == 1) {
                    if (!a) { push(m, a, e, ans, BHead); }
                }
            }
        } else {
            if (a > 40) {
                if (e == 2) {
                    if (a) { push(m, a, e, ans, BHead); }
                }
            } else if (a < 25) {
                if (e == 0) {
                    if (a) { push(m, a, e, ans, BHead); }
                }
            }
        }
        q = q->next;
    }
}

int main()
{
    PNode MainHead;
    ReadFile(MainHead);
    PrintList(MainHead);

    PNode AHead;   // мужчины, возраст > 40, высшее образование, ДА
    PNode BHead;  // женщины, возраст < 30, среднее образование, НЕТ
    PNode CHead; // мужчины, возраст < 25, начальное образование, ДА
    MakeGroup(MainHead, AHead, BHead, CHead);

    cout << " Группа А: " << endl;
    PrintList(AHead);

    cout << " Группа B: " << endl;
    PrintList(BHead);

    cout << " Группа C: " << endl;
    PrintList(CHead);

    return 0;
}
