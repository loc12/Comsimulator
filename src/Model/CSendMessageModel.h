#ifndef SENDMESSAGEMODEL_H
#define SENDMESSAGEMODEL_H

#include <QObject>

class CSendMessageModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
public:
    CSendMessageModel(QObject* parent = 0);
    CSendMessageModel(const QString& name, const QString& content, QObject*parent = 0);

    QString name() const;
    void setName(const QString &name);

    QString content() const;
    void setContent(const QString &content);
signals:
    void nameChanged();
    void contentChanged();

private:
    QString m_name;
    QString m_content;
};

#endif // SENDMESSAGEMODEL_H
