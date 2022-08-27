#ifndef CPORTCOM_H
#define CPORTCOM_H
#include <QQueue>
#include <QQueue>
#include <QMutex>
#include <QThread>
#include <QtSerialPort/QSerialPort>

#include "../Message/CPrimaryMessage.h"
#include "../DefConst.h"
#include "CHandleMessageThread.h"

class CPortCom : public QObject
{
    Q_OBJECT
    QThread handleMessageThread;
public:
    static CPortCom* getInstance()
    {
        static QMutex mutex;
        mutex.lock();
        if (!m_instance){
            m_instance = new CPortCom();
        }
        mutex.unlock();
        return m_instance;
    }
    static void drop()
    {
        static QMutex mutex;
        mutex.lock();
        if(m_instance != NULL)
        {
            delete m_instance;
            m_instance = NULL;
        }
        mutex.unlock();
    }
//    void SetSerialPortComm(QSerialPort* serialPortComm){
//        m_pSerialPort = serialPortComm;

////        connect(m_serialPort, &QSerialPort::getData, this, &CUVComm::writeData);
//    }
    QSerialPort* GetSerialPortComm(){
        return m_pSerialPort;
    }
    bool getOpenStatus();
    void addSendMessage(QString msg);
private:
    static CPortCom* m_instance;
    explicit CPortCom(QObject* parent = 0);
    ~CPortCom();
    QSerialPort* m_pSerialPort;
    QQueue<CMessage> m_queueSend;
    QQueue<CMessage> m_queueReceive;
    CHandleMessageThread* handleMessage;
public:
    CPortComSetting m_portComSetting;
private:
    QMutex ReceiveMsg;
public slots:
    void onReceiveMessage(QString msg);
    void readData();
    void writeData();
public:
    bool openPortCom();
    bool closePortCom();
signals:
    void readReveiveMsg();
    void receiveMsg(QString msg);
    void openComPortOK();
    void openComPortNG();
    void closeComPortOK();
    void closeComPortNG();
};

#endif // CPORTCOM_H
