#ifndef HISTORYCOLLECTIONOBJECT_H
#define HISTORYCOLLECTIONOBJECT_H

#include <TMongoObject>
#include <QSharedData>


class T_MODEL_EXPORT HistorycollectionObject : public TMongoObject, public QSharedData
{
public:
    QString _id;
    QString userId;
    QStringList quests;
    QDateTime createdAt;
    QDateTime updatedAt;
    int lockRevision;

    enum PropertyIndex {
        Id = 0,
        UserId,
        Quests,
        CreatedAt,
        UpdatedAt,
        LockRevision,
    };

    virtual QString collectionName() const override { return QLatin1String("historycollection"); }
    virtual QString objectId() const override { return _id; }
    virtual QString &objectId() override { return _id; }

private:
    Q_OBJECT
    Q_PROPERTY(QString _id READ get_id WRITE set_id)
    T_DEFINE_PROPERTY(QString, _id)
    Q_PROPERTY(QString userId READ getuserId WRITE setuserId)
    T_DEFINE_PROPERTY(QString, userId)
    Q_PROPERTY(QStringList quests READ getquests WRITE setquests)
    T_DEFINE_PROPERTY(QStringList, quests)
    Q_PROPERTY(QDateTime createdAt READ getcreatedAt WRITE setcreatedAt)
    T_DEFINE_PROPERTY(QDateTime, createdAt)
    Q_PROPERTY(QDateTime updatedAt READ getupdatedAt WRITE setupdatedAt)
    T_DEFINE_PROPERTY(QDateTime, updatedAt)
    Q_PROPERTY(int lockRevision READ getlockRevision WRITE setlockRevision)
    T_DEFINE_PROPERTY(int, lockRevision)
};
 
#endif // HISTORYCOLLECTIONOBJECT_H