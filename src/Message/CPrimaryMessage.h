#ifndef CPRIMARYMESSAGE_H
#define CPRIMARYMESSAGE_H

#include "CMessage.h"

class CPrimaryMessage
{
public:
    CPrimaryMessage();
    void setPrimaryMessage(CMessage* primaryMessage);
    void setAnsMessages(QList<CMessage>* list);

    CMessage* getPrimaryMessage();
    QList<CMessage>* getAnsMessages();
private:
    CMessage* m_primaryMessage;                   // The define for primary message
    QList<CMessage> *m_answerMessages;            // The list answer for primary message
};

#endif // CPRIMARYMESSAGE_H
