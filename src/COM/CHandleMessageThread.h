#ifndef CHANDLEMESSAGETHREAD_H
#define CHANDLEMESSAGETHREAD_H

#include <QObject>
#include <QQueue>
#include <QMutex>
#include "../Message/CMessage.h"

class CHandleMessageThread : public QObject
{
    Q_OBJECT
public:
    explicit CHandleMessageThread(QObject* parent = nullptr);
    ~CHandleMessageThread();
signals:
    void receiveMessage(QString msg);

public slots:
    void onParserMsg();
    void setTerminationFlag();
public:
    void SetRQueueMessage(QQueue<CMessage>* queue);
    void SetSQueueMessage(QQueue<CMessage>* queue);
private:
    QMutex mutex;
    bool terminationRequested;
    QQueue<CMessage>* m_queueRMsg;         // Queue of receive message
    QQueue<CMessage>* m_queueSMsg;           // Queue of send message
};

#endif // CHANDLEMESSAGETHREAD_H
