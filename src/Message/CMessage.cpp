#include "CMessage.h"

CMessage::CMessage()
{

}

CMessage::CMessage(QString name, QString content)
    : m_name(name)
    , m_content(content)
{

}

const QString &CMessage::name() const
{
    return m_name;
}

void CMessage::setName(const QString &newName)
{
    m_name = newName;
}

const QString &CMessage::content() const
{
    return m_content;
}

void CMessage::setContent(const QString &newContent)
{
    m_content = newContent;
}

