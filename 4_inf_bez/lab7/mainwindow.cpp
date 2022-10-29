#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);

    ui->orig_Edit->setFont(font);
    ui->crypt_Edit->setFont(font);
    ui->decrypt_Edit->setFont(font);
}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::on_crypt_Button_clicked()
{
    QString alf1 = alfa, alf2 = alfa;
    std::random_shuffle(alf1.begin(), alf1.end());
    std::random_shuffle(alf2.begin(), alf2.end());

    qDebug() << alf1;
    qDebug() << alf2;

    QString str = ui->orig_Edit->text().toLower().replace(" ", "");
    ui->orig_Edit->setText(str);
    if (str.size()%2 == 0)
    {
        ui->crypt_Edit->setText(crypt(str, alf1, alf2));

        str = ui->crypt_Edit->text();
        ui->decrypt_Edit->setText(crypt(str, alf1, alf2));
    }
}

QString MainWindow::crypt(const QString &str, const QString &alf1, const QString &alf2)
{
    QString out(str.size(), 'a');

    for (int i=0; i<str.size(); i+=2)
    {
        int J1 = alf1.indexOf(str[i]);
        int J2 = alf2.indexOf(str[i+1]);

        int i1 = (J1/step)*step;
        int i2 = (J2/step)*step;
        int j1 = (J1%step);
        int j2 = (J2%step);

        if (i1 == i2 || j1 == j2)
        {
            out[i] = alf1[J2];
            out[i+1] = alf2[J1];
        } else
        {
            out[i] = alf1[i1+j2];
            out[i+1] = alf2[i2+j1];
        }
    }

    return (out);
}

// ШИФРРЕШЕТКАЯВЛЯЕТСЯЧАСТНЫМСЛУЧАЕМШИФРАМАРШРУТНОЙПЕРЕСТАНОВКИ
