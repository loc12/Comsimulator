#include "CHandleMessageThread.h"

CHandleMessageThread::CHandleMessageThread(QObject* parent)
    : QObject(parent),
     terminationRequested(false)
{

}

CHandleMessageThread::~CHandleMessageThread()
{
    mutex.unlock();
}

void CHandleMessageThread::onParserMsg()
{
    mutexReceiveMsg->lock();
    while(!m_queueRMsg->empty()){
        if(terminationRequested){
            break;
        }
        CMessage msg;
        msg = m_queueRMsg->dequeue();
        QString rstr = msg.content();
        emit receiveMessage(rstr);
    }
    mutexReceiveMsg->unlock();

}

void CHandleMessageThread::setTerminationFlag()
{
    QMutexLocker locker(&mutex);
    terminationRequested = true;
}

void CHandleMessageThread::SetRQueueMessage(QQueue<CMessage> *queue)
{
    this->m_queueRMsg = queue;
}

void CHandleMessageThread::SetSQueueMessage(QQueue<CMessage> *queue)
{
    this->m_queueSMsg = queue;
}
void CHandleMessageThread::SetRMutexMsg(QMutex* receiveMsg)
{
    this->mutexReceiveMsg = receiveMsg;
}
