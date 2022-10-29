#ifndef THEORY_H
#define THEORY_H

#include <QWidget>
#include <QMessageBox>
#include <QFile>

namespace Ui { class theory; }

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
    void on_return_to_clicked();

    void on_teo_anchorClicked(const QUrl &arg1);

private:
    Ui::theory *ui;

    QString teo = "files/teo.html";
    QString slovo = "files/slovo.html";

};

#endif // THEORY_H
