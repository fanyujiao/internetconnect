
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ipAddressLineEdit->setInputMask("000.000.000.000;");       /**设置输入格式**/
    ui->maskLineEdit->setInputMask("000.000.000.000;");
    ui->gatewayLineEdit->setInputMask("000.000.000.000;");
    ui->dnsLineEdit->setInputMask("000.000.000.000;");
    ui->connectPushButton->setEnabled(false);
    //this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setGeometry(QRect(950, 55, 350, 250));//可设置窗口显示的方位与大小

    //this->setWindowOpacity(0.7);//设置透明1-全体透明
   // this->setAttribute(Qt::WA_TranslucentBackground, true);//设置透明2-窗体标题栏不透明,背景透明
    this->resize(350,460);//显示大小

}

MainWindow::~MainWindow()
{
    delete ui;
}


/*************************************************
Function:       connectPushButtenIsOk
Description:    连接按键置灰条件
Parameter:
Return:          bool
*************************************************/
bool MainWindow::connectPushButtonIsOk()
{
    bool sta = false;
    QString dns = this->ui->dnsLineEdit->text();
    QString ip = this->ui->ipAddressLineEdit->text();
    QString mask = this->ui->maskLineEdit->text();
    QString name = this->ui->connectionNameLineEdit->text();
    QString gateway = this->ui->gatewayLineEdit->text();
    if (!dns.isEmpty() && !ip.isEmpty() && !mask.isEmpty()
            && !name.isEmpty() && !gateway.isEmpty())
    {
        sta = true;
    }
    return sta;
}


/*************************************************
Function:       on_ipAddressLineEdit_textChanged
Description:     刷新button状态
Parameter:
Return:
*************************************************/
void MainWindow::on_ipAddressLineEdit_textChanged(const QString &arg1)
{
    if ("..." != arg1)
    {
        ui->connectPushButton->setEnabled(connectPushButtonIsOk());
    }
    else
    {
        ui->connectPushButton->setEnabled(false);
    }
}

/*************************************************
Function:       getAdapterInfoWithQt
Description:    获取网络信息
Parameter:      无
Return:         无
*************************************************/
void MainWindow::getAdapterInfoWithQt()
{
    AboutNetwork network;
    QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();

    foreach(QNetworkInterface interfaceItem, interfaceList)
    {
        if(interfaceItem.flags().testFlag(QNetworkInterface::IsUp)
                && interfaceItem.flags().testFlag(QNetworkInterface::IsRunning)
                && interfaceItem.flags().testFlag(QNetworkInterface::CanBroadcast)
                && interfaceItem.flags().testFlag(QNetworkInterface::CanMulticast)
                && !interfaceItem.flags().testFlag(QNetworkInterface::IsLoopBack)
                && interfaceItem.hardwareAddress()!="00:50:56:C0:00:01"                    /**排除虚拟网卡**/
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
                    // qDebug() << "getAdapterInfoWithQt";
                    ui->ipAddressLineEdit->setText(addressEntryItem.ip().toString());
                    ui->maskLineEdit->setText(addressEntryItem.netmask().toString());
                    ui->gatewayLineEdit->setText(network.getGateway());
                    ui->dnsLineEdit->setText(network.getDNS());
                    ui->connectionNameLineEdit->setText(network.getConnectName());
                }
            }

        }
    }
}


/*************************************************
Function:       on_connectPushButton_clicked
Description:    连接网络
Parameter:
Return:
*************************************************/
void MainWindow::on_connectPushButton_clicked()
{
    QString dns = this->ui->dnsLineEdit->text();
    QString ip = this->ui->ipAddressLineEdit->text();
    QString mask = this->ui->maskLineEdit->text();
    QString name = this->ui->connectionNameLineEdit->text();
    QString gateway = this->ui->gatewayLineEdit->text();
    int mod = ui->modeComboBox->currentIndex();
    qDebug() << mod;
    if (0 == mod)   /**dhcp**/
    {

    }
    else if (1 == mod)   /**手动**/
    {

    }
    else
    {

    }

}

/*************************************************
Function:       on_connectionNameLineEdit_textChanged
Description:     刷新button状态
Parameter:
Return:
*************************************************/
void MainWindow::on_connectionNameLineEdit_textChanged(const QString &arg1)
{
    if ("..." != arg1)
    {
        ui->connectPushButton->setEnabled(connectPushButtonIsOk());
    }
    else
    {
        ui->connectPushButton->setEnabled(false);
    }
}


/*************************************************
Function:       on_maskLineEdit_textChanged
Description:     刷新button状态
Parameter:
Return:
*************************************************/
void MainWindow::on_maskLineEdit_textChanged(const QString &arg1)
{
    if ("..." != arg1)
    {
        ui->connectPushButton->setEnabled(connectPushButtonIsOk());
    }
    else
    {
        ui->connectPushButton->setEnabled(false);
    }
}


/*************************************************
Function:       on_gatewayLineEdit_textChanged
Description:     刷新button状态
Parameter:
Return:
*************************************************/
void MainWindow::on_gatewayLineEdit_textChanged(const QString &arg1)
{
    if ("..." != arg1)
    {
        ui->connectPushButton->setEnabled(connectPushButtonIsOk());
    }
    else
    {
        ui->connectPushButton->setEnabled(false);
    }
}


/*************************************************
Function:       on_dnsLineEdit_textChanged
Description:     刷新button状态
Parameter:
Return:
*************************************************/
void MainWindow::on_dnsLineEdit_textChanged(const QString &arg1)
{
    if ("..." != arg1)
    {
        ui->connectPushButton->setEnabled(connectPushButtonIsOk());
    }
    else
    {
        ui->connectPushButton->setEnabled(false);
    }
}




/*************************************************
Function:       listenNewConnection
Description:   监听新连接
Parameter:
Return:
*************************************************/
void MainWindow::listenNewConnection()
{
    //    qDebug() << QDBusConnection::systemBus().connect("org.freedesktop.NetworkManager",
    //                                         "/org/freedesktop/NetworkManager/Settings",
    //                                         "org.freedesktop.NetworkManager.Settings",
    //                                         "NewConnection",this,SLOT(newConnectionSlot(QDBusObjectPath)));

    QDBusConnection::systemBus().connect("org.freedesktop.NetworkManager",
                                         "/org/freedesktop/NetworkManager",
                                         "org.freedesktop.NetworkManager",
                                         "PropertiesChanged",this,SLOT(newConnectionSlot(QVariantMap)));

}


/*************************************************
Function:       newConnectionSlot
Description:    新连接槽函数
Parameter:
Return:
*************************************************/
void MainWindow::newConnectionSlot(QVariantMap qVariantMap)
{
    NMDBus nmdbus;
    const  int status = -1;
    QVariant qVariant = qVariantMap["ActiveConnections"];
    QString activeConnectionPath = "";
    // qDebug() << "qVariant.isNull:" << qVariant.isNull() << "qVariant.isValid:" << qVariant.isValid();
    if(!qVariant.isNull() && qVariant.isValid())
    {
        QList<QDBusObjectPath> qDBusObjPathList;
        qVariant.value<QDBusArgument>() >> qDBusObjPathList;
        if(!qDBusObjPathList.isEmpty())
        {
            int count = qDBusObjPathList.count();
            for (int i = 0; i < count; ++i)
            {
                activeConnectionPath = qDBusObjPathList.at(i).path();
                //  qDebug() << qDBusObjPathList.at(0).path();
                if (activeConnectionPath.isEmpty())
                {
                    return;
                }
                QDBusObjectPath qDBusObjPath = nmdbus.getDBusObjPath(activeConnectionPath);
                if (qDBusObjPath.path().isEmpty())
                {
                    return;
                }
                MY_QMAP tmpMap = nmdbus.getSettings(qDBusObjPath);
                if (status != tmpMap.begin().key().indexOf("ethernet"))
                {
                    //  qDebug() << "newConnectionisethernet";
                    getAdapterInfoWithQt();
                }
                else
                {
                    //  qDebug() << "newConnectionisWireless";
                    return;
                }
            }
        }
        else
        {
            // qDebug() << "newConnection--->qDBusObjPathListisEmpty";
            return;
        }

    }
    else
    {
        // qDebug() << "newConnectionPropertiesChanged--->qVariantisNull or qVariantisValid";
        return;
    }

}
