#ifndef THEORY_H
#define THEORY_H

#include <QWidget>
#include <QMessageBox>
#include <QFile>

#include "reader.h"

namespace Ui { class theory; }

class theory : public QWidget
{
    Q_OBJECT

public:
    explicit theory(QWidget *parent = nullptr);
    ~theory();

    void read_theory(); // чтение и вывод теории

signals:
    void return_to_menu();

private slots:
    void on_teo_anchorClicked(const QUrl &arg1); // нажатие на ссылку

    void on_return_to_clicked(); // вернуться в лавное меню

private:
    Ui::theory *ui;

    QString teo = "files/teo.txt";
    QString slovo = "files/slovo.txt";

};

#endif // THEORY_H
