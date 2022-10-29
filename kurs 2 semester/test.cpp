#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <conio.h>

#include "struct.h"
#include "stat.h"
#include "print.h"

#include "test.h"

using namespace std;

void init_Quest (vector<Quest> &Test, int &r_answer_i)
{
    ifstream in ("all_test.dat", ios::binary);
    string temp;
    char question_mark = '?';
    char answer_mark = '+';
    char ans_r_mark = '!';
    Quest test;
    Answer answer;
    int i = 0;
    int j = 0;
    if (in) {
        while (getline(in, temp, 'Y'))
        {
            for (char &i: temp) { i ^= 0xAABBC53; }
            char t = temp[0];
            temp.erase(0, 1);
            if (t == question_mark) {
                if (i>0) {
                    random_shuffle(test.answer_Quest.begin(), test.answer_Quest.end());
                    Test.push_back(test);
                    test.answer_Quest.clear();
                    j = 0;
                }
                test.question = temp;
                i++;
            } else if ((t != answer_mark) && (t != ans_r_mark)) {
                test.question += "\n\t\t" + temp;
            } else {
                answer.ans = temp;
                if (t == answer_mark) { answer.ans_r = 0;
                } else if (t == ans_r_mark) {
                    answer.ans_r = 1;
                }
                test.answer_Quest.push_back(answer);
                j++;
            }
        }
        random_shuffle(test.answer_Quest.begin(), test.answer_Quest.end());
        Test.push_back(test);
        test.answer_Quest.clear();
        random_shuffle(Test.begin(), Test.end());
        Test.erase(Test.begin()+5, Test.end());
        for (int i=0; i<5; i++)
        {
            int m = Test[i].answer_Quest.size();
            for (int j=0; j<m; j++)
            {
            if (Test[i].answer_Quest[j].ans_r) { r_answer_i++; }
            }
        }
    } else { cout << "Файл не найден" << endl; }
    in.close();
}

void print_Quest (const Quest &Test)
{
    int m = Test.answer_Quest.size();
    for (int j=0; j<m; j++)
    {
        cout << "\t" << j+1 << ". " << Test.answer_Quest[j].ans << endl;
    }
    cout << endl;
}
void print_Quests (const vector<Quest> &Test)
{
    for (int i=0; i<5; i++)
    {
        cout << i+1 << ". " << Test[i].question << endl;
        print_Quest(Test[i]);
    }
}

void input_ans(const Quest &Test, int &quest_r_ans)
{
    string ans;
    vector<int> answers;
    cout << " Введите ответы подряд, через пробел: ";
    getline(cin, ans);

    int m = 0;
    for (size_t i=0; i<Test.answer_Quest.size(); i++)
    {
        if (Test.answer_Quest[i].ans_r) { m++; }
    }

    bool num = 0;
    int n = 0;
    int p = ans.length();
    for (int j=0; j<p; j++) {
        if ((ans[j]>='0') && (ans[j]<='9') && (!num)) {
            answers.push_back(atoi(&ans[j]));
            num = 1;
            n++;
        } else { num = 0; }
    }

    if (n>m) { return; }
    for (int j=0; j<n; j++)
    {
        if (answers[j]>0) {
            if (Test.answer_Quest[answers[j]-1].ans_r) { quest_r_ans++; }
        }
    }
}
void main_test (const vector<Quest> &Test, int &stud_r_answer_i)
{
    int n = 5;
    int comand;
    int i = 0;
    vector<int> quest_r_ans (n, 0);
    vector<bool> was (n, 0);;
    while(i<n) {
        system("cls");
        cout << i+1 << ". " << Test[i].question << endl;
        print_Quest(Test[i]);
        if (was[i]) { cout << " Вы уже ответили на этот вопрос" << endl; }
        cout << "\n\t\t\t Esc - выход в меню \n\t\t\t Enter - ответить \n\t\t\t --> - вперед \n\t\t\t <-- - назад" << endl;
        do {
            cin.clear();
            comand = getch();
        } while ((comand != 27) && (comand != 13) && (comand != 77) && (comand != 75));
        switch (comand)
        {
        case 27 : { i = n; break; } // Esc - в меню
        case 13 : // Enter - ответить
            {
                was[i] = 1;
                quest_r_ans[i] = 0;
                input_ans(Test[i], quest_r_ans[i]);
                i++;
            break; }
        case 77 : { i++; break; } // --> - вперед
        case 75 : // <-- - назад
            {
                if (i == 0) {
                    i = n;
                } else { i--; }
            }
        }
        cout << endl;
    }
    for (int j = 0; j<n; j++) { stud_r_answer_i += quest_r_ans[j]; }
}

void testing (const string &nickname)
{
    vector<Quest> Test;
    int r_answer_i = 0;
    int stud_r_answer_i = 0;
    init_Quest(Test, r_answer_i);
    main_test(Test, stud_r_answer_i);
    input_stat(stud_r_answer_i, r_answer_i, nickname);
    Test.clear();
}
