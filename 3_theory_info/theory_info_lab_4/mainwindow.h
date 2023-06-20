#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>

#include <math.h>
#include <random>

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
    void on_spinBox_valueChanged(int arg1);

    void on_init_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;

    std::vector<QString> A_gh;
    std::vector<QString> E_h;
    std::vector<QString> E_g;

    QString qs;
    QString b;
    QString _b;
    QString _s;
    int er;

    int r;
    int n;
    int k;

    void H_table();
    void G_table();
    void find_error();
    void init(const QString &arg1);
};
#endif // MAINWINDOW_H
