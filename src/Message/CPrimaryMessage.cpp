#include "CPrimaryMessage.h"

CPrimaryMessage::CPrimaryMessage()
{

}

void CPrimaryMessage::setPrimaryMessage(CMessage *primaryMessage)
{
    this->m_primaryMessage = primaryMessage;
}

void CPrimaryMessage::setAnsMessages(QList<CMessage> *list)
{
    this->m_answerMessages = list;
}

CMessage *CPrimaryMessage::getPrimaryMessage()
{
    return m_primaryMessage;
}

QList<CMessage> *CPrimaryMessage::getAnsMessages()
{
    return m_answerMessages;
}
