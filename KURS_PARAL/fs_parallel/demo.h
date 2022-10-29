#ifndef DEMO_H
#define DEMO_H

#include <QWidget>
#include <QFile>
#include <QMessageBox>
#include <QInputDialog>

#include <random>

#include "alg.cpp"

namespace Ui { class demo; }

class demo : public QWidget
{
    Q_OBJECT

public:
    explicit demo(QWidget *parent = nullptr);
    ~demo();

signals:
    void return_to_menu();

private slots:
    void on_return_to_clicked(); // возвращение в меню

    void on_begin_clicked();

    void on_algobox_currentTextChanged(const QString &arg1);

private:
    Ui::demo *ui;

    QStringList algs;
    QStringList pot;

    QVector<int> generate_str(const int &n);

    void init_stat(const int &n, const int &m, const double &time);

    int i;
    QString stat;

    demo(const demo &)  = delete;
    demo(const demo &&) = delete;
    demo& operator=(const demo &)  = delete;
    demo& operator=(const demo &&) = delete;
};

#endif // DEMO_H
