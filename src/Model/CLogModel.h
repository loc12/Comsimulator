#ifndef CLOGMODEL_H
#define CLOGMODEL_H
#include <QAbstractListModel>
#include <QStringList>
#include <QDateTime>

typedef struct CLogInfo{
    QString dateTimeLog;
    QString contentLog;
    QString colorLog;
    CLogInfo(){
        this->dateTimeLog = "";
        this->contentLog = "";
        this->colorLog = "";
    }
    CLogInfo(QString datetime, QString content, QString colorLog){
        this->dateTimeLog = datetime;
        this->contentLog = content;
        this->colorLog = colorLog;
    }
}CLogInfo;
Q_DECLARE_METATYPE(CLogInfo);

class CLogModel : public QAbstractListModel
{
    Q_OBJECT
public:
    CLogModel(QObject *parent = nullptr);
    enum LogRole: int {
        DATETIME = Qt::UserRole+1,
        CONTENT,
        COLOR,
    };

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const override;
    QVariant datafromIndex(const int& index, int role) const;
    void addLog(const CLogInfo& logInfo);
public:
    void addLogView(QString message, QString color = "black");
private:
    QList<CLogInfo> m_logs;
};


#endif // CLOGMODEL_H
