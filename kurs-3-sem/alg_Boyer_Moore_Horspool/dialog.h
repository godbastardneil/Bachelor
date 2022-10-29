#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui { class dialog; }

class dialog : public QDialog
{
    Q_OBJECT

public:
    explicit dialog(QWidget *parent = nullptr);
    ~dialog();

    QString get_name() { return name; }
    QString get_password() { return password; }
    bool isCancel() { return c; }

private slots:
    void on_name_textChanged(const QString &arg1) { name = arg1; }
    void on_password_textChanged(const QString &arg1) { password = arg1; }
    void on_buttonBox_accepted() { c = false; close(); }
    void on_buttonBox_rejected() { c = true; close(); }

private:
    Ui::dialog *ui;

    QString name; // введеное имя
    QString password; // введеный пароль
    bool c;

    dialog(const dialog &)  = delete;
    dialog(const dialog &&) = delete;
    dialog& operator=(const dialog &)  = delete;
    dialog& operator=(const dialog &&) = delete;
};

#endif // DIALOG_H
