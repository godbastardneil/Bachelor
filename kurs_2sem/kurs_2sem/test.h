#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <vector>
#include <string>
#include "struct.h"

void init_Quest (std::vector<Quest> &Test, int &r_answer_i);

void print_Quest (const Quest &Test);
void print_Quests (const std::vector<Quest> &Test);

void input_ans (const Quest &Test, int &quest_r_ans);
void main_test (const std::vector<Quest> &Test, int &stud_r_answer_i);

void testing (const std::string &nickname);

#endif // TEST_H_INCLUDED
