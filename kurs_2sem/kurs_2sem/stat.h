#ifndef STAT_H_INCLUDED
#define STAT_H_INCLUDED

#include <string>

void input_stat (const int &stud_r_answer_i, const int &r_answer_i, const std::string &nickname);

bool checkdata (const std::string &nickname, const std::string &temp);
void init_stat (const std::string &nickname, const bool &admin, const int &con);

#endif // STAT_H_INCLUDED
