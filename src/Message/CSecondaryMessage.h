#ifndef CSECONDARYMESSAGE_H
#define CSECONDARYMESSAGE_H

#include "CMessage.h"
#include "../DefConst.h"
#include <QList>

class CSecondaryMessage
{
public:
    CSecondaryMessage();
    void setSecondaryMessage(CMessage* secondaryMessage);
    void setAckMessages(QList<CMessage*> list);

    CMessage* getSecondaryMessage();

private:
    CMessage* m_secondaryMessage;            // The define for secondary message
public:
    CMessage* m_ackMessages[MAX_REPONSE_MSG];          // The list ack send to Machine
};

#endif // CSECONDARYMESSAGE_H
