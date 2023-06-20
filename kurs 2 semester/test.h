#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

using namespace std;

void init_Quest (vector<Quest> &Test, int &r_answer_i);

void print_Quest (const Quest &Test);
void print_Quests (const vector<Quest> &Test);

void input_ans (const Quest &Test, int &quest_r_ans);
void main_test (const vector<Quest> &Test, int &stud_r_answer_i);

void testing (const string &nickname);

#endif // TEST_H_INCLUDED
