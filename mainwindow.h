/*************************************************
Copyright:Wuxi National Fundamental Software of China Co., Ltd
Author:yujiao.fan
Date:2016-05-09
Description: 主界面窗口
**************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "aboutnetwork.h"



namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void getAdapterInfoWithQt();
    bool connectPushButtonIsOk();
    void listenNewConnection();

private slots:
    void on_ipAddressLineEdit_textChanged(const QString &arg1);
    void on_connectPushButton_clicked();
    void on_connectionNameLineEdit_textChanged(const QString &arg1);
    void on_maskLineEdit_textChanged(const QString &arg1);
    void on_gatewayLineEdit_textChanged(const QString &arg1);
    void on_dnsLineEdit_textChanged(const QString &arg1);
    void newConnectionSlot(QVariantMap qVariantMap);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
