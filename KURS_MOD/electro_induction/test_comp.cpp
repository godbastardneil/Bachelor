#include "test_comp.h"

#include <QDebug>

QVector<quest> test_comp::create_test(QString text)
{
    std::random_device rd;
    std::mt19937 mt(rd());

    points = 0;
    QVector<quest> testing;

    // теги ? - вопрос, + - вариант ответа, ! - правильный вариант ответа
    QChar q = '?';
    QChar a = '+';
    QChar ra = '!';
    int i = 0; // какой сейчас вопрос записывается
    quest ex;
    answer answ;
    while (text.size() > 0)
    {
        QChar t = text[0];
        text.remove(0, 1);
        if (text[0] == ' ') { text.remove(0, 1); }

        QString qs = text.left(text.indexOf('\n'));
        text.remove(0, qs.size());

        if (text.size()>0) { text.remove(0, 1); }

        if (t == q)
        {
            if (i>0)
            {
                std::shuffle(ex.q_answer.begin(), ex.q_answer.end(), mt);
                testing.push_back(ex);
                ex.q_answer.clear();
            }
            ex.question = qs;
            ++i;

        } else if ((t == a) || (t == ra))
        {
            answ.ans = qs;
            if (t == a)
            {
                answ.r = 0;
            } else if (t == ra) { answ.r = 1;}
            ex.q_answer.push_back(answ);

        } else if (i>0)
        {
            ex.question += '\n' + qs;

        } else { ex.question += qs; }

    }
    std::shuffle(ex.q_answer.begin(), ex.q_answer.end(), mt);
    testing.push_back(ex);
    ex.q_answer.clear();
    std::shuffle(testing.begin(), testing.end(), mt);
    testing.erase(testing.begin()+num, testing.end());
    for (int i=0; i<num; ++i)
    {
        int m = testing[i].q_answer.size();
        if (m == 1) { ++points; }
        for (int j=0; j<m; ++j)
        {
            if (testing[i].q_answer[j].r) { ++points; }
        }
    }

    return testing;
}

uint8_t test_comp::check_ans(const QVector<answer> &test, const QString &ans)
{
    int k = test.size();
    if (k>1)
    {
        int m = 0;
        for (int i=0; i<k; ++i)
        {
            if (test[i].r) { ++m; }
        }

        int p = ans.length();
        if (p>m) { return 0; }
        uint8_t quest_r_ans = 0;
        for (int j=0; j<p; j++)
        {
            int a = ans[j].toLatin1() - '0' - 1;
            if ((a>=0) && (a<k) && (test[a].r)) { ++quest_r_ans; }
        }
        return quest_r_ans;
    } else
    {
        if (test[0].ans == ans)
        {
            return 2; // ответы, которые нужно вводить руками оцениваются в два балла
        } else { return 0; }
    }
}

QString test_comp::input_stat(const QString &name, const int &res)
{
    time_t t = time(nullptr);
    std::string ti = asctime(localtime(&t));

    std::ofstream out ("files/stat.txt", std::ios::binary | std::ios::app);

    std::string temp = "<pre>\nИмя: " + name.toStdString() + "Баллы: " + std::to_string(res) + '/' + std::to_string(points) + "\nОценка: ";
    if ((double(res)/points) > 0.80)
    {
        temp += std::to_string(5);
    } else if ((double(res)/points) > 0.70)
    {
        temp += std::to_string(4);
    } else if ((double(res)/points) > 0.50)
    {
        temp += std::to_string(3);
    } else { temp += std::to_string(2); }
    temp += "\nВремя: " + ti + "</pre>\n";
    QString stat = QString::fromStdString(temp);
    int c = reader::get_code();
    for (char &i: temp) { i ^= c; }
    out.write(temp.data(), int(temp.size()));

    out.close();
    return stat;
}
