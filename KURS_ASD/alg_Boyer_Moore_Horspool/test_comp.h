#ifndef TEST_COMP_H
#define TEST_COMP_H

#include <QString>
#include <QVector>
#include <reader.h>
#include <ctime>

struct answer {
    QString ans; // содержание ответа
    bool r; // правильность ответа
};

struct quest {
    QString question; // вопрос
    QVector<answer> q_answer; // ответы на вопросы
};


class test_comp
{

public:
    static test_comp& Instance() {
        static test_comp test_comp;
        return test_comp;
    }
    test_comp() {}

    uint8_t get_points() { return points; }

    QVector<quest> create_test(QString fname);

    uint8_t check_ans (const QVector<answer> &test, const QString &ans);
    QString input_stat(const QString &name, const int &res);

private:
    uint8_t points;
    reader writer;

    test_comp(const test_comp &)  = delete;
    test_comp(const test_comp &&) = delete;
    test_comp& operator=(const test_comp &)  = delete;
    test_comp& operator=(const test_comp &&) = delete;
};

#endif // TEST_COMP_H
