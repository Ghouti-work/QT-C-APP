#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int firstnum, secondnum, result;

void MainWindow::on_btnadd_clicked()
{
    firstnum = ui->txtfirstnum->text().toInt();
    secondnum = ui->txtsecondnum->text().toInt();
    result = firstnum + secondnum;
    ui->txtresult->setText(QString::number(result));
}


void MainWindow::on_btnsub_clicked()
{
    firstnum = ui->txtfirstnum->text().toInt();
    secondnum = ui->txtsecondnum->text().toInt();
    result = firstnum - secondnum;
    ui->txtresult->setText(QString::number(result));
}


void MainWindow::on_btnmul_clicked()
{
    firstnum = ui->txtfirstnum->text().toInt();
    secondnum = ui->txtsecondnum->text().toInt();
    result = firstnum * secondnum;
    ui->txtresult->setText(QString::number(result));
}


void MainWindow::on_btndiv_clicked()
{
    firstnum = ui->txtfirstnum->text().toInt();
    secondnum = ui->txtsecondnum->text().toInt();
    result = firstnum / secondnum;
    ui->txtresult->setText(QString::number(result));
}

