#include "CSendMessageModel.h"

CSendMessageModel::CSendMessageModel(QObject* parent)
    :QObject(parent)
{

}

CSendMessageModel::CSendMessageModel(const QString &name, const QString &content, QObject *parent)
    :QObject(parent)
    , m_name(name)
    , m_content(content)
{

}

QString CSendMessageModel::name() const
{
    return m_name;
}

void CSendMessageModel::setName(const QString &name)
{
    if(name != m_name){
        m_name = name;
        emit nameChanged();
    }
}

QString CSendMessageModel::content() const
{
    return m_content;
}

void CSendMessageModel::setContent(const QString &content)
{
    if(content != m_content){
        m_content = content;
        emit contentChanged();
    }
}
