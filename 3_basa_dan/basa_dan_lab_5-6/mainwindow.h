#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tabWidget_currentChanged(int index);

    void insert(QSqlQuery &qdb, const QVector<QVector<QString>> &qvs, const QVector<QString> &data, const int &j);
    void on_input_clicked();

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;
    QSqlTableModel *tdb;

    QVector<QVector<QString>> qvs;
};
#endif // MAINWINDOW_H
