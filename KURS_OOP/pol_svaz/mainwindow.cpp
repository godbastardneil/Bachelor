#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    to_admin();
    if (c == 3) { exit(0); }

    only_text = new show_text();

    connect(ui->demo_show, &demo::return_to_menu, this, &MainWindow::return_to_menu);
    connect(ui->theory_show, &theory::return_to_menu, this, &MainWindow::return_to_menu);
    connect(ui->training_show, &train::return_to_menu, this, &MainWindow::return_to_menu);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_prog_info_triggered()
{
    only_text->setWindowTitle("Информация");
    only_text->write_text("files/begin.txt");
    only_text->show();
}
void MainWindow::on_Statistica_triggered()
{
    only_text->setWindowTitle("Статистика");
    only_text->write_stat("files/stat.txt", name.toStdString());
    only_text->show();
}


void MainWindow::on_Theory_clicked()
{
    ui->theory_show->read_theory();
    ui->stackedWidget->setCurrentWidget(ui->theory_show);
}
void MainWindow::on_Demo_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->demo_show);
}
void MainWindow::on_Train_clicked()
{
    ui->training_show->set_name(name);
    ui->stackedWidget->setCurrentWidget(ui->training_show);
}
void MainWindow::on_Change_clicked() { to_admin(); }


void MainWindow::return_to_menu()
{
    ui->stackedWidget->setCurrentWidget(ui->main_menu);
}


void MainWindow::to_admin()
{
    user = new dialog();

    do {
        user->exec();
        c = user->isCancel();
    } while (c == 0);

    if (c == 1)
    {
        ui->stackedWidget->setCurrentWidget(ui->main_menu);
        name = user->get_name();
    } else if (c == 2)
    {
        ui->stackedWidget->setCurrentWidget(ui->admin_show);
        delete user;
    }
}
