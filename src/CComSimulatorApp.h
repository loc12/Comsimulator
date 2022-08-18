#ifndef CCOMSIMULATORAPP_H
#define CCOMSIMULATORAPP_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>
#include <QFile>
#include <QDir>
#include "COM/CPortCom.h"
#include "Message/CPrimaryMessage.h"
#include "Message/CSecondaryMessage.h"
#include "Model/CSendMessageModel.h"
#include "Model/CLogModel.h"
#include "Model/CAckMessageModel.h"
#include "DefConst.h"
#include "enums.h"


class CComSimulatorApp : public QObject
{
    Q_OBJECT
public:
    CComSimulatorApp(QObject *parent = 0);

private:
    CPortCom* m_portCom;
    QList<CPrimaryMessage> m_primaryMessage;
    QList<CSecondaryMessage> m_secondaryMessage;
    QList<QObject*> m_sendMessageModel;
    CLogModel* m_pLogModel;
    CAckMessageModel* m_pAckModel;
    QQmlApplicationEngine* m_pEngine;

public:
    bool readConfigFile();
    void initApplication();
    void setQmlAppEngine(QQmlApplicationEngine *engine);
    Q_INVOKABLE void settingPortCom(const int& portNo, const int& baudRate, const int& dataBit, const int& parity);
public slots:
    void onConnect();
    void onDisconnect();
    void onSendMessage(QString msg);
    void onReceiveMessage(QString msg);
private:
    bool connectPortCom();
    bool disconnectPortCom();
signals:
    void showAckMessages();
    bool sendMessage();
};

#endif // CCOMSIMULATORAPP_H
