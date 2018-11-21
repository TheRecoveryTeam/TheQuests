#ifndef CARDLINKCOLLECTIONOBJECT_H
#define CARDLINKCOLLECTIONOBJECT_H

#include <TMongoObject>
#include <QSharedData>


class T_MODEL_EXPORT CardlinkcollectionObject : public TMongoObject, public QSharedData
{
public:
    QString _id;
    QString toId;
    QVariantMap weight;
    QDateTime createdAt;
    QDateTime updatedAt;
    int lockRevision;

    enum PropertyIndex {
        Id = 0,
        ToId,
        Weight,
        CreatedAt,
        UpdatedAt,
        LockRevision,
    };

    virtual QString collectionName() const override { return QLatin1String("cardlinkcollection"); }
    virtual QString objectId() const override { return _id; }
    virtual QString &objectId() override { return _id; }

private:
    Q_OBJECT
    Q_PROPERTY(QString _id READ get_id WRITE set_id)
    T_DEFINE_PROPERTY(QString, _id)
    Q_PROPERTY(QString toId READ gettoId WRITE settoId)
    T_DEFINE_PROPERTY(QString, toId)
    Q_PROPERTY(QVariantMap weight READ getweight WRITE setweight)
    T_DEFINE_PROPERTY(QVariantMap, weight)
    Q_PROPERTY(QDateTime createdAt READ getcreatedAt WRITE setcreatedAt)
    T_DEFINE_PROPERTY(QDateTime, createdAt)
    Q_PROPERTY(QDateTime updatedAt READ getupdatedAt WRITE setupdatedAt)
    T_DEFINE_PROPERTY(QDateTime, updatedAt)
    Q_PROPERTY(int lockRevision READ getlockRevision WRITE setlockRevision)
    T_DEFINE_PROPERTY(int, lockRevision)
};
 
#endif // CARDLINKCOLLECTIONOBJECT_H