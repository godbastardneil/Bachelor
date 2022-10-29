#ifndef EXERCISE_H
#define EXERCISE_H

#include <QWidget>
#include <QMessageBox>

#include "exercise_comp.h"

namespace Ui { class exercise; }

class exercise : public QWidget
{
    Q_OBJECT

public:
    explicit exercise(QWidget *parent = nullptr);
    ~exercise();

    void write_exercise();

signals:
    void return_to_menu();

private slots:
    void on_exersize_activated(int index);
    void on_return_to_clicked(); // вернуться в меню

    void on_check_clicked();

    void on_answer_textChanged(const QString &arg1);

private:
    Ui::exercise *ui;

    uint i = 0; // номер задания

    QString fname_ex = "files/exercise.txt";

    QString ans;
    QVector<task> ex;

    void change_exercise();
};

#endif // EXERCISE_H
