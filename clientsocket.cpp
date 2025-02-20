#include "clientsocket.h"
#include "databasemagr.h"

#include <QFile>
#include <QDebug>
#include <QHostAddress>
#include <QDataStream>
#include <QApplication>

#define SERVER_IP "192.168.2.199"
#define SERVER_PORT 60100

ClientSocket::ClientSocket(QObject *parent) :
    QObject(parent)
{
    m_nId = -1;

    m_tcpSocket = new QTcpSocket(this);

    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(SltReadyRead()));
    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(SltConnected()));
    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(SltDisconnected()));
}

ClientSocket::~ClientSocket()
{
}

/**
 * @brief ClientSocket::GetUserId
 * 获取当前用户id
 * @return
 */
int ClientSocket::GetUserId() const
{
    return  m_nId;
}

/**
 * @brief ClientSocket::SetUserId
 * 设置当前socket的用户id
 * @param id
 */
void ClientSocket::SetUserId(const int &id)
{
    m_nId = id;
}

void ClientSocket::CheckConnected()
{
    if (m_tcpSocket->state() != QTcpSocket::ConnectedState)
    {
        m_tcpSocket->connectToHost(QString(SERVER_IP), SERVER_PORT);
    }
}

/**
 * @brief ClientSocket::ColseConnected
 * 主动断开连接
 */
void ClientSocket::ColseConnected()
{
    if (m_tcpSocket->isOpen()) {
        m_tcpSocket->abort();
    }
}

/**
 * @brief ClientSocket::ConnectToHost
 * 链接服务器接口
 * @param host
 * @param port
 */
void ClientSocket::ConnectToHost(const QString &host, const int &port)
{
    if (m_tcpSocket->isOpen()) m_tcpSocket->abort();
    m_tcpSocket->connectToHost(host, port);
}

/**
 * @brief ClientSocket::ConnectToHost
 * 链接服务器接口
 * @param host
 * @param port
 */
void ClientSocket::ConnectToHost(const QHostAddress &host, const int &port)
{
    if (m_tcpSocket->isOpen()) {
        m_tcpSocket->abort();
    }
    m_tcpSocket->connectToHost(host, port);
}

/**
 * @brief ClientSocket::SltSendMessage
 * tcp socket消息管理
 * @param type
 * @param dataVal
 */
void ClientSocket::SltSendMessage(const quint8 &type, const QJsonValue &dataVal)
{
    // 连接服务器
    if (!m_tcpSocket->isOpen()) {
        m_tcpSocket->connectToHost(QString(SERVER_IP), SERVER_PORT);
        m_tcpSocket->waitForConnected(1000);
    }
    // 超时1s后还是连接不上，直接返回
    if (!m_tcpSocket->isOpen()) {
        return;
    }

    // 构建 Json 对象
    QJsonObject json;
    json.insert("type", type);
    json.insert("from", m_nId);
    json.insert("data", dataVal);

    // 构建 Json 文档
    QJsonDocument document;
    document.setObject(json);
    qDebug() << "m_tcpSocket->write:" << document.toJson(QJsonDocument::Compact);
    m_tcpSocket->write(document.toJson(QJsonDocument::Compact));
}

/**
 * @brief ClientSocket::SltDisconnected
 */
void ClientSocket::SltDisconnected()
{
    qDebug() << "has disconnecetd";
    m_tcpSocket->abort();
}

/**
 * @brief ClientSocket::SltConnected
 */
void ClientSocket::SltConnected()
{
    qDebug() << "has connecetd";
}


/**
 * @brief ClientSocket::SltReadyRead
 * 服务器消息处理
 */
void ClientSocket::SltReadyRead()
{

}
