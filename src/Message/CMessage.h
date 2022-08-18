#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

class CMessage
{
public:
    CMessage();
    CMessage(QString name, QString content);

    const QString &name() const;
    void setName(const QString &newName);

    const QString &content() const;
    void setContent(const QString &newContent);
    CMessage& operator=(const CMessage& other){
        this->m_name = other.m_name;
        this->m_content = other.m_content;
        return *this;
    }

private:
    QString m_name;
    QString m_content;
};

#endif // MESSAGE_H
