#include "train_comp.h"

QChar train_comp::operationt_rand(const uint &i)
{
    switch (i)
    {
    case 0:
        return '^';
    case 1:
        return '%';
    case 2:
        return '/';
    case 3:
        return '*';
    case 4:
        return '-';
    default:
        return '+';
    }
}

void train_comp::hooks(const QString &qs, const int &op_i, const int &gap, int &i, int &j)
{
    int tmp = 0;
    while (i<qs.size() && tmp<op_i-gap)
    {
        if (algor::is_op(qs[i])) { ++tmp; }
        ++i;
    }
    j = i;
    while (j<qs.size() && tmp<op_i+gap)
    {
        if (algor::is_op(qs[j])) { ++tmp; }
        ++j;
    }
    ++j;
    if (j<qs.size()) { --j; }
}

QString train_comp::super_easy(std::random_device &re, std::uniform_int_distribution<int> &dis)
{
    return (QString::number(dis(re)) + operationt_rand(dis(re)%6) + QString::number(dis(re)));
}

QString train_comp::easy(std::random_device &re, std::uniform_int_distribution<int> &dis)
{
    return ((super_easy(re, dis)) + operationt_rand(dis(re)%6) + super_easy(re, dis));
}

QString train_comp::normal(std::random_device &re, std::uniform_int_distribution<int> &dis)
{
    QString qs = ((easy(re, dis)) + operationt_rand(dis(re)%6) + super_easy(re, dis));
    int op_i = dis(re)%6;
    int i = 0, j = 0;
    if (op_i != 0)
    {
        hooks(qs, op_i, 1, i, j);
        qs.insert(i, '(');
        qs.insert(j, ')');
    }
    int tmp;
    do { tmp = dis(re)%6; } while(tmp == op_i || tmp-1 == op_i || tmp+1 == op_i);
    op_i = tmp;
    i = 0; j = 0;
    if (op_i != 0)
    {
        hooks(qs, op_i, 1, i, j);
        qs.insert(i, '(');
        qs.insert(j, ')');
    }
    return qs;
}

QString train_comp::hard(std::random_device &re, std::uniform_int_distribution<int> &dis)
{
    QString qs;
    if (dis(re) < 50)
    {
        qs = ((normal(re, dis)) + operationt_rand(dis(re)%6) + super_easy(re, dis));
    } else { qs = ((super_easy(re, dis)) + operationt_rand(dis(re)%6) + normal(re, dis)); }

    int i;
    int j;
    int op_i = dis(re)%8;
    int sk1 = qs.indexOf('(');
    int sk2 = qs.indexOf(')', sk1);
    int sk3 = qs.indexOf('(', sk2);
    int sk4 = qs.indexOf(')', sk3);
    if (op_i != 0)
    {
        do {
            i = 0, j = 0;
            hooks(qs, op_i, 2, i, j);
            op_i = dis(re)%8;
        } while(op_i != 0 && (((sk1 < i) && (sk2 > i)) || ((sk3 < i) && (sk4 > i)) || ((sk1 < j) && (sk2 > j)) || ((sk3 < j) && (sk4 > j))));
        if (op_i != 0)
        {
            qs.insert(i, '(');
            qs.insert(j, ')');
        }
    }
    return qs;
}

QString train_comp::check_stat(const QString &name, const QString &level, const QString *ex, const QString *ans, const int &n)
{
    time_t t = time(nullptr);
    std::string ti = asctime(localtime(&t));

    std::string temp = "<pre>\n Имя: " + name.toStdString() + "\n Уровень: " + level.toStdString();

    temp += "\n Ответы: ";
    int j = 0;
    for (int i = 0; i < n; ++i)
    {
        if (ans[i] == algor::alg(ex[i]))
        {
            temp += '1';
            ++j;
        } else { temp += '0'; }
    }

    temp += "\n Результат: " + std::to_string(j) + '/' + std::to_string(n);
    temp += "\n Время: " + ti + "</pre>\n";

    QString stat = QString::fromStdString(temp);

    std::ofstream out ("files/stat.txt", std::ios::binary | std::ios::app);
    int c = reader::get_code();
    for (char &i: temp) { i ^= c; }
    out.write(temp.data(), int(temp.size()));

    out.close();
    return stat;

}
