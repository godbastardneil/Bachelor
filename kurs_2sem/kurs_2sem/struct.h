#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

#include <string>
#include <vector>

struct Answer
{
    std::string ans;
    bool ans_r;
};
struct Quest
{
    std::string question;
    std::vector<Answer> answer_Quest;
};

struct Node
{
    short int el;
    Node *next, *prev;
};
typedef Node *PNode;

#endif // STRUCT_H_INCLUDED
