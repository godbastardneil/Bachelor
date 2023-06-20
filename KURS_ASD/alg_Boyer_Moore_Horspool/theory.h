#ifndef THEORY_H
#define THEORY_H

#include <QWidget>
#include <QMessageBox>
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
    void write_teo();

private slots:
    void on_teo_anchorClicked(const QUrl &arg1);

private:
    Ui::theory *ui;
    reader writer;

    QString teo = "files/teo.txt";
    QString slovo = "files/slovo.txt";

};

#endif // THEORY_H
