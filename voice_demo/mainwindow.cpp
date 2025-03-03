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

    delete m_dev;
    delete m_out;
}


void MainWindow::on_pushButton_clicked()
{
    //设置声音三要素
    QAudioFormat format;
    format.setSampleRate(44100);    //设置采样率
    format.setChannelCount(1);      //设置通道数
    format.setSampleSize(16);       //设置样本数据
    format.setCodec("audio/pcm");   //播出格式为pcm格式
    format.setByteOrder(QAudioFormat::LittleEndian);    //默认小端格式
    format.setSampleType(QAudioFormat::UnSignedInt);    //无符号整数型

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice()); //选择默认输出设备
    if(!info.isFormatSupported(format))
    {
        qDebug()<<"输出设备不支持该格式，不能播放音频";
        return;
    }

    //创建声音输出对象
    m_out = new QAudioOutput(format,this);

    //把文件pcm数据放到内存数组里
    QFile file("G:\\QtStudy\\project\\voice_demo\\sound\\system.wav");     //音频文件位置
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"文件以只读方式打开失败！";
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    //创建自定义的IO设备
    m_dev = new MyDevice(data);
    m_out->start(m_dev);

}

void MainWindow::on_pushButton_2_clicked()
{
    FmodMedia::getInstance()->playWav("G:\\QtStudy\\project\\voice_demo\\sound\\system.wav");     //音频文件位置
}
