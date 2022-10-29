#ifndef TRAIN_COMP_H
#define TRAIN_COMP_H

#include <random>
#include <fstream>
#include <ctime>

#include "algor.h"
#include "reader.h"

class train_comp
{
public:
    train_comp() {}

    static QString super_easy(std::random_device &re, std::uniform_int_distribution<int> &dis); // составление супер-легкого задания
    static QString easy(std::random_device &re, std::uniform_int_distribution<int> &dis); // составление легкого задания
    static QString normal(std::random_device &re, std::uniform_int_distribution<int> &dis); // составление нормального задания
    static QString hard(std::random_device &re, std::uniform_int_distribution<int> &dis); // составление тяжелого задания

    static QString check_stat(const QString &name, const QString &level, const QString *ex, const QString *ans, const int &n); // проверка и запись в статистику

private:
    static QChar operationt_rand(const uint &i); // случайная операция

    static void hooks(const QString &qs, const int &op_i, const int &gap, int &i, int &j); // получение номеров вставки открывающей и закрывающей скобки


};

#endif // TRAIN_COMP_H
