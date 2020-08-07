#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::managerFinished(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QString answer = reply->readAll();

    qDebug() << answer;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager();
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(managerFinished(QNetworkReply*)));
}

void MainWindow::on_pushButton_clicked()
{
    //https://stackoverflow.com/a/46947157
    manager->get(*request);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}
