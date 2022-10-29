#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <struct.h>

void PrintList (PNode p);

PNode CreateNode (short int NewEl);

void AddFirst (PNode NewNode);
void AddLast(PNode NewNode);
void AddAfter (PNode p, PNode NewNode);
void AddBefore (PNode p, PNode NewNode);

void DeleteHead ();
void DeleteTail ();
void DeleteNode(PNode OldNode);

PNode Find (short int LostEl);
PNode Findex (short int LostEl);

void DeleteAll ();

bool check_newe (const int &newe);

void work_with_list (const int &con);

#endif // LIST_H_INCLUDED
