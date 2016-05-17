/*************************************************
Copyright:Wuxi National Fundamental Software of China Co., Ltd
Author:yujiao.fan
Date:2016-05-10
Description: 系统网络相关方法
**************************************************/

#ifndef ABOUTNETWORK_H
#define ABOUTNETWORK_H

#include <QtNetwork/QHostInfo>
#include <QtNetwork/QNetworkInterface>
#include <QDebug>
#include <QString>
#include <QProcess>
#include "nmdbus.h"



class AboutNetwork
{
public:
    AboutNetwork();
    void dhcpConnect();
    void staticConnect();
    QString getAdapterName();
    QString getConnectName();
    QString getIP();
    QString getGateway();
    QString getDNS();
    int SetGateWay(const char *szGateWay);

private:
    char* make8Bit(char *p,u_int32_t num);
    char* changeIP(u_int32_t num);
};

#endif // ABOUTNETWORK_H
