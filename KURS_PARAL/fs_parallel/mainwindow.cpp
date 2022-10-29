#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->demo_show, &demo::return_to_menu, this, &MainWindow::return_to_menu);
    connect(ui->theory_show, &theory::return_to_menu, this, &MainWindow::return_to_menu);
    connect(ui->info_show, &show_text::return_to_menu, this, &MainWindow::return_to_menu);
}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::on_Theory_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->theory_show);
}
void MainWindow::on_Demo_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->demo_show);
}

void MainWindow::on_Info_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->info_show);
}

void MainWindow::return_to_menu()
{
    ui->stackedWidget->setCurrentWidget(ui->main_menu);
}

