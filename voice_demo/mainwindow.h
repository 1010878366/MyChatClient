#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QAudioFormat>
#include<QAudioDeviceInfo>  //获取设备声卡信息
#include<QAudioOutput>
#include<QFile>
#include<QDebug>
#include<QMessageBox>
#include"media/mydevice/mydevice.h"
#include"media/fmodmedia/fmodmedia.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    QAudioOutput *m_out;
    MyDevice *m_dev;

};
#endif // MAINWINDOW_H
