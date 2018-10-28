#include <TreeFrogModel>
#include "userscollection.h"
#include "userscollectionobject.h"

UsersCollection::UsersCollection()
    : TAbstractModel(), d(new UsersCollectionObject())
{
    d->lockRevision = 0;
}

UsersCollection::UsersCollection(const UsersCollection &other)
    : TAbstractModel(), d(new UsersCollectionObject(*other.d))
{ }

UsersCollection::UsersCollection(const UsersCollectionObject &object)
    : TAbstractModel(), d(new UsersCollectionObject(object))
{ }

UsersCollection::~UsersCollection()
{
    // If the reference count becomes 0,
    // the shared data object 'UsersCollectionObject' is deleted.
}

QString UsersCollection::id() const
{
    return d->_id;
}

QDateTime UsersCollection::createdAt() const
{
    return d->createdAt;
}

QDateTime UsersCollection::updatedAt() const
{
    return d->updatedAt;
}

int UsersCollection::lockRevision() const
{
    return d->lockRevision;
}

UsersCollection &UsersCollection::operator=(const UsersCollection &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

bool UsersCollection::upsert(const QVariantMap &criteria)
{
    auto *obj = dynamic_cast<TMongoObject*>(modelData());
    return (obj) ? obj->upsert(criteria) : false;
}

UsersCollection UsersCollection::create(const QString &)
{
    UsersCollectionObject obj;
    if (!obj.create()) {
        return UsersCollection();
    }
    return UsersCollection(obj);
}

UsersCollection UsersCollection::create(const QVariantMap &values)
{
    UsersCollection model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

UsersCollection UsersCollection::get(const QString &id)
{
    TMongoODMapper<UsersCollectionObject> mapper;
    return UsersCollection(mapper.findByObjectId(id));
}

UsersCollection UsersCollection::get(const QString &id, int lockRevision)
{
    TMongoODMapper<UsersCollectionObject> mapper;
    TCriteria cri;
    cri.add(UsersCollectionObject::Id, id);
    cri.add(UsersCollectionObject::LockRevision, lockRevision);
    return UsersCollection(mapper.findFirst(cri));
}

int UsersCollection::count()
{
    TMongoODMapper<UsersCollectionObject> mapper;
    return mapper.findCount();
}

QList<UsersCollection> UsersCollection::getAll()
{
    return tfGetModelListByMongoCriteria<UsersCollection, UsersCollectionObject>(TCriteria());
}

QJsonArray UsersCollection::getAllJson()
{
    QJsonArray array;
    TMongoODMapper<UsersCollectionObject> mapper;

    if (mapper.find()) {
        while (mapper.next()) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(UsersCollection(mapper.value()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *UsersCollection::modelData()
{
    return d.data();
}

const TModelObject *UsersCollection::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const UsersCollection &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, UsersCollection &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(UsersCollection)
