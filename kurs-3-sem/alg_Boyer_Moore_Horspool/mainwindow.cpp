#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    to_admin();
    if (user->isCancel()) { exit(0); }
    ui->setupUi(this);

    main_text = new show_text(ui->MW);
    main_text->resize(ui->MW->size());

    teo = new theory(ui->MW);
    teo->resize(ui->MW->size());

    offset = new test(ui->MW);
    offset->resize(ui->MW->size());

    algorithm = new Algorithm(ui->MW);
    algorithm->resize(ui->MW->size());

    on_Main_clicked();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::new_con()
{
    main_text->hide();
    teo->hide();
    offset->hide();
    algorithm->hide();

}

void MainWindow::on_Main_clicked()
{
    new_con();
    main_text->write_text("files/begin.txt");
    main_text->show();
}

void MainWindow::on_Algorithm_clicked()
{
    new_con();
    algorithm->show();
}

void MainWindow::on_Theory_clicked()
{
    new_con();
    teo->write_teo();
    teo->show();
}

void MainWindow::on_Test_clicked()
{
    new_con();
    offset->write_test(name);
    offset->show();
}

void MainWindow::on_Statistic_clicked()
{
    new_con();
    main_text->write_stat("files/stat.txt", name.toStdString());
    main_text->show();
}

void MainWindow::to_admin()
{
    user = new dialog();
    while ((!user->isCancel()) && ((user->get_name() == "") || ((user->get_name() == "admin") && (user->get_password() != "password"))))
    {
        user->exec();
    }
    if ((user->get_name() == admin_n) && (user->get_password() == admin_p))
    {
        adm = new admin();
        adm->show();
    }
    name = user->get_name();
    delete user;
}
