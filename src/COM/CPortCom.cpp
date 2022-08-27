#include "CPortCom.h"
CPortCom* CPortCom::m_instance = 0;
bool CPortCom::getOpenStatus()
{
    return m_pSerialPort->isOpen();
}

void CPortCom::addSendMessage(QString msg)
{
    m_queueSend.push_back(CMessage("", msg));
}

CPortCom::CPortCom(QObject *parent)
    :QObject(parent)
{
    m_pSerialPort = new QSerialPort();
    handleMessage = new CHandleMessageThread();
    handleMessage->moveToThread(&handleMessageThread);
    connect(this, &CPortCom::readReveiveMsg, handleMessage, &CHandleMessageThread::onParserMsg);
    connect(&handleMessageThread, &QThread::finished, handleMessage, &QObject::deleteLater);
    connect(handleMessage, &CHandleMessageThread::receiveMessage, this, &CPortCom::onReceiveMessage);
    connect(m_pSerialPort, &QSerialPort::readyRead, this, &CPortCom::readData);
    handleMessageThread.start();
    handleMessage->SetRQueueMessage(&m_queueReceive);
    handleMessage->SetSQueueMessage(&m_queueSend);
    handleMessage->SetRMutexMsg(&ReceiveMsg);
}

CPortCom::~CPortCom()
{
    delete m_pSerialPort;
    m_pSerialPort = NULL;
}

void CPortCom::readData()
{
    static QString rstr;
    QByteArray rcvBuf = m_pSerialPort->readAll();
    bool isReadData = false;
    for(int i = 0; i < rcvBuf.size(); i++){
        if((rcvBuf.at(i) >= '!' && rcvBuf.at(i) < '~') || rcvBuf.at(i) == ENDCHAR){
            if(rcvBuf.at(i) != ENDCHAR){
                rstr += rcvBuf[i];
            }
            else {
                int len;
                len = rstr.size();
                if(len > 1){
                    ReceiveMsg.lock();
                    CMessage message("", rstr);
                    m_queueReceive.push_back(message);
                    ReceiveMsg.unlock();
                }
                rstr.clear();
                isReadData = true;
            }
        }
    }

    if(isReadData){
       emit readReveiveMsg();
    }
}

void CPortCom::writeData()
{
    static QMutex mutexWrite;
    mutexWrite.lock();
    while(m_queueSend.size()>0){
        CMessage msg = m_queueSend.front();
        m_queueSend.pop_back();
        QByteArray br = msg.content().toUtf8();
        m_pSerialPort->write(br);
    }
    mutexWrite.unlock();
}

void CPortCom::onReceiveMessage(QString msg)
{
    emit receiveMsg(msg);
}

bool CPortCom::openPortCom()
{
    bool r = true;
    m_pSerialPort->setPortName(m_portComSetting.m_portNo);
    m_pSerialPort->setBaudRate(m_portComSetting.m_baudRate);
    m_pSerialPort->setDataBits(m_portComSetting.m_dataBit);
    m_pSerialPort->setParity(m_portComSetting.m_parity);
    m_pSerialPort->setStopBits(QSerialPort::OneStop);
    m_pSerialPort->setFlowControl(QSerialPort::NoFlowControl);
    if (m_pSerialPort->open(QIODevice::ReadWrite)) {
        emit openComPortOK();
        r = true;
    } else {
        emit openComPortNG();
        r = false;
    }
    return r;
}

bool CPortCom::closePortCom()
{
    bool r = true;
    if (m_pSerialPort->isOpen()){
        m_pSerialPort->close();
        emit closeComPortOK();
    }
    return r;
}
