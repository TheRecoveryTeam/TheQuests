#ifndef USERSCOLLECTIONOBJECT_H
#define USERSCOLLECTIONOBJECT_H

#include <TMongoObject>
#include <QSharedData>


class T_MODEL_EXPORT UsersCollectionObject : public TMongoObject, public QSharedData
{
public:
    QString _id;
    QDateTime createdAt;
    QDateTime updatedAt;
    int lockRevision;

    enum PropertyIndex {
        Id = 0,
        CreatedAt,
        UpdatedAt,
        LockRevision,
    };

    virtual QString collectionName() const override { return QLatin1String("users_collection"); }
    virtual QString objectId() const override { return _id; }
    virtual QString &objectId() override { return _id; }

private:
    Q_OBJECT
    Q_PROPERTY(QString _id READ get_id WRITE set_id)
    T_DEFINE_PROPERTY(QString, _id)
    Q_PROPERTY(QDateTime createdAt READ getcreatedAt WRITE setcreatedAt)
    T_DEFINE_PROPERTY(QDateTime, createdAt)
    Q_PROPERTY(QDateTime updatedAt READ getupdatedAt WRITE setupdatedAt)
    T_DEFINE_PROPERTY(QDateTime, updatedAt)
    Q_PROPERTY(int lockRevision READ getlockRevision WRITE setlockRevision)
    T_DEFINE_PROPERTY(int, lockRevision)
};
 
#endif // USERSCOLLECTIONOBJECT_H