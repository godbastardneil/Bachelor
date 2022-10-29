#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void to_admin(); // вход в админа

private slots:
    void on_Theory_clicked();
    void on_Demo_clicked();
    void on_Info_clicked();

    void return_to_menu(); // возврат в меню

private:
    Ui::MainWindow *ui;

    MainWindow(const MainWindow &)  = delete;
    MainWindow(const MainWindow &&) = delete;
    MainWindow& operator=(const MainWindow &)  = delete;
    MainWindow& operator=(const MainWindow &&) = delete;
};
#endif // MAINWINDOW_H
