#ifndef CARDCOLLECTIONOBJECT_H
#define CARDCOLLECTIONOBJECT_H

#include <TMongoObject>
#include <QSharedData>


class T_MODEL_EXPORT CardCollectionObject : public TMongoObject, public QSharedData
{
public:
    QString _id;
    QString questId;
    QString title;
    QString imagePath;
    QString description;
    QVariantMap links;
    QString type;

    enum PropertyIndex {
        Id = 0,
        QuestId,
        Title,
        ImagePath,
        Description,
        Links,
        Type,
    };

    virtual QString collectionName() const override { return QLatin1String("cardcollection"); }
    virtual QString objectId() const override { return _id; }
    virtual QString &objectId() override { return _id; }

private:
    Q_OBJECT
    Q_PROPERTY(QString _id READ get_id WRITE set_id)
    T_DEFINE_PROPERTY(QString, _id)
    Q_PROPERTY(QString questId READ getquestId WRITE setquestId)
    T_DEFINE_PROPERTY(QString, questId)
    Q_PROPERTY(QString title READ gettitle WRITE settitle)
    T_DEFINE_PROPERTY(QString, title)
    Q_PROPERTY(QString imagePath READ getimagePath WRITE setimagePath)
    T_DEFINE_PROPERTY(QString, imagePath)
    Q_PROPERTY(QString description READ getdescription WRITE setdescription)
    T_DEFINE_PROPERTY(QString, description)
    Q_PROPERTY(QVariantMap links READ getlinks WRITE setlinks)
    T_DEFINE_PROPERTY(QVariantMap, links)
    Q_PROPERTY(QString type READ gettype WRITE settype)
    T_DEFINE_PROPERTY(QString, type)
};
 
#endif // CARDCOLLECTIONOBJECT_H