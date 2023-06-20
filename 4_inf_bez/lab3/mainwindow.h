#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum rule : uint8_t
{
    no, user = 0,
    read = 1,
    change, admin = 2
};

using rules  = QVector<rule>;
using rights = QVector<rules>;
using users  = QVector<QString>;

struct object
{
    QString name;
    QString content;
};
using objects = QVector<object>;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_object_list_currentRowChanged(int currentRow);

    void on_user_box_currentIndexChanged(int index);

    void on_in_object_textChanged();

    void on_admin_button_clicked();


    void on_object_edit_but_accepted();
    void on_object_edit_but_rejected();

    void on_user_edit_but_accepted();
    void on_user_edit_but_rejected();

    void on_object_box_currentIndexChanged(int index);
    void on_user_box_2_currentIndexChanged(int index);

    void on_rights_box_currentIndexChanged(int index);


    void on_back_button_clicked();

private:
    Ui::MainWindow *ui;

    users uss;      // Массив пользователей
    objects objs;   // Массив значений объектов типа String
    rights P;       // Матрица прав доступа

    void view_text(const int &i, const int &j);

    void create_user(const QString &name, const rule &role);
    void create_object(const QString &name, const QString &content);

    void delete_user(const int &i);
    void delete_object(const int &j);

    bool search_obj(const QString &name);
};
#endif // MAINWINDOW_H
