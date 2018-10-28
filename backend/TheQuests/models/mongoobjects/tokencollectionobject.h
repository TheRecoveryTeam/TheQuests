#ifndef TOKENCOLLECTIONOBJECT_H
#define TOKENCOLLECTIONOBJECT_H

#include <TMongoObject>
#include <QSharedData>


class T_MODEL_EXPORT TokencollectionObject : public TMongoObject, public QSharedData
{
public:
    QString _id;
    QString key;
    QString expires;
    QDateTime createdAt;
    QDateTime updatedAt;
    int lockRevision;

    enum PropertyIndex {
        Id = 0,
        Key,
        Expires,
        CreatedAt,
        UpdatedAt,
        LockRevision,
    };

    virtual QString collectionName() const override { return QLatin1String("tokencollection"); }
    virtual QString objectId() const override { return _id; }
    virtual QString &objectId() override { return _id; }

private:
    Q_OBJECT
    Q_PROPERTY(QString _id READ get_id WRITE set_id)
    T_DEFINE_PROPERTY(QString, _id)
    Q_PROPERTY(QString key READ getkey WRITE setkey)
    T_DEFINE_PROPERTY(QString, key)
    Q_PROPERTY(QString expires READ getexpires WRITE setexpires)
    T_DEFINE_PROPERTY(QString, expires)
    Q_PROPERTY(QDateTime createdAt READ getcreatedAt WRITE setcreatedAt)
    T_DEFINE_PROPERTY(QDateTime, createdAt)
    Q_PROPERTY(QDateTime updatedAt READ getupdatedAt WRITE setupdatedAt)
    T_DEFINE_PROPERTY(QDateTime, updatedAt)
    Q_PROPERTY(int lockRevision READ getlockRevision WRITE setlockRevision)
    T_DEFINE_PROPERTY(int, lockRevision)
};
 
#endif // TOKENCOLLECTIONOBJECT_H