#ifndef TRAIN_H
#define TRAIN_H

#include <QWidget>
#include <QMessageBox>
#include <QCloseEvent>

#include "train_comp.h"

static std::random_device rd;
static std::uniform_int_distribution<int> dis(1, 99);

namespace Ui { class train; }

class train : public QWidget
{
    Q_OBJECT

public:
    explicit train(QWidget *parent = nullptr);
    ~train();

    void set_name(const QString &n)
    {
        name = n;
        set_rul();
    }

signals:
    void return_to_menu();

private slots:
    void on_return_to_clicked(); // возвращение в главное меню

    void on_stud_c_textChanged(const QString &arg1); // ввод ответа пользователя

    void on_l_back_clicked(); // назад по тренировке
    void on_l_forward_clicked(); // вперед по тренировке

    void on_Super_Easy_clicked(); // супер-легкий уровень сложности
    void on_Easy_clicked(); // легкий уровень сложности
    void on_Normal_clicked(); // средний уровень сложности
    void on_Hard_clicked(); // тяжелый уровень сложности
    void on_Random_clicked(); // случайный уровень сложности

    void on_end_test_clicked(); // завершить тестирование

private:
    Ui::train *ui;

    int i = 0;
    int n = 10; // количество заданий

    QString rul = "files/rules.txt";

    QString *ex; // все задания
    QString *ans; // все ответы

    QString name; // имя тестируемого
    QString level; // уровень сложности

    void set_rul();
    void start_test(); // начать тестирование
};

#endif // TRAIN_H
