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

void MainWindow::on_btnVerContra_clicked()
{
    if(ui->txtContra->echoMode()==QLineEdit::Password){
        ui->txtContra->setEchoMode(QLineEdit::Normal);
        ui->btnVerContra->setText("👁");
    }else{
        ui->txtContra->setEchoMode(QLineEdit::Password);
        ui->btnVerContra->setText("🙈");
    }
}

