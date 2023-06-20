#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dialog.h"
#include "show_text.h"
#include "theory.h"
#include "algorithm.h"
#include "test.h"
#include "admin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void new_con();
    void to_admin();

private slots:
    void on_Main_clicked();
    void on_Algorithm_clicked();
    void on_Theory_clicked();
    void on_Test_clicked();
    void on_Statistic_clicked();

private:
    Ui::MainWindow *ui;

    dialog *user;
    QString name;

    const QString admin_n = "admin";
    const QString admin_p = "password";

    show_text *main_text; // виджет для вывода просто текста
    theory *teo;
    Algorithm *algorithm; // виджет для показа демонстрации
    test *offset; // виджет тестирования
    admin *adm; // виджет режима администратора, открывается в другом окне


    MainWindow(const MainWindow &)  = delete;
    MainWindow(const MainWindow &&) = delete;
    MainWindow& operator=(const MainWindow &)  = delete;
    MainWindow& operator=(const MainWindow &&) = delete;
};
#endif // MAINWINDOW_H
