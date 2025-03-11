#ifndef DATABASEMAGR_H
#define DATABASEMAGR_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMutex>
#include <QJsonArray>
#include "iteminfo.h"


/// 客户端数据库管理类
class DataBaseMagr : public QObject
{
    Q_OBJECT
private:
    explicit DataBaseMagr(QObject *parent = 0);
    ~DataBaseMagr();

public:
    bool OpenUserDb(const QString &dataName);
    bool OpenMessageDb(const QString &dataName);

    void AddHistoryMsg(const int &userId, ItemInfo *itemInfo);

    // 单实例运行
    static DataBaseMagr *Instance()
    {
        static QMutex mutex;
        if (NULL == self) {
            QMutexLocker locker(&mutex);

            if (!self) {
                self = new DataBaseMagr();
            }
        }

        return self;
    }


    bool isMyFriend(const int &userId, const QString &name);
    QJsonArray GetMyFriend(const int &userId);
    void AddFriend(const int &friendId, const int &userId, const QString &name);

    // 获取历史聊天记录
    QVector<ItemInfo *> QueryHistory(const int &id, const int &count = 0);


    // 添加群组
    void AddGroup(const int &id, const int &userId, const QString &name);

    QJsonArray GetMyGroup(const int &userId) const;

signals:

public slots:

private:
    static DataBaseMagr *self;

    // 数据库管理
    QSqlDatabase userdb;
    QSqlDatabase msgdb;
};

#endif // DATABASEMAGR_H
