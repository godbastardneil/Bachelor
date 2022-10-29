#include <iostream>
#include <vector>
#include <windows.h>
#include <iomanip>

#include "print.h"
#include "struct.h"

using namespace std;

PNode Head, Tail;

void PrintList (PNode p)
{
    gotoXY(0, 0);
    PNode q = Head;
    cout << " Список: ";
    if(q) {
        set_col(LightBlue, Black);
        cout << q->el << " ";
        q = q->next;
        set_col(White, Black);
        while (q)
        {
            if (q == Tail) { set_col(LightRed, Black); }
            else if (q == p) { set_col(LightGreen, Black); }
            cout << q->el << " ";
            q = q->next;
            set_col(White, Black);
        }
    }
}

PNode CreateNode (short int NewEl)
{
    PNode NewNode = new Node;
    NewNode -> el = NewEl;
    NewNode -> next = NULL;
    NewNode -> prev = NULL;
    return NewNode;
}

void AddFirst (PNode NewNode)
{
    gotoXY(0, 4);
    if (Head) {
        cout << "        /-------\\              /-------\\" << endl;
        cout << "        |NewHead|              |OldHead|" << endl;
        cout << "        \\-------/              \\-------/" << endl;
        cout << "            |                      |" << endl;
        cout << "            \\/                     \\/" << endl;
        cout << "       /------------\\        /------------\\" << endl;
        cout << "       | |        | |        | |" << setw(8) << Head->el << "| |->NULL" << endl;
        cout << "       | |" << setw(8) << NewNode << "| |  NULL<-| |" << setw(8) << Head << "| |" << endl;
        cout << "       \\------------/        \\------------/" << endl;
        if (Head->next){
            gotoXY(43, 10);
            cout << "->... ";
            gotoXY(43, 11);
            cout << "<-...";
        }
        gotoXY(0, 19);
        system("pause");

        gotoXY(10, 10);
        cout << setw(8) << NewNode->el;
        gotoXY(0, 19);
        system("pause");

        gotoXY(21, 10);
        cout << "------->";
        gotoXY(0, 19);
        system("pause");

        gotoXY(1, 11);
        cout << "NULL<-";
        gotoXY(0, 19);
        system("pause");

        gotoXY(21, 11);
        cout << "<-------";
    } else {
        cout << "        /-------\\" << endl;
        cout << "        |NewHead|" << endl;
        cout << "        \\-------/" << endl;
        cout << "            |" << endl;
        cout << "            \\/" << endl;
        cout << "       /------------\\" << endl;
        cout << "       | |        | |" << endl;
        cout << "       | |" << setw(8) << NewNode << "| |" << endl;
        cout << "       \\------------/" << endl;
        gotoXY(0, 19);
        system("pause");

        gotoXY(10, 10);
        cout << setw(8) << NewNode->el;
        gotoXY(0, 19);
        system("pause");

        gotoXY(21, 10);
        cout << "->NULL";
        gotoXY(0, 19);
        system("pause");

        gotoXY(1, 11);
        cout << "NULL<-";
    }
    NewNode -> next = Head;
    NewNode -> prev = NULL;
    if ( Head ) { Head -> prev = NewNode; }
    Head = NewNode;
    if ( !Tail ) { Tail = Head; }
}
void AddLast (PNode NewNode)
{
    gotoXY(0, 4);
    if (Tail) {
        cout << "         /-------\\            /-------\\" << endl;
        cout << "         |OldTail|            |NewTail|" << endl;
        cout << "         \\-------/            \\-------/" << endl;
        cout << "             |                    |" << endl;
        cout << "             \\/                   \\/" << endl;
        cout << "       /------------\\        /------------\\" << endl;
        cout << "       | |" << setw(8) << Tail->el  << "| |->NULL  | |        | |" << endl;
        cout << " NULL<-| |" << setw(8) << Tail << "| |        | |"  << setw(8) << NewNode << "| |" << endl;
        cout << "       \\------------/        \\------------/" << endl;
        if (Tail->prev) {
            gotoXY(0, 10);
            cout << "  ...->";
            gotoXY(0, 11);
            cout << "  ...<-";
        }
        gotoXY(0, 19);
        system("pause");

        gotoXY(32, 10);
        cout <<  setw(8) << NewNode->el;
        gotoXY(0, 19);
        system("pause");

        gotoXY(21, 11);
        cout <<  "<-------";
        gotoXY(0, 19);
        system("pause");

        gotoXY(43, 10);
        cout <<  "->NULL ";
        gotoXY(0, 19);
        system("pause");

        gotoXY(21, 10);
        cout <<  "------->";
    } else {
        cout << "         /-------\\" << endl;
        cout << "         |NewTail|" << endl;
        cout << "         \\-------/" << endl;
        cout << "             |" << endl;
        cout << "             \\/" << endl;
        cout << "       /------------\\" << endl;
        cout << "       | |        | |" << endl;
        cout << "       | |" << setw(8) << NewNode << "| |" << endl;
        cout << "       \\------------/" << endl;
        gotoXY(0, 19);
        system("pause");

        gotoXY(9, 10);
        cout << setw(8) << NewNode->el;
        gotoXY(0, 19);
        system("pause");

        gotoXY(21, 10);
        cout << "->NULL";
        gotoXY(0, 19);
        system("pause");

        gotoXY(1, 11);
        cout << "NULL<-";
    }
    NewNode -> prev = Tail;
    NewNode -> next = NULL;
    if ( Tail ) { Tail -> next = NewNode; }
    Tail = NewNode;
    if ( !Head ) { Head = Tail; }
}
void AddAfter (PNode p, PNode NewNode)
{
    if (!p->next) { AddLast(NewNode); }
    else
    {
        gotoXY(0, 4);
        cout << "                 /-------\\" << endl;
        cout << "                 |NewNode|" << endl;
        cout << "                 \\-------/" << endl;
        cout << "                     |" << endl;
        cout << "                     \\/" << endl;
        cout << "               /------------\\" << endl;
        cout << "          /-\\  | |        | |" << endl;
        cout << "          |p|  | |" << setw(8) << NewNode << "| |" << endl;
        cout << "          \\-/  \\------------/" << endl;
        cout << "           |" << endl;
        cout << "           \\/" << endl;
        cout << "       /------------\\   /------------\\" << endl;
        cout << "       | |" << setw(8) << p->el << "| |-->| |" << setw(8) << p->next->el << "| |->..." << endl;
        cout << " NULL<-| |" << setw(8) << p << "| |<--| |" << setw(8) << p->next << "| |<-..." << endl;
        cout << "       \\------------/   \\------------/" << endl;
        if (p->prev) {
            gotoXY(0, 16);
            cout << "  ...->";
            gotoXY(0, 17);
            cout << "  ...<-";
        }
        gotoXY(0, 19);
        system("pause");

        gotoXY(18, 10);
        cout << setw(8) << NewNode->el;
        gotoXY(0, 19);
        system("pause");

        gotoXY(27, 13);
        cout << "|";
        gotoXY(27, 14);
        cout << "\\/";
        gotoXY(0, 19);
        system("pause");

        gotoXY(16, 13);
        cout << "|";
        gotoXY(16, 14);
        cout << "\\/";
        gotoXY(0, 19);
        system("pause");

        gotoXY(21, 17);
        cout << "   ";
        gotoXY(25, 13);
        cout << "^";
        gotoXY(25, 14);
        cout << "|";
        gotoXY(0, 19);
        system("pause");

        gotoXY(21, 16);
        cout << "   ";
        gotoXY(19, 13);
        cout << "^";
        gotoXY(19, 14);
        cout << "|";

        NewNode -> next = p -> next;
        NewNode -> prev = p;
        p -> next -> prev = NewNode;
        p -> next = NewNode;
    }
}
void AddBefore (PNode p, PNode NewNode)
{
    if (!p->prev) { AddFirst(NewNode); }
    else
    {
        gotoXY(0, 4);
        cout << "                 /-------\\" << endl;
        cout << "                 |NewNode|" << endl;
        cout << "                 \\-------/" << endl;
        cout << "                     |" << endl;
        cout << "                     \\/" << endl;
        cout << "                /------------\\" << endl;
        cout << "                | |        | |  /-\\" << endl;
        cout << "                | |" << setw(8) << NewNode << "| |  |p|" << endl;
        cout << "                \\------------/  \\-/" << endl;
        cout << "                                 |" << endl;
        cout << "                                 \\/" << endl;
        cout << "       /------------\\   /------------\\" << endl;
        cout << "  ...->| |" << setw(8) << p->prev->el << "| |-->| |" << setw(8) << p->el << "| |->NULL" << endl;
        cout << "  ...<-| |" << setw(8) << p->prev << "| |<--| |" << setw(8) << p << "| |" << endl;
        cout << "       \\------------/   \\------------/" << endl;
        if (p->next) {
            gotoXY(38, 16);
            cout << "->... ";
            gotoXY(38, 17);
            cout << "<-...";
        }
        gotoXY(0, 19);
        system("pause");

        gotoXY(19, 10);
        cout << setw(8) << NewNode->el;
        gotoXY(0, 19);
        system("pause");

        gotoXY(17, 13);
        cout << "|";
        gotoXY(17, 14);
        cout << "\\/";
        gotoXY(0, 19);
        system("pause");

        gotoXY(28, 13);
        cout << "|";
        gotoXY(28, 14);
        cout << "\\/";
        gotoXY(0, 19);
        system("pause");

        gotoXY(21, 16);
        cout << "   ";
        gotoXY(19, 13);
        cout << "^";
        gotoXY(19, 14);
        cout << "|";
        gotoXY(0, 19);
        system("pause");

        gotoXY(21, 17);
        cout << "   ";
        gotoXY(25, 13);
        cout << "^";
        gotoXY(25, 14);
        cout << "|";

        NewNode -> prev = p -> prev;
        NewNode -> next = p;
        p -> prev -> next = NewNode;
        p -> prev = NewNode;
    }
}

void DeleteHead ()
{
    if (Head->next) {
        gotoXY(0, 4);
        cout << "       /-------\\" << endl;
        cout << "       |   Head|" << endl;
        cout << "       \\-------/" << endl;
        cout << "           |" << endl;
        cout << "           \\/" << endl;
        cout << "       /------------\\            /------------\\" << endl;
        cout << "       | |" << setw(8) << Head->el << "| |----------->| |"  << setw(8) << Head->next->el << "| |->NULL" << endl;
        cout << " NULL<-| |" << setw(8) << Head << "| |<-----------| |"  << setw(8) << Head->next << "| |" << endl;
        cout << "       \\------------/            \\------------/" << endl;
        if (Head->next->next) {
            gotoXY(47, 10);
            cout << "->... ";
            gotoXY(47, 11);
            cout << "<-...";
        }
        gotoXY(0, 19);
        system("pause");

        gotoXY(0, 4);
        cout << "       /-------\\                   /-------\\" << endl;
        cout << "       |OldHead|                   |NewHead|" << endl;
        cout << "       \\-------/                   \\-------/" << endl;
        cout << "           |                          |" << endl;
        cout << "           \\/                         \\/" << endl;
        gotoXY(0, 19);
        system("pause");

        gotoXY(0, 10);
        cout << "       | |" << setw(8) << Head->el << "| |->NULL      " << endl;
        cout << " NULL<-| |" << setw(8) << Head << "| |      NULL<-| |"  << setw(8) << Head->next << "| |" << endl;
        gotoXY(0, 19);
        system("pause");
    }
    Head = Head -> next;
    if (Head) { Head -> prev = NULL; }
    else { Tail = NULL; }
}
void DeleteTail ()
{
    if (Tail->prev) {
        gotoXY(0, 4);
        cout << "                                   /-------\\" << endl;
        cout << "                                   |   Tail|" << endl;
        cout << "                                   \\-------/" << endl;
        cout << "                                       |" << endl;
        cout << "                                       \\/" << endl;
        cout << "       /------------\\            /------------\\" << endl;
        cout << "       | |" << setw(8) << Tail->prev->el << "| |----------->| |"  << setw(8) << Tail->el << "| |->NULL" << endl;
        cout << " NULL<-| |" << setw(8) << Tail->prev << "| |<-----------| |"  << setw(8) << Tail << "| |" << endl;
        cout << "       \\------------/            \\------------/" << endl;
        if (Tail->prev->prev) {
            gotoXY(0, 10);
            cout << "  ...->";
            gotoXY(0, 11);
            cout << "  ...<-";
        }
        gotoXY(0, 19);
        system("pause");

        gotoXY(0, 4);
        cout << "       /-------\\                    /-------\\" << endl;
        cout << "       |NewTail|                    |OldTail|" << endl;
        cout << "       \\-------/                    \\-------/" << endl;
        cout << "           |                           |" << endl;
        cout << "           \\/                          \\/" << endl;
        gotoXY(0, 19);
        system("pause");

        gotoXY(7, 10);
        cout << "| |" << setw(8) << Tail->prev->el << "| |->NULL     " << endl;
        gotoXY(7, 11);
        cout << "| |" << setw(8) << Tail->prev << "| |     NULL<-| |"  << setw(8) << Tail << "| |" << endl;
        gotoXY(0, 19);
        system("pause");
    }
    Tail = Tail -> prev;
    if (Tail) { Tail -> next = NULL; }
    else { Head = NULL; }
}
void DeleteNode (PNode OldNode)
{
    if (Head == OldNode) {
        DeleteHead();
    } else if (Tail == OldNode) {
        DeleteTail();
    } else {
        gotoXY(0, 4);
        cout << "                /-------\\" << endl;
        cout << "                |OldNode|" << endl;
        cout << "                \\-------/" << endl;
        cout << "                    |" << endl;
        cout << "                    \\/" << endl;
        cout << "               /------------\\ " << endl;
        cout << "               | |" << setw(8) << OldNode->el << "| |" << endl;
        cout << "               | |" << setw(8) << OldNode << "| |" << endl;
        cout << "               \\------------/ " << endl;
        cout << "                |  ^     ^ |" << endl;
        cout << "                \\/ |     | \\/" << endl;
        cout << "       /------------\\   /------------\\ " << endl;
        cout << "       | |" << setw(8) << OldNode->prev->el << "| |   | |" << setw(8) << OldNode->next->el << "| |->NULL" << endl;
        cout << " NULL<-| |" << setw(8) << OldNode->prev << "| |   | |" << setw(8) << OldNode->next << "| |" << endl;
        cout << "       \\------------/   \\------------/" << endl;
        if (OldNode->prev->prev) {
            gotoXY(0, 16);
            cout << "  ...->";
            gotoXY(0, 17);
            cout << "  ...<-";
        }
        if (OldNode->next->next) {
            gotoXY(38, 16);
            cout << "->... ";
            gotoXY(38, 17);
            cout << "<-...";
        }
        gotoXY(0, 19);
        system("pause");

        gotoXY(19, 13);
        cout << " " << endl;
        gotoXY(19, 14);
        cout << " " << endl;
        gotoXY(21, 16);
        cout << "-->" << endl;
        gotoXY(0, 19);
        system("pause");

        gotoXY(25, 13);
        cout << " " << endl;
        gotoXY(25, 14);
        cout << " " << endl;
        gotoXY(21, 17);
        cout << "<--" << endl;
        gotoXY(0, 19);
        system("pause");

        gotoXY(16, 13);
        cout << "                               " << endl;
        gotoXY(16, 14);
        cout << "                               " << endl;
        gotoXY(0, 19);

        OldNode -> prev -> next = OldNode -> next;
        if (Head) { OldNode -> next -> prev = OldNode -> prev; }
        else { Tail = NULL; }
        delete OldNode;
    }
}

PNode Find (short int LostEl)
{
    PNode q = Head;
    while (q) {
        if (LostEl == q->el) { return q; }
        q = q -> next;
    }
    return q;
}
PNode Findex (short int LostEl)
{
    PNode q = Head;
    if (q) {
        if (LostEl == q->el) { set_col(LightGreen, Black); }
        gotoXY(0, 4);
        cout << "       /-------\\" << endl;
        cout << "       |  Head |" << endl;
        cout << "       \\-------/" << endl;
        cout << "           |" << endl;
        cout << "           \\/" << endl;
        cout << "      /------------\\" << endl;
        if (q->next) {
            cout << "      | |" << setw(8) << q->el << "| |" << endl;
            cout << "NULL<-| |" << setw(8) << q << "| |" << endl;
            cout << "      \\------------/" << endl;
            set_col(White, Black);
            if (LostEl == q->el) {
                gotoXY(20, 10);
                cout << "->...";
                gotoXY(20, 11);
                cout << "<-...";
                return q;
            }
            q = q -> next;
            int i = 1;
            while (q) {
                if (LostEl == q->el) { set_col(LightGreen, Black); }
                gotoXY(20*i, 9);
                cout << "      /------------\\" << endl;
                gotoXY(20*i, 10);
                cout << "----->| |" << setw(8) << q->el << "| |->NULL" << endl;
                gotoXY(20*i, 11);
                cout << "<-----| |" << setw(8) << q << "| |" << endl;
                gotoXY(20*i, 12);
                cout << "      \\------------/" << endl;
                if (q == Tail) {
                    gotoXY(24*i, 4);
                    cout << "        /-------\\" << endl;
                    gotoXY(24*i, 5);
                    cout << "        |  Tail |" << endl;
                    gotoXY(24*i, 6);
                    cout << "        \\-------/" << endl;
                    gotoXY(24*i, 7);
                    cout << "            |" << endl;
                    gotoXY(24*i, 8);
                    cout << "            \\/" << endl;
                }
                i++;
                set_col(White, Black);
                if (LostEl == q->el) {
                    if (q != Tail) {
                        gotoXY(20*i, 10);
                        cout << "->... ";
                        gotoXY(20*i, 11);
                        cout << "<-...";
                    }
                    return q;
                }
                q = q -> next;
            }
        } else {
            cout << "       | |" << setw(8) << q->el << "| |->NULL" << endl;
            cout << " NULL<-| |" << setw(8) << q << "| |" << endl;
            cout << "       \\------------/" << endl;
            set_col(White, Black);
            if (LostEl == q->el) { return q; }
            q = q -> next;
        }
    }
    system("cls");
    return q;
}

void DeleteAll ()
{
    PNode q = Head;
    while (q)
    {
        Head = q -> next;
        if (Head) { Head -> prev = NULL; }
        else { Tail = NULL; }
        q = q->next;
    }
}

bool check_newe (const int &newe)
{
    PNode q = Head;
    while (q) {
        if (newe == q->el) { return false; }
        q = q->next;
    }
    return true;
}

void work_with_list (const int &con)
{
    srand((unsigned)time(0));
    system("cls");
    short int j = 0;
    short int m_operation;
    vector<string> MenuOperationList = { "Добавить элемент", "Удалить элемент", "Поиск элемента", "Выйти" };
    Menu(m_operation, MenuOperationList, con);
    while (m_operation != 4)
    {
        if (Head) { j=Head->el; }
        PrintList(Find(j));
        short int m_ex;
        int i;
        switch (m_operation)
        {
        case 1: { // Добавить элемент
                int newe;
                if (Head) {
                    vector<string> MenuEx = { "Голову", "Хвост", "Перед заданным", "После заданного" };
                    Menu(m_ex, MenuEx, con);
                } else { m_ex = 1; }
                PrintList(Find(j));
                do {
                    gotoXY(0, 1);
                    cout << " Введите значение нового элемента [ -100; 100]:       ";
                    gotoXY(48, 1);
                    cin >> newe;
                } while ((newe < -100) || (newe > 100)  || !check_newe(newe));
                switch (m_ex)
                {
                case 1: {
                        AddFirst(CreateNode(newe));
                        PrintList(Find(j));
                    break; }
                case 2: {
                        if (Tail) { j = Tail->el;; }
                        AddLast(CreateNode(newe));
                        PrintList(Find(j));
                    break; }
                case 3: {
                        do {
                            gotoXY(0, 2);
                            cout << " Введите значение элемента, перед которым вставить новый узел (кроме головы и хвоста):       ";
                            gotoXY(87, 2);
                            cin >> i;
                        } while (check_newe(i));
                        AddBefore(Find(i), CreateNode(newe));
                        j = Find(i)->prev->el;
                        PrintList(Find(j));
                    break; }
                case 4: {
                        do {
                            gotoXY(0, 2);
                            cout << " Введите значение элемента, после которого вставить новый узел (кроме головы и хвоста):       ";
                            gotoXY(88, 2);
                            cin >> i;
                        } while (check_newe(i));
                        AddAfter(Find(i), CreateNode(newe));
                        j = Find(i)->next->el;
                        PrintList(Find(j));
                    }
                }
            break; }
        case 2: { // Удаление элемента
                if (Head) {
                    vector<string> MenuEx = { "Голову", "Хвост", "Заданный" };
                    Menu(m_ex, MenuEx, con);
                    PrintList(Find(j));
                    switch (m_ex)
                    {
                    case 1: { // Первый
                            DeleteHead();
                            PrintList(Find(j));
                            cout << "    ";
                            gotoXY(0, 17);
                        break; }
                    case 2: { // Последний
                            DeleteTail();
                            PrintList(Find(j));
                            cout << "    ";
                        break; }
                    case 3: { // Заданный
                            do {
                                gotoXY(0, 1);
                                cout << " Введите значение удаляемого узла (кроме головы и хвоста):       ";
                                gotoXY(59, 1);
                                cin >> i;
                            } while (check_newe(i));
                            PrintList(Find(i));
                            DeleteNode(Find(i));
                            PrintList(Find(j));
                            cout << "    ";
                        }
                    }
                } else { cout << " Нечего удалять" << endl; }
            break; }
        case 3: {
                if (Head) {
                    cout << "\n Введите значение элемента: ";
                    cin >> i;
                    PNode f = Findex(i);
                    if (f) {
                        PrintList(f);
                    } else { cout << "Элемент не найден" << endl; }
                } else { cout << "Список пуст"; }
            break; }
        }
        gotoXY(0, 19);
        system("pause");
        system("cls");
        PrintList(Find(j));
        Menu(m_operation, MenuOperationList, con);
    }
    DeleteAll();
}
