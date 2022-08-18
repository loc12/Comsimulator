#ifndef ACKMESSAGEMODEL_H
#define ACKMESSAGEMODEL_H

#include <QAbstractListModel>
#include "../Message/CMessage.h"

class CAckMessageModel : public QAbstractListModel
{
    Q_OBJECT
public:
    CAckMessageModel(QObject *parent = nullptr);
    enum LogRole: int {
        NAME = Qt::UserRole+1,
        CONTENT,
    };
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const override;
    QVariant datafromIndex(const int& index, int role) const;
    void addAckMessage(const CMessage& ackMessage);
    void clearAll();
private:
    QList<CMessage> m_messages;
};

#endif // ACKMESSAGEMODEL_H
