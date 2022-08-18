#include "CAckMessageModel.h"

CAckMessageModel::CAckMessageModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

QHash<int, QByteArray> CAckMessageModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NAME]     = "name";
    roles[CONTENT]  = "content";
    return roles;
}

int CAckMessageModel::rowCount(const QModelIndex &parent) const
{
    do{
        (void)(parent);
    }while(0);
    return m_messages.count();
}

QVariant CAckMessageModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_messages.count()){
        return QVariant();
    }
    return datafromIndex(index.row(), role);
}

QVariant CAckMessageModel::datafromIndex(const int &index, int role) const
{
    QVariant value{QVariant::fromValue<QString>("")};
    switch (role) {
    case CAckMessageModel::NAME:
        value = QVariant::fromValue<QString>(m_messages.at(index).name());
        break;
    case CAckMessageModel::CONTENT:
        value = QVariant::fromValue<QString>(m_messages.at(index).content());
        break;
    }
    return value;
}

void CAckMessageModel::addAckMessage(const CMessage &ackMessage)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_messages << ackMessage;
    endInsertRows();
}

void CAckMessageModel::clearAll()
{
    beginResetModel();
    m_messages.clear();
    endResetModel();
}
