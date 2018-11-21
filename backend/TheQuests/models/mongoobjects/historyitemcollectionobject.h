#ifndef HISTORYITEMCOLLECTIONOBJECT_H
#define HISTORYITEMCOLLECTIONOBJECT_H

#include <TMongoObject>
#include <QSharedData>


class T_MODEL_EXPORT HistoryitemcollectionObject : public TMongoObject, public QSharedData
{
public:
    QString _id;
    QString questId;
    QString cardId;
    QString stage;
    QVariantMap resources;
    QDateTime createdAt;
    QDateTime updatedAt;
    int lockRevision;

    enum PropertyIndex {
        Id = 0,
        QuestId,
        CardId,
        Stage,
        Resources,
        CreatedAt,
        UpdatedAt,
        LockRevision,
    };

    virtual QString collectionName() const override { return QLatin1String("historyitemcollection"); }
    virtual QString objectId() const override { return _id; }
    virtual QString &objectId() override { return _id; }

private:
    Q_OBJECT
    Q_PROPERTY(QString _id READ get_id WRITE set_id)
    T_DEFINE_PROPERTY(QString, _id)
    Q_PROPERTY(QString questId READ getquestId WRITE setquestId)
    T_DEFINE_PROPERTY(QString, questId)
    Q_PROPERTY(QString cardId READ getcardId WRITE setcardId)
    T_DEFINE_PROPERTY(QString, cardId)
    Q_PROPERTY(QString stage READ getstage WRITE setstage)
    T_DEFINE_PROPERTY(QString, stage)
    Q_PROPERTY(QVariantMap resources READ getresources WRITE setresources)
    T_DEFINE_PROPERTY(QVariantMap, resources)
    Q_PROPERTY(QDateTime createdAt READ getcreatedAt WRITE setcreatedAt)
    T_DEFINE_PROPERTY(QDateTime, createdAt)
    Q_PROPERTY(QDateTime updatedAt READ getupdatedAt WRITE setupdatedAt)
    T_DEFINE_PROPERTY(QDateTime, updatedAt)
    Q_PROPERTY(int lockRevision READ getlockRevision WRITE setlockRevision)
    T_DEFINE_PROPERTY(int, lockRevision)
};
 
#endif // HISTORYITEMCOLLECTIONOBJECT_H