#include "CSecondaryMessage.h"


CSecondaryMessage::CSecondaryMessage()
{

}

void CSecondaryMessage::setSecondaryMessage(CMessage *secondaryMessage)
{
    this->m_secondaryMessage = secondaryMessage;
}

void CSecondaryMessage::setAckMessages(QList<CMessage*> list)
{
    for(int i = 0; i < MAX_REPONSE_MSG && i < list.size(); ++i){
        this->m_ackMessages[i] = list.at(i);
    }
}

CMessage *CSecondaryMessage::getSecondaryMessage()
{
    return m_secondaryMessage;
}
