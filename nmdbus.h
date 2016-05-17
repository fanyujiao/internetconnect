/*************************************************
Copyright:Wuxi National Fundamental Software of China Co., Ltd
Author:yujiao.fan
Date:2016-05-11
Description: NetworkManagerx相关DBus调用
**************************************************/
#ifndef NMDBUS_H
#define NMDBUS_H
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusConnection>
#include <QDBusInterface>
#include <QDBusObjectPath>
#include <QDBusReply>
#include <QDBusVariant>
#include <QDBusMetaType>
#include <QDBusArgument>
#include <QDebug>
#include <QPrinter>



typedef  QList<u_int32_t> ARRARY_UINT32 ;
typedef QMap<QString, QVariantMap> MY_QMAP;

Q_DECLARE_METATYPE(ARRARY_UINT32)
Q_DECLARE_METATYPE(MY_QMAP)

class NMDBus
{
public:
    NMDBus();
    u_int32_t getNameServers();
    QDBusObjectPath getDBusObjPath(QString activeConnectionPath);
    MY_QMAP getSettings(QDBusObjectPath qDBusObjPath);
    QVariant getActiveConnections();

private:
    QString nmip4configgetpath ;

};

#endif // NMDBUS_H
