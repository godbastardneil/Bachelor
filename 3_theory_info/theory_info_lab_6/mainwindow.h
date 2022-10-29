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

enum {N = 0, K, R, S};

static QVector<QVector<int>> BCH = {
                                    {15,  11, 4,  1},
                                    {15,  7,  8,  2},
                                    {15,  5,  10,  3},
                                    {31,  11, 20,  5},
                                    {31,  6,  25,  7},
                                    {63,  10, 53,  13},
                                    {63,  7,  56,  15},
                                    {127, 15, 119, 27},
                                    {127, 8,  119, 31}
                                   };

static QVector<QVector<bit>> g_table = {
                                        {bit("111")},
                                        {bit("1011"), bit("1101")},
                                        {bit("10011"), bit("11111"), bit("111"), bit("111001")},
                                        {bit("100101"), bit("111101"), bit("110111"), bit("101111"), bit("110111"), bit("111011")},
                                        {bit("1000011"), bit("1010111"), bit("1100111"), bit("1001001"), bit("1101"), bit("1101101")},
                                        {bit("10001001"), bit("10001111"), bit("10011101"), bit("11110111"), bit("10111111"), bit("11010101"),
                                            bit("10000011"), bit("0"), bit("0"), bit("11001011"), bit("11100101")},
                                        {bit("100011101"), bit("101110111"), bit("111110011"), bit("101101001"), bit("110111101"), bit("111100111"),
                                            bit("100101011"), bit("111010111"), bit("010011"), bit("101100101"), bit("110001011"), bit("101100011"),
                                            bit("100011011"), bit("100111111"), bit("0"), bit("0"), bit("0"), bit("0"),
                                            bit("101011111"), bit("0"), bit("0"), bit("111000011"), bit("100111001"), bit("0"),
                                            bit("0"), bit("011111"), bit("0"), bit("0"), bit("0"), bit("0"),
                                            bit("0"), bit("0")},
                                        {bit("1000010001"), bit("1001011001"), bit("1100110001"), bit("1010011001"), bit("1100010011"), bit("1000101101"),
                                            bit("1001110111"), bit("1101100001"), bit("1011011011"), bit("1110000101"), bit("1000010111"), bit("1111101001"),
                                            bit("1111100011"), bit("1110001111"), bit("101101011"), bit("0"), bit("0"), bit("1100000001"),
                                            bit("1001101111"), bit("1111001101"), bit("1101110011"), bit("1111001011"), bit("1001111101"), bit("0"),
                                            bit("0"), bit("1111010101"), bit("1010010101"), bit("1010111101"), bit("0"), bit("0"),
                                            bit("0"), bit("0")},
                                        {bit("10000001001"), bit("10000001111"), bit("10100001101"), bit("11111111001"), bit("10010101111"), bit("10000110101"),
                                            bit("10001101111"), bit("10110101011"), bit("11101001101"), bit("10111111011"), bit("11111101011"), bit("10000011011"),
                                            bit("10100100011"), bit("11101111011"), bit("10100110001"), bit("11000100001"), bit("111101"), bit("11000010011"),
                                            bit("11101100011"), bit("10001000111"), bit("10111100101"), bit("10100011001"), bit("11000110001"), bit("11001111111"),
                                            bit("11101010101"), bit("10101100111"), bit("10110001111"), bit("11100101011"), bit("11001010001"), bit("11100111001"),
                                            bit("0"), bit("0")}
                                       };

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_init_textEdited(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    bit b;
    bit _b;
    bit bi;

    bit a;
    bit g;

    int what;
    int h;
    int i = 0;

    void find_error();

    void get_g();
    void init(QString arg1);
};
#endif // MAINWINDOW_H
