#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->hide();


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
    connect(ServerSocket,SIGNAL(newUser(User*)),this,SLOT(newUser(User*)));
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
        ui->listWidget->show();
    }

}

void MainWindow::newUser(struct User *user)
{
    map.insert(user->name,user);
    ui->listWidget->addItem(user->name);
}
void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{





}
