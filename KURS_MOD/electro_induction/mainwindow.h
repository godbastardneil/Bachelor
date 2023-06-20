#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dialog.h"
#include "show_text.h"

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
    void on_Faradei_clicked();
    void on_Exercise_clicked(); // открытие задач
    void on_Test_clicked();
    void on_Change_clicked(); // открытие поменять пользователя

    void return_to_menu(); // возврат в меню

    void on_prog_info_triggered();
    void on_Statistica_triggered();

private:
    Ui::MainWindow *ui;

    QString name; // имя пользователя

    dialog *user; // виждет входа

    uint8_t c;

    show_text *only_text;

    MainWindow(const MainWindow &)  = delete;
    MainWindow(const MainWindow &&) = delete;
    MainWindow& operator=(const MainWindow &)  = delete;
    MainWindow& operator=(const MainWindow &&) = delete;
};
#endif // MAINWINDOW_H
