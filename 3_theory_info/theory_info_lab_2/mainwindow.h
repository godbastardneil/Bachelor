#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include <algorithm>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_start_clicked();

private:
    Ui::MainWindow *ui;

    std::vector<double> px;
    std::vector<double> p_yx;

    QString qs;
    QStringList qsl1;
    QStringList qsl2;

    double Hx = 0;
    double Hyx = 0;
    double H_xy = 0;
    double Dp = 0;
    double Ds = 0;

    void first_table();
    void second_table();
};
#endif // MAINWINDOW_H
