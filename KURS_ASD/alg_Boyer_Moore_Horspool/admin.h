#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>

#include "reader.h"

namespace Ui { class admin; }

class admin : public QWidget
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();
    void show_text();
private slots:
    void on_Main_clicked();
    void on_Theory_clicked();
    void on_Test_clicked();
    void on_Statistic_clicked();
    void on_Do_clicked();

    void on_Slovo_clicked();

private:
    Ui::admin *ui;
    QString fname;
    reader writer;

    admin(const admin &)  = delete;
    admin(const admin &&) = delete;
    admin& operator=(const admin &)  = delete;
    admin& operator=(const admin &&) = delete;
};

#endif // ADMIN_H
