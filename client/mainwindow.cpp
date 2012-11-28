#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listView->hide();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_clicked()
{
    ui->login->hide();
    ServerSocket = new Tcp(this);
    QHostAddress add(GAMESERVERIP);
    ServerSocket->ConnectTo(&add,GAMESERVERPORT);
    if(ServerSocket->isOpen())
    {
        if(!ServerSocket->login(ui->name->text(),ui->passwd->text()))
        {
            ui->info->setText("error");
            delete ServerSocket;
            ui->login->show();
            return ;
        }
        ui->widget->hide();
        ui->listView->show();
    }

}

void MainWindow::newUser(struct User *user)
{

}
