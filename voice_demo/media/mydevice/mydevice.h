#ifndef MYDEVICE_H
#define MYDEVICE_H
#include<QIODevice>


class MyDevice : public QIODevice
{
public:
    MyDevice(QByteArray dataPcm);
    ~MyDevice();

protected:
    //读写数据
    qint64 readData(char *data, qint64 maxSize);
    qint64 writeData(const char *data, qint64 maxSize);


private:
    QByteArray m_dataPcm;   //存放pcm数据
    int m_writeLen;         //记录已经写入多少字节

};

#endif // MYDEVICE_H
