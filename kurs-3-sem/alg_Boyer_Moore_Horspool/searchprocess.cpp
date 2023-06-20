#include "searchprocess.h"

int searchprocess::is(const QChar &c, const int &i)
{
    int n = pattern.size()-2;
    for (int j=n; j>i; --j)
    {
        if (c == pattern[j]) { return n-j+1; }
    }
    return n-i+1;
}
void searchprocess::table()
{
    QVector<QString> qvs;
    proz.push_back(qvs);
        QString t = "<pre>";
        for (int i=0; i<dm-1; ++i) { t += pattern[i] + QString(1, ' '); }
        t += '\n';
    d[dm-1] = d[dm-2] = dm-1;
        proz[0].push_back(t + QString(dm-1, ' ') + QString(dm-1, ' ') + QString::number(d[dm-1]) + "</pre>");
    for (int i=dm-3; i>=0; --i)
    {
        d[i] = is(pattern[i], i);
            proz[0].push_back(t + QString(i, ' ') + QString(i, ' ') + QString::number(d[i]) + "</pre>");
            for (int j=i; j<dm-2; ++j)
            {

            }
    }
    d[dm-2] = is(pattern[dm-2], -1);
        proz[0].push_back(t + QString(dm-2, ' ') + QString(dm-2, ' ') + QString::number(d[dm-2]) + "</pre>");
}

// b - каким цветом выделить <---> 1 - сравнение соответствующих букв
//                                 0 - поиск буквы в подстроке
// p - страница визуализации и количество \n
// j - символ шаблома, который участвует в алгоритме
// m - размер шаблона
// i - количество отступов и номер первого элемента сравниваемой части строки
void searchprocess::present(bool b, int p, int j, int m, int i)
{
    proz[p].push_back("<pre>" + str + QString(p, '\n') + QString(i, ' '));
    int n = proz[p].size()-1;
    proz[p][n].append(pattern.data(), j);
    if (b)
    {
        proz[p][n] += "<font color=\"green\">";

    } else { proz[p][n] += "<font color=\"red\">"; }
    proz[p][n] += pattern[j] + "</font>";

    for (int k=j+1; k<m; ++k) { proz[p][n] += pattern[k]; }
    proz[p][n] += "</pre>";
}

bool searchprocess::BMH()
{
    int n = str.size();
    int m = pattern.size();

    QVector<QString> qvs;
    if (n < m)
    {
        proz.push_back(qvs);
        proz[0].push_back("<pre>подстрока длинее строки</pre>");
        return 0;
    }
    dm = m+1;
    d = new int[dm];
    table();

    for (int i=0, p=1, j=0, l=0; (i<n); i += d[j], ++p)
    {
        proz.push_back(qvs);
        proz[p].push_back("<pre>" + str + QString(p, '\n') + QString(i, ' ') + pattern + "</pre>");
        for (j=m-1; (j>=0) && (str[i+j] == pattern[j]); --j) { present(1, p, j, m, i); }

        if (j != -1)
        {
            for (l = m-1; (l >= 0) && (str[i+m-1] != pattern[l]); --l) { present(0, p, l, m, i); }

            if(l != -1)
            {
                j = l;
            } else { j = m; }

        } else { return 1; }
    }
    return 0;
}
