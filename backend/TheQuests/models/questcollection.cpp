#include <TreeFrogModel>
#include "questcollection.h"
#include "questcollectionobject.h"

QuestCollection::QuestCollection()
    : TAbstractModel(), d(new QuestCollectionObject())
{
    d->lockRevision = 0;
}

QuestCollection::QuestCollection(const QuestCollection &other)
    : TAbstractModel(), d(new QuestCollectionObject(*other.d))
{ }

QuestCollection::QuestCollection(const QuestCollectionObject &object)
    : TAbstractModel(), d(new QuestCollectionObject(object))
{ }

QuestCollection::~QuestCollection()
{
    // If the reference count becomes 0,
    // the shared data object 'QuestCollectionObject' is deleted.
}

QString QuestCollection::id() const
{
    return d->_id;
}

QDateTime QuestCollection::createdAt() const
{
    return d->createdAt;
}

QDateTime QuestCollection::updatedAt() const
{
    return d->updatedAt;
}

int QuestCollection::lockRevision() const
{
    return d->lockRevision;
}

QuestCollection &QuestCollection::operator=(const QuestCollection &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

bool QuestCollection::upsert(const QVariantMap &criteria)
{
    auto *obj = dynamic_cast<TMongoObject*>(modelData());
    return (obj) ? obj->upsert(criteria) : false;
}

QuestCollection QuestCollection::create(const QString &)
{
    QuestCollectionObject obj;
    if (!obj.create()) {
        return QuestCollection();
    }
    return QuestCollection(obj);
}

QuestCollection QuestCollection::create(const QVariantMap &values)
{
    QuestCollection model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

QuestCollection QuestCollection::get(const QString &id)
{
    TMongoODMapper<QuestCollectionObject> mapper;
    return QuestCollection(mapper.findByObjectId(id));
}

QuestCollection QuestCollection::get(const QString &id, int lockRevision)
{
    TMongoODMapper<QuestCollectionObject> mapper;
    TCriteria cri;
    cri.add(QuestCollectionObject::Id, id);
    cri.add(QuestCollectionObject::LockRevision, lockRevision);
    return QuestCollection(mapper.findFirst(cri));
}

int QuestCollection::count()
{
    TMongoODMapper<QuestCollectionObject> mapper;
    return mapper.findCount();
}

QList<QuestCollection> QuestCollection::getAll()
{
    return tfGetModelListByMongoCriteria<QuestCollection, QuestCollectionObject>(TCriteria());
}

QJsonArray QuestCollection::getAllJson()
{
    QJsonArray array;
    TMongoODMapper<QuestCollectionObject> mapper;

    if (mapper.find()) {
        while (mapper.next()) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(QuestCollection(mapper.value()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *QuestCollection::modelData()
{
    return d.data();
}

const TModelObject *QuestCollection::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const QuestCollection &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, QuestCollection &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(QuestCollection)
