#ifndef THEORY_H
#define THEORY_H

#include <QWidget>
#include <QMessageBox>
#include <QFile>

#include "reader.h"

namespace Ui {
class theory;
}

class theory : public QWidget
{
    Q_OBJECT

public:
    explicit theory(QWidget *parent = nullptr);
    ~theory();

    void read_theory();

signals:
    void return_to_menu();

private slots:
    void on_teo_anchorClicked(const QUrl &arg1);

    void on_return_to_clicked();

private:
    Ui::theory *ui;

    QString teo = "files/teo.txt";
    QString slovo = "files/slovo.txt";

};

#endif // THEORY_H
