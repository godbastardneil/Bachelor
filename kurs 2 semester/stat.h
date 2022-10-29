#ifndef STAT_H_INCLUDED
#define STAT_H_INCLUDED

using namespace std;

void input_stat (const int &stud_r_answer_i, const int &r_answer_i, const string &nickname);

bool checkdata (const string &nickname, const string &temp);
void init_stat (const string &nickname, const bool &admin, const int &con);

#endif // STAT_H_INCLUDED
