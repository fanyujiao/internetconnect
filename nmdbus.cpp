#include "nmdbus.h"

NMDBus::NMDBus()
{
}


/*************************************************
Function:       getActiveConnections
Description:   获取连接ActiveConnections
Parameter:
Return:      ActiveConnections
*************************************************/
QVariant NMDBus::getActiveConnections()
{
    QVariant qvariant;
    QDBusInterface iface( "org.freedesktop.NetworkManager", "/org/freedesktop/NetworkManager",
                          "org.freedesktop.DBus.Properties", QDBusConnection::systemBus());
    if (!iface.isValid())
    {
        qDebug() << qPrintable(QDBusConnection::systemBus().lastError().message());
        return qvariant;
    }
    QString interface = "org.freedesktop.NetworkManager";
    QString propname = "ActiveConnections";
    QDBusReply<QVariant> reply = iface.call("Get",interface,propname);
    if(!reply.isValid())
    {
        //  qDebug() << "!reply.isValid";
        return qvariant;
    }
    else
    {
        qvariant = reply.value();
    }
    return qvariant;
}



/*************************************************
Function:       getNameServers
Description:   通过DBbus获取DNS
Parameter:
Return:      u_int32_t格式DNS
*************************************************/
u_int32_t NMDBus::getNameServers()
{
    // qDebug() << "in";
    u_int32_t retVal = 0;
    QDBusInterface iface( "org.freedesktop.NetworkManager", "/org/freedesktop/NetworkManager/IP4Config/0",
                          "org.freedesktop.DBus.Properties", QDBusConnection::systemBus());
    if (!iface.isValid())
    {
        return retVal;
        qDebug() << qPrintable(QDBusConnection::systemBus().lastError().message());
    }
    QString interface = "org.freedesktop.NetworkManager.IP4Config";
    QString propname = "Nameservers";
    QDBusReply<QDBusVariant> reply = iface.call("Get",interface,propname);
    if(!reply.isValid())
    {
        //  qDebug() << "!reply.isValid";
        return retVal;
    }
    else
    {
        //           QListIterator<u_int32_t> i(reply.value());
        //            for (;i.hasNext();)
        //            {
        //              retVal = i.next();
        //if(reply)
        //QList<int> tmp = qvariant_cast<ARRARY_UINT32>(reply.value().variant());
        //qDebug() << tmp.length();
        ARRARY_UINT32 tmp;
        reply.value().variant().value<QDBusArgument>() >> tmp;
        //  qDebug() << tmp.at(0);
        retVal = tmp.at(0);
        // qDebug() << reply.value().variant().type();
        // qDebug() << "reply.isValid ok!" << retVal;
        //            }
    }
    // qDebug() << "11111" << retVal;

    //    QDBusMessage m = QDBusMessage::createMethodCall("org.freedesktop.NetworkManager",
    //                                                    "/org/freedesktop/NetworkManager/IP4Config/1",
    //                                                    "org.freedesktop.DBus.Properties",
    //                                                    "Get");
    //      //      给方法传递参数
    //            m << "org.freedesktop.NetworkManager.IP4Config" << "NameServers";
    //    //        调用方法
    //    QDBusMessage response = QDBusConnection::systemBus().call(m);
    //    //       判断方法的返回值
    //    if (response.type() == QDBusMessage::ReplyMessage) {
    //        // QDBusMessage的arguments不仅可以用来存储发送的参数，也用来存储返回值;
    //        // 这里取得checkIn的返回值
    //        retVal = response.arguments().takeFirst().toUInt();
    //        qDebug() << retVal;
    //    }
    //    else
    //    {
    //        qDebug( "Check In fail!/n");
    //    }

    return retVal;
}


/*************************************************
Function:       getDBusObjPath
Description:   通过DBbus获取ObjPath
Parameter:
Return:      QDBusObjectPath
*************************************************/
QDBusObjectPath NMDBus::getDBusObjPath(QString activeConnectionPath)
{
    QDBusObjectPath qDBusObjPath;
    QDBusInterface iface( "org.freedesktop.NetworkManager", activeConnectionPath,
                          "org.freedesktop.DBus.Properties", QDBusConnection::systemBus());
    if (!iface.isValid())
    {
        // qDebug() << "!iface.isValid";
        qDebug() << qPrintable(QDBusConnection::systemBus().lastError().message());
        return qDBusObjPath;
    }
    else
    {
        QString interface = "org.freedesktop.NetworkManager.Connection.Active";
        QString propname = "Connection";
        QDBusReply<QDBusVariant> reply = iface.call("Get",interface, propname);
        if(!reply.isValid())
        {
         //   qDebug() << "!reply.isValid";
            return qDBusObjPath;
        }
        else
        {
            qDBusObjPath = qvariant_cast<QDBusObjectPath>(reply.value().variant());
         //   qDebug() << "QDbusObjPath : " << qDBusObjPath.path();
        }
    }
    return qDBusObjPath;
}


/*************************************************
Function:       getSettings
Description:   通过DBbus获取配置信息
Parameter:
Return:      MY_QMAP
*************************************************/
MY_QMAP NMDBus::getSettings(QDBusObjectPath qDBusObjPath)
{
    qDBusRegisterMetaType<MY_QMAP>();
    MY_QMAP tmpMap;
    QDBusInterface qDBusInterface( "org.freedesktop.NetworkManager", qDBusObjPath.path(),
                                   "org.freedesktop.NetworkManager.Settings.Connection", QDBusConnection::systemBus());
    if (!qDBusInterface.isValid())
    {
        // qDebug() << qPrintable(QDBusConnection::systemBus().lastError().message());
        return tmpMap;
    }
    QDBusReply<MY_QMAP> qDbusReply = qDBusInterface.call("GetSettings");
    if(!qDbusReply.isValid())
    {
        //  qDebug() << "!reply.isValid";
        return tmpMap;
    }
    else
    {
        //qDebug() << qDbusReply.value().count();
        tmpMap = qDbusReply.value();
    }
    //MY_QMAP::Iterator it;
    //for(it = tmpMap.begin(); it != tmpMap.end(); ++it)
    //{
    //    qDebug() << "#############" << it.key();
    //}
    return tmpMap;
}
