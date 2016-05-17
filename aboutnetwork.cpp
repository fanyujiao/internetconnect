#include "aboutnetwork.h"
#include <arpa/inet.h>
#include <math.h>

AboutNetwork::AboutNetwork()
{
}

/*************************************************
Function:       dhcpConnect
Description:    DHCP连接
Parameter:      无
Return:         无
*************************************************/
void AboutNetwork::dhcpConnect()
{
//    QProcess proc;
//    QStringList arguments;
//    arguments << "connection" << "add" << con-name
//              << "dhcp" << type << ethernet ifname
//              << eno16777736 ;
//    qDebug()<<arguments;
//    proc.start("nmcli", arguments);

//    if (!proc.waitForStarted())            /**等待进程启动**/
//    {
//        qDebug() << "启动失败\n";
//        return NULL;
//    }
//    proc.closeWriteChannel();               /**关闭写通道,因为没有向进程写数据,没用到**/
//    QByteArray procOutput;                  /**用于保存进程的控制台输出**/
//    while (false == proc.waitForFinished()) /**等待进程结束**/
//    {
//        qDebug() << "结束失败\n";
//        return NULL;
//    }
//    procOutput = proc.readAll();            /**读取进程输出到控制台的数据**/
//    // qDebug() << procOutput.data();            /**输出读到的数据**/
//    if (!procOutput.isEmpty())
//    {
//        // procOutput.mid(8) == AboutNetwork.getAdapterName()
//        //     qDebug() << "NULL\n";

//    }

}


/*************************************************
Function:       staticConnect
Description:    手动连接
Parameter:      无
Return:         无
*************************************************/
void AboutNetwork::staticConnect()
{

}


/*************************************************
Function:       getAdapterName
Description:    获取网卡名称
Parameter:      无
Return:         网卡名称
*************************************************/
QString AboutNetwork::getAdapterName()
{
    QString adaptername = "";
    QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();
    foreach(QNetworkInterface interfaceItem, interfaceList)
    {
        if(interfaceItem.flags().testFlag(QNetworkInterface::IsUp)
                && interfaceItem.flags().testFlag(QNetworkInterface::IsRunning)
                && interfaceItem.flags().testFlag(QNetworkInterface::CanBroadcast)
                && interfaceItem.flags().testFlag(QNetworkInterface::CanMulticast)
                && !interfaceItem.flags().testFlag(QNetworkInterface::IsLoopBack)
                && interfaceItem.hardwareAddress()!="00:50:56:C0:00:01"
                && interfaceItem.hardwareAddress()!="00:50:56:C0:00:08")
        {
            QList<QNetworkAddressEntry> addressEntryList=interfaceItem.addressEntries();
            foreach(QNetworkAddressEntry addressEntryItem, addressEntryList)
            {
                if(addressEntryItem.ip().protocol()==QAbstractSocket::IPv4Protocol
                        && interfaceItem.name() != "wlan0"
                        && interfaceItem.name() != "wlan1"
                        && interfaceItem.name() != "wlan2"
                        && interfaceItem.name() != "wlan3"
                        && interfaceItem.name() != "wlan4")
                {
                    adaptername = interfaceItem.name();
                }
            }

        }
    }
    return adaptername;
}


/*************************************************
Function:       getConnectName
Description:    获取网络连接名称
Parameter:      无
Return:         网络连接名称
*************************************************/
QString AboutNetwork::getConnectName()
{
//        FILE *fp;                                        /**方法一**/
//        char buf[512];
//        char cmd[128];
//        char connectionname[128];
//        char *tmp;
//        char *name;
//        QString  adaptername = getAdapterName();
//        QByteArray ba = adaptername.toLatin1();
//        name = ba.data();

//      //  extern char *strcat(char *dest,char *src);

//        strcpy(cmd, "nmcli connection status | grep ");
//        strcat(cmd,name);
//       strcat(cmd,"| awk '{FS= "/t"} {print $1}'");
//        fp = popen(cmd, "r");
//        if(NULL == fp)
//        {
//            perror("popen error");
//            return "";
//        }
//        while(fgets(buf, sizeof(buf), fp) != NULL)
//        {
//            tmp =buf;
//            while(*tmp && isspace(*tmp))
//                ++ tmp;
//            if(strncmp(tmp, "名称", strlen("名称")) == 0)
//              //  qDebug()<<"11111111111111";
//                break;
//                int i=0;
//                char *p = tmp;
//                while (*(p++)!=' ')
//                {
//                    *(tmp+i)=*p;
//                    i++;
//                }
//                *p=0;
//        }
//        qDebug()<<QObject::tr(tmp);
//        pclose(fp);

//        return QString(connectionname);

//    QProcess proc;                                    /**方法二**/
//    QStringList arguments;
//    arguments << "connection" << "status" ;
//    qDebug()<<arguments;
//    proc.start("nmcli", arguments);

//    if (!proc.waitForStarted())            /**等待进程启动**/
//    {
//        qDebug() << "启动失败\n";
//        return NULL;
//    }
//    proc.closeWriteChannel();               /**关闭写通道,因为没有向进程写数据,没用到**/
//    QByteArray procOutput;                  /**用于保存进程的控制台输出**/
//    while (false == proc.waitForFinished()) /**等待进程结束**/
//    {
//        qDebug() << "结束失败\n";
//        return NULL;
//    }
//    procOutput = proc.readAll();            /**读取进程输出到控制台的数据**/
//   // qDebug() << procOutput.data();            /**输出读到的数据**/
//    if (!procOutput.isEmpty())
//    {
//       // procOutput.mid(8) == AboutNetwork.getAdapterName()
//   //     qDebug() << "NULL\n";

//    }
QString connectname = "";
NMDBus nmdbus;
QString activeConnectionPath = "";
const int status = -1;
QList<QDBusObjectPath> qDBusObjPathList;
QVariant qvariant = nmdbus.getActiveConnections();
 qvariant.value<QDBusArgument>() >> qDBusObjPathList;
 if (qDBusObjPathList.isEmpty())
 {
     return connectname;
 }
 int count = qDBusObjPathList.count();
for (int i = 0; i < count; ++i)
{
 activeConnectionPath = qDBusObjPathList.at(i).path();
//  qDebug() << activeConnectionPath;
QDBusObjectPath qDBusObjPath = nmdbus.getDBusObjPath(activeConnectionPath);
if (qDBusObjPath.path().isEmpty())
{
    return connectname;
}
MY_QMAP tmpMap = nmdbus.getSettings(qDBusObjPath);
if (status != tmpMap.begin().key().indexOf("ethernet"))
{
      QVariantMap qVarMap = tmpMap["connection"];
      if(!qVarMap.isEmpty())
      {
          QVariant qVariant = qVarMap["id"];
          if(!qVariant.isNull() && qVariant.isValid())
          {
              connectname = qVariant.toString();
          }
      }


}
}
  //  qDebug() << connectname;
      return connectname;
}

/*************************************************
Function:       changeIP
Description:    转换IP格式
Parameter:      DBus信号
Return:         生成的IP
*************************************************/
char* AboutNetwork::changeIP(u_int32_t num)
{
   // char *res = new char[16];
    char *res = (char *)malloc(16);
    if(NULL == res)
    {
        return NULL;
    }
    char *p = res;
    for (int i = 3; i >= 0; i--)
    {
        //qDebug() << "num:" << num;
        u_int32_t tmp = (num>>((3-i)*8))&0xFF;
       // qDebug() << "tmp:" << tmp;
        p = make8Bit(p,tmp);
    }
    p--;
    *p='\0';
    return res;
}

/*************************************************
Function:       make8Bit
Description:    转换格式
Parameter:      传参
Return:         生成的IP
*************************************************/
char* AboutNetwork::make8Bit(char *p,u_int32_t num)
{
    bool flag = false;
    for (int i = 2; i >= 0; i--)
    {
        int carry = num/pow(10,i);
       // qDebug() << "carry:" << carry;
        if (carry > 0)
        {
            *(p++) = carry+'0';
            flag = true;
        }
        else{
            if(flag){
                 *(p++) = carry+'0';
            }
        }
        num = num % (int)pow(10,i);
      //  qDebug() << "num2" << num;
    }
    if (!flag)
    {
        *(p++) = '0';
    }
    *(p++) = '.';
    return p;
}


//char* AboutNetwork::ipStr(u_int32_t dwIp) // 网络序输入？
//{
//  static char szIp[18] = {0};  //单线程版本，不能用于多线程
//  unsigned char *pbyIp = &dwIp;
//  sprintf(szIp, "%c.%c.%c.%c", pbyIp[0], pbyIp[1], pbyIp[2], pbyIp[3]);
//  return szIp;
//}


/*************************************************
Function:       getIP
Description:    获取网络IP地址
Parameter:      无
Return:         IP
*************************************************/
QString AboutNetwork::getIP()
{

    QString ip;
    //    QString localHostName = QHostInfo::localHostName();
    //   // qDebug() << localHostName;
    //    QHostInfo hostinfo = QHostInfo::fromName(localHostName);
    //    QList<QHostAddress> listAddress = hostinfo.addresses();
    //    foreach(QHostAddress address,hostinfo.addresses())                 /**只能获取本地IP**/
    //    {
    //        if(address.protocol() == QAbstractSocket::IPv4Protocol)
    //            qDebug() <<"IPV4 Address: "<< address.toString();
    //    }
    //    if (!listAddress.isEmpty())
    //    {
    //       QListIterator<QHostAddress> i(listAddress);
    //       for (;i.hasNext();)
    //       {
    //           qDebug()<<"!!!!!!!!!!!"<<i.next();
    //       }
    //    }

    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    //  qDebug() << list;
    foreach (QHostAddress address, list)
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)          /**只获取IPV4**/
        {
            if (address.toString().contains("127.0."))
            {
                continue;
            }
            else
            {
                ip = address.toString();
            }
        }
    }
    if (ip == "127.0.0.1")
    {
        //    qDebug() << "get local ip fail";
        return NULL;
    }
    else
    {
        //   qDebug() << ip;
        return ip;
    }

    return NULL;
}


/*************************************************
Function:       getGateway
Description:    获取网关信息
Parameter:      无
Return:         网关
*************************************************/

QString AboutNetwork::getGateway()
{

    FILE *fp;
    char buf[512];
    char cmd[128];
    char gateway[30];
    char *tmp;

    strcpy(cmd, "ip route");
    fp = popen(cmd, "r");
    if(NULL == fp)
    {
        perror("popen error");
        return "";
    }
    while(fgets(buf, sizeof(buf), fp) != NULL)
    {
        tmp =buf;
        while(*tmp && isspace(*tmp))
            ++ tmp;
        if(strncmp(tmp, "default", strlen("default")) == 0)
            break;
    }
    sscanf(buf, "%*s%*s%s", gateway);
    //   printf("default gateway:%s\n", gateway);
    pclose(fp);

    return QString(gateway);
}

/*************************************************
Function:       getDNS
Description:    获取DNS
Parameter:      无
Return:         DNS
*************************************************/

QString AboutNetwork::getDNS()
{
    NMDBus nmdbus;
    QString dnsStr = "";
    QString activeConnectionPath = "";
    const int status = -1;
    u_int32_t uint32dns;
//    char *str = changeIP(nmdbus.getNameServers());
//    if(NULL == str)
//    {
//        return dnsStr;
//    }
//    dnsStr = QString(str);
    QList<QDBusObjectPath> qDBusObjPathList;
    QVariant qvariant = nmdbus.getActiveConnections();
     qvariant.value<QDBusArgument>() >> qDBusObjPathList;
     if (qDBusObjPathList.isEmpty())
     {
         return dnsStr;
     }
     int count = qDBusObjPathList.count();
    for (int i = 0; i < count; ++i)
    {
     activeConnectionPath = qDBusObjPathList.at(i).path();
   //  qDebug() << activeConnectionPath;
    QDBusObjectPath qDBusObjPath = nmdbus.getDBusObjPath(activeConnectionPath);
    if (qDBusObjPath.path().isEmpty())
    {
        return dnsStr;
    }
    MY_QMAP tmpMap = nmdbus.getSettings(qDBusObjPath);
    if (status != tmpMap.begin().key().indexOf("ethernet"))
    {
          QVariantMap qVarMap = tmpMap["ipv4"];
          if(!qVarMap.isEmpty())
          {
              QVariant qVariant = qVarMap["dns"];
              if(!qVariant.isNull() && qVariant.isValid())
              {
                  qDBusRegisterMetaType<QList<u_int32_t> >();
                  QList<u_int32_t> uIntList;
                  qVariant.value<QDBusArgument>() >> uIntList;
                  uint32dns = uIntList.at(0);
                  dnsStr = changeIP(uint32dns);
              }
          }


    }
    }
    return dnsStr;
}

/*************************************************
Function:       SetGateWay
Description:    设置网卡
Parameter:      网卡地址
Return:         是否成功
*************************************************/

int AboutNetwork::SetGateWay(const char *szGateWay)
{
    int ret = 0;
    char cmd[128];
    QString DefGW = getGateway();

    const char *strGW = DefGW.toLatin1();

    strcpy(cmd, "route del default gw ");
    strcat(cmd, strGW);
    ret = system(cmd);
    if(ret < 0)
    {
        perror("route error");
        return -1;
    }
    strcpy(cmd, "route add default gw ");
    strcat(cmd, szGateWay);

    ret = system(cmd);
    if(ret < 0)
    {
        perror("route error");
        return -1;
    }

    return ret;
}
