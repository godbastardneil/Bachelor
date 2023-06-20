#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer> // таймер


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    double T[6]; // части стержня
    int Time; // время
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_doubleSpinBox_0_valueChanged(double arg1); // ввод температуры левого конца стержня
    void on_doubleSpinBox_5_valueChanged(double arg1); // ввод температуры правого конца стержня
    void on_unit_tem_valueChanged(double arg1); // ввод температуры между концами стержня
    void on_time_valueChanged(int arg1); // ввод температуры

    void start(); // сам процесс
    void on_Ok_clicked(); // нажатие кнопки начала процесса

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
