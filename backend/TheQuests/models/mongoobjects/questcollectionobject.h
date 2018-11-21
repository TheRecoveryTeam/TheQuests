#ifndef QUESTCOLLECTIONOBJECT_H
#define QUESTCOLLECTIONOBJECT_H

#include <TMongoObject>
#include <QSharedData>


class T_MODEL_EXPORT QuestCollectionObject : public TMongoObject, public QSharedData
{
public:
    QString _id;
    QString title;
    QString description;
    QString imagePath;
    QString firstCardId;
    QString anotherId;
    QVariantMap resources;
    QDateTime createdAt;
    QDateTime updatedAt;
    int lockRevision;

    enum PropertyIndex {
        Id = 0,
        Title,
        Description,
        ImagePath,
        FirstCardId,
        AnotherId,
        Resources,
        CreatedAt,
        UpdatedAt,
        LockRevision,
    };

    virtual QString collectionName() const override { return QLatin1String("questcollection"); }
    virtual QString objectId() const override { return _id; }
    virtual QString &objectId() override { return _id; }

private:
    Q_OBJECT
    Q_PROPERTY(QString _id READ get_id WRITE set_id)
    T_DEFINE_PROPERTY(QString, _id)
    Q_PROPERTY(QString title READ gettitle WRITE settitle)
    T_DEFINE_PROPERTY(QString, title)
    Q_PROPERTY(QString description READ getdescription WRITE setdescription)
    T_DEFINE_PROPERTY(QString, description)
    Q_PROPERTY(QString imagePath READ getimagePath WRITE setimagePath)
    T_DEFINE_PROPERTY(QString, imagePath)
    Q_PROPERTY(QString firstCardId READ getfirstCardId WRITE setfirstCardId)
    T_DEFINE_PROPERTY(QString, firstCardId)
    Q_PROPERTY(QString anotherId READ getanotherId WRITE setanotherId)
    T_DEFINE_PROPERTY(QString, anotherId)
    Q_PROPERTY(QVariantMap resources READ getresources WRITE setresources)
    T_DEFINE_PROPERTY(QVariantMap, resources)
    Q_PROPERTY(QDateTime createdAt READ getcreatedAt WRITE setcreatedAt)
    T_DEFINE_PROPERTY(QDateTime, createdAt)
    Q_PROPERTY(QDateTime updatedAt READ getupdatedAt WRITE setupdatedAt)
    T_DEFINE_PROPERTY(QDateTime, updatedAt)
    Q_PROPERTY(int lockRevision READ getlockRevision WRITE setlockRevision)
    T_DEFINE_PROPERTY(int, lockRevision)
};
 
#endif // QUESTCOLLECTIONOBJECT_H