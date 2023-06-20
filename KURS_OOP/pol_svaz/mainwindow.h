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
    void on_Theory_clicked(); // открыть "теория"
    void on_Train_clicked(); // открыть "тренировка"
    void on_Change_clicked(); // открыть "авторизация"
    void on_Demo_clicked(); // открыть "демонстрация"

    void on_prog_info_triggered(); // открыть "титульник"
    void on_Statistica_triggered(); // открыть "статистика"

    void return_to_menu(); // возврат в меню


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
