#ifndef EXERCISE_COMP_H
#define EXERCISE_COMP_H

#include <QString>
#include <QVector>

#include "reader.h"

struct task {
    QString ex; // задача
    QString how; // решение задачи
    QString ans; // ответ
};

class exercise_comp
{
public:
    exercise_comp() {}

    static QVector<task> create_exercise(QString text)
    {
        QVector<task> testing;

        // теги ? - задача, ! - ответ, + - решение
        QChar q = '?'; // задача
        QChar a = '+'; // решение
        QChar ra = '!'; // ответ

        int i = 0; // какой сейчас вопрос записывается
        task tmp;

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
                if (i > 0) { testing.push_back(tmp); }
                tmp.ex = qs;
                ++i;
            } else if (t == a)
            {
                tmp.how = qs;
            } else if (t == ra)
            {
                tmp.ans = qs;
            } else { tmp.how += qs; }
        }
        if (i > 0) { testing.push_back(tmp); }

        return testing;
    }

private:

    exercise_comp(const exercise_comp &)  = delete;
    exercise_comp(const exercise_comp &&) = delete;
    exercise_comp& operator=(const exercise_comp &)  = delete;
    exercise_comp& operator=(const exercise_comp &&) = delete;
};

#endif // EXERCISE_COMP_H
