#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

using namespace std;

struct Answer
{
    string ans;
    bool ans_r;
};
struct Quest
{
    string question;
    vector<Answer> answer_Quest;
};

struct Node
{
    short int el;
    Node *next, *prev;
};
typedef Node *PNode;

#endif // STRUCT_H_INCLUDED
