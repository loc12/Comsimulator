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
    for(;;){
        while(m_queueRMsg->size() >0){
            mutex.lock();
            if(terminationRequested){
                break;
            }
            CMessage msg;
            msg = m_queueRMsg->front();
            m_queueRMsg->pop_back();
            QString rstr = msg.content();
            receiveMessage(rstr);
            mutex.unlock();
        }
    }
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
