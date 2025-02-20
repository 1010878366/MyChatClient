#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);

    //this->setStyleSheet("QWidget { background-image: url(:/resouse/background/logo.png); background-repeat: no - repeat; background - position: center; }");
}

MainWindow::~MainWindow()
{
    delete ui;
}

