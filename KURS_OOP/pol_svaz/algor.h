
#ifndef ALGOR_H
#define ALGOR_H

#include <QString>
#include <QStack>

class algor
{
public:
    algor() {}

    static bool is_op (const QChar &op) // проверка на то является ли символ операцией
    {
        return ((op == '^') || (op == '+') || (op == '-') || (op == '*') || (op == '/') || (op == '%'));
    }
    static uint8_t priority (const QChar &op) // возвращение приоритета той или иной операции
    {
        return (op == '^') ? 3 :
               (op == '*' || op == '/' || op == '%') ? 2 :
               (op == '+' || op == '-') ? 1 :
               0;
    }

    static void main_alg(const QChar &qc, QString &vh, QStack<QChar> &op)
    {
        if (qc == '(')
        {
            op.push(qc);
        } else if (qc == ')')
        {
            while (op.top() != '(')
            {
                vh += ' ';
                vh += op.top();
                op.pop();
            }
            op.pop();
        } else if (isdigit(qc.toLatin1()))
        {
            vh += qc;
        } else if (is_op(qc))
        {
            vh += ' ';
            while (!op.empty() && priority(op.top()) >= priority(qc))
            {
                vh += op.top();
                vh += ' ';
                op.pop();
            }
            op.push(qc);
        }
    }

    static QString alg(QString in_qs) // собственно алгоритм Дейкстры перевода в обратную польскую запись
    {
        QString vh;
        QStack<QChar> op;

        QChar qc;
        while(in_qs.size() > 0)
        {
            qc = in_qs[0];
            in_qs.remove(0, 1);
            main_alg(qc, vh, op);
        }

        while (!op.empty())
        {
            vh += ' ';
            vh += op.top();
            op.pop();
        }

        return vh;
    }

    static void alg(QString in_qs, QVector<QString> &vsvh, QVector<QString> &vscop) // собственно алгоритм Дейкстры перевода в обратную польскую запись
    {
        QString vh;
        QStack<QChar> op;
        QStack<QChar> tmp;

        vsvh.push_back("");
        vscop.push_back("");

        QChar qc;
        while(in_qs.size() > 0)
        {
            qc = in_qs[0];
            in_qs.remove(0, 1);
            main_alg(qc, vh, op);

            vsvh.push_back(vh);

            tmp = op;
            vscop.push_back("");
            while (!tmp.empty())
            {
                vscop[vscop.size()-1] += tmp.top();
                tmp.pop();
            }
        }

        while (!op.empty())
        {
            vh += ' ';
            vh += op.top();
            op.pop();
        }
        vsvh.push_back(vh);
        vscop.push_back("");
    }
};

#endif // ALGOR_H
