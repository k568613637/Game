#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QDataStream>
#include <QMap>
#include "tcp.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_login_clicked();
    void newUser(struct User *);

private:
    Ui::MainWindow *ui;
    Tcp *ServerSocket;
    QMap<QString, struct User *> map;
};

#endif // MAINWINDOW_H
