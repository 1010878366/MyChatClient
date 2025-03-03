#include "mydevice.h"

MyDevice::MyDevice(QByteArray dataPcm)
    :m_dataPcm(dataPcm)
{
    //打开
    this->open(QIODevice::ReadOnly);

    m_writeLen = 0;
}

MyDevice::~MyDevice()
{
    this->close();
}

qint64 MyDevice::readData(char *data, qint64 maxSize)
{
    //读取数据
    if(m_writeLen > m_dataPcm.size())
    {
        return 0;
    }
    //计算未播放数据长度
    int len = (m_writeLen + maxSize) > m_dataPcm.size() ? (m_dataPcm.size() - m_writeLen) : maxSize;

    memcpy(data,m_dataPcm.data()+m_writeLen,len);   //把要播放的pcm数据存入声卡缓冲区

    m_writeLen += len;
    return len;

}

qint64 MyDevice::writeData(const char *data, qint64 maxSize)
{

}
