#ifndef SEARCHPROCESS_H
#define SEARCHPROCESS_H

#include <QString>
#include <QVector>

class searchprocess
{

public:
    searchprocess() {}

    void set_str (const QString &qs) { str = qs; }
    void set_pattern (const QString &qs) { pattern = qs; }
    void clear ()
    {
        int n = proz.size();
        for (int i=0; i<n; ++i) { proz[i].clear(); }
        proz.clear();
        delete [] d;
        dm = 0;
    }
    QString get_str () { return str; }
    QString get_pattern () { return pattern; }
    QVector<QVector<QString>> get_proz () { return proz; }
    int get_table_size() { return dm; }
    QString get_table () {
        int m = pattern.size()+1;
        QString table;
        for (int i=0; i<m; ++i) {
            table += QString::number(d[i]) + ' ';
        }
        return table;
    }

    int is(const QChar &c, const int &i); // поиск наличия символа в слове до этого
    void table(); // заполнение таблицы смещения
    void present(bool b, int p, int j, int m, int i);
    bool BMH(); // салгоритм поиска

private:
    QString str = "строка"; // строка, в которой ищут шаблон
    QString pattern = "подстрока"; // шаблон, который ищится
    QVector<QVector<QString>> proz; // демонстрация
    int* d; // таблица смещения
    int dm = 0; // размер таблицы

    searchprocess(const searchprocess &)  = delete;
    searchprocess(const searchprocess &&) = delete;
    searchprocess& operator=(const searchprocess &)  = delete;
    searchprocess& operator=(const searchprocess &&) = delete;

};

#endif // SEARCHPROCESS_H
