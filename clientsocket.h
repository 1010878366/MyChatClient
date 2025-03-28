#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QFile>

/// socket通信类
class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = 0);
    ~ClientSocket();

    // 获取当前用户的ID
    int GetUserId() const;
    void SetUserId(const int &id);

    void CheckConnected();
    void CloseConnected();

    // 连接服务器
    void ConnectToHost(const QString &host, const int &port);
    void ConnectToHost(const QHostAddress &host, const int &port);
signals:
    void signalMessage(const quint8 &type, const QJsonValue &dataVal);
    void signalStatus(const quint8 &state);
public slots:
    // socket消息发送封装
    void SltSendMessage(const quint8 &type, const QJsonValue &dataVal);
private:
    // tcpsocket
    QTcpSocket *m_tcpSocket; //维持id=2的用户的连接
    int m_nId; //用户id
private slots:
    // 与服务器断开链接
    void SltDisconnected();
    // 链接上服务器
    void SltConnected();
    // tcp消息处理
    void SltReadyRead();

private:
    void ParseLogin(const QJsonValue &dataVal);

private:
};









//////////////////////////////////////////////////////////////////////
/// \brief The ClientFileSocket class
/// 文件传输socket
class ClientFileSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientFileSocket(QObject *parent = 0);
    ~ClientFileSocket();

    bool isConneciton();

    // 发送文件大小等信息
    void StartTransferFile(QString fileReadName);

    // 连接到服务器
    void ConnectToServer(const QString &ip, const int &port, const int &usrId);
    // 断开服务器
    void CloseConnection();

    // 文件传输完成
    void FileTransFinished();

    // 设置当前socket的id
    void SetUserId(const int &id);
signals:
    void signalSendFinished();
    void signamFileRecvOk(const quint8 &type, const QString &filePath);
    void signalUpdateProgress(quint64 currSize, quint64 total);
    void signalConnectd();
private:
    quint64         loadSize;   //每次发送数据的大小

    /************* Receive file *******************/
    quint64         bytesReceived;  //已收到数据的大小
    quint64         fileNameSize;  //文件名的大小信息
    QString         fileReadName;   //存放文件名
    QByteArray      inBlock;   //数据缓冲区
    quint64         ullRecvTotalBytes;  //数据总大小
    QFile           *fileToRecv;  //要发送的文件

    /************* Send file **********************/
    quint16         blockSize;  //存放接收到的信息大小
    QFile           *fileToSend;  //要发送的文件
    quint64         ullSendTotalBytes;  //数据总大小
    quint64         bytesWritten;  //已经发送数据大小
    quint64         bytesToWrite;   //剩余数据大小
    QByteArray      outBlock;  //数据缓冲区，即存放每次要发送的数据

    // 用户目录
    QString         m_strFilePath;

    // 通信类
    QTcpSocket      *m_tcpSocket;

    bool            m_bBusy;
    int             m_nWinId;
    quint8          m_nType;
private:
    // socket 初始化
    void InitSocket();
public slots:

private slots:
    // 显示错误
    void displayError(QAbstractSocket::SocketError);
    // 发送文件数据，更新进度条
    void SltUpdateClientProgress(qint64);

    // 文件接收
    void SltReadyRead();
    void SltConnected();
    void SltDisConnected();
};

#endif //TCPCLIENT_H
