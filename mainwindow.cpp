<<<<<<< HEAD
#include "mainwindow.h"
=======
﻿#include "mainwindow.h"
>>>>>>> ef25af80c77988ad285a418bbaf9f51f75c71c52
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
<<<<<<< HEAD
=======

    this->setWindowFlags(Qt::FramelessWindowHint);

    //this->setStyleSheet("QWidget { background-image: url(:/resouse/background/logo.png); background-repeat: no - repeat; background - position: center; }");
>>>>>>> ef25af80c77988ad285a418bbaf9f51f75c71c52
}

MainWindow::~MainWindow()
{
    delete ui;
}

