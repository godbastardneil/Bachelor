#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>

#include <math.h>
#include <random>

#include "bit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


static QVector<QVector<bit>> g_table = {
                                        {bit("11")},
                                        {bit("101"), bit("111")},
                                        {bit("1001"), bit("1011"), bit("1101"), bit("1111")},
                                        {bit("10001"), bit("10011"), bit("10101"), bit("10111"), bit("11001"), bit("11011"), bit("11101"), bit("11111")},
                                        {bit("100001"), bit("100011"), bit("100101"), bit("100111"), bit("101001"), bit("101011"),
                                            bit("101101"), bit("101111"), bit("110001"), bit("111001"), bit("111011"), bit("111101"), bit("111111")},
                                        {bit("1000001"), bit("1000011"), bit("1000101"), bit("1000111"), bit("1001001"), bit("1001011"),
                                            bit("1001101"), bit("1001111"), bit("1010001"), bit("1010011"), bit("1010101"), bit("1010111"),
                                            bit("1011001"), bit("1011011"), bit("1011101"), bit("1011111"), bit("1100001"), bit("1100011"),
                                            bit("1100101"), bit("1100111"), bit("1101101"), bit("1101111"), bit("1110001"), bit("1110011"),
                                            bit("1110101"), bit("1110111"), bit("1111001"), bit("1111011"), bit("1111101"), bit("1111111")},
                                        {bit("10000001"), bit("11100001")},
                                        {bit("100000001"), bit("100000011")},
                                        {bit("1000000001"), bit("1100000001")},
                                        {bit("10000000001")},
                                        {bit("100000000001"), bit("100000000011"), bit("100000000101")},
                                        {bit("1000000000001")},
                                        {bit("10000000000001")},
                                        {bit("100000000000011"), bit("100000000000101")}
                                       };

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_init_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;

    QString qs;

    bit b;
    bit _b;
    bit bi;

    bit a;
    bit g;

    int r;
    int n;
    int k;

    void find_error();

    void get_g();
    void init(QString arg1);
};
#endif // MAINWINDOW_H
