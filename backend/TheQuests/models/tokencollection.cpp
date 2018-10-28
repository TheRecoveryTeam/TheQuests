#include <TreeFrogModel>
#include "tokencollection.h"
#include "tokencollectionobject.h"

Tokencollection::Tokencollection()
    : TAbstractModel(), d(new TokencollectionObject())
{
    d->lockRevision = 0;
}

Tokencollection::Tokencollection(const Tokencollection &other)
    : TAbstractModel(), d(new TokencollectionObject(*other.d))
{ }

Tokencollection::Tokencollection(const TokencollectionObject &object)
    : TAbstractModel(), d(new TokencollectionObject(object))
{ }

Tokencollection::~Tokencollection()
{
    // If the reference count becomes 0,
    // the shared data object 'TokencollectionObject' is deleted.
}

QString Tokencollection::id() const
{
    return d->_id;
}

QString Tokencollection::key() const
{
    return d->key;
}

void Tokencollection::setKey(const QString &key)
{
    d->key = key;
}

QString Tokencollection::expires() const
{
    return d->expires;
}

void Tokencollection::setExpires(const QString &expires)
{
    d->expires = expires;
}

QDateTime Tokencollection::createdAt() const
{
    return d->createdAt;
}

QDateTime Tokencollection::updatedAt() const
{
    return d->updatedAt;
}

int Tokencollection::lockRevision() const
{
    return d->lockRevision;
}

Tokencollection &Tokencollection::operator=(const Tokencollection &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

bool Tokencollection::upsert(const QVariantMap &criteria)
{
    auto *obj = dynamic_cast<TMongoObject*>(modelData());
    return (obj) ? obj->upsert(criteria) : false;
}

Tokencollection Tokencollection::create(const QString &key, const QString &expires)
{
    TokencollectionObject obj;
    obj.key = key;
    obj.expires = expires;
    if (!obj.create()) {
        return Tokencollection();
    }
    return Tokencollection(obj);
}

Tokencollection Tokencollection::create(const QVariantMap &values)
{
    Tokencollection model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Tokencollection Tokencollection::get(const QString &id)
{
    TMongoODMapper<TokencollectionObject> mapper;
    return Tokencollection(mapper.findByObjectId(id));
}

Tokencollection Tokencollection::get(const QString &id, int lockRevision)
{
    TMongoODMapper<TokencollectionObject> mapper;
    TCriteria cri;
    cri.add(TokencollectionObject::Id, id);
    cri.add(TokencollectionObject::LockRevision, lockRevision);
    return Tokencollection(mapper.findFirst(cri));
}

int Tokencollection::count()
{
    TMongoODMapper<TokencollectionObject> mapper;
    return mapper.findCount();
}

QList<Tokencollection> Tokencollection::getAll()
{
    return tfGetModelListByMongoCriteria<Tokencollection, TokencollectionObject>(TCriteria());
}

QJsonArray Tokencollection::getAllJson()
{
    QJsonArray array;
    TMongoODMapper<TokencollectionObject> mapper;

    if (mapper.find()) {
        while (mapper.next()) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Tokencollection(mapper.value()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Tokencollection::modelData()
{
    return d.data();
}

const TModelObject *Tokencollection::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Tokencollection &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Tokencollection &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Tokencollection)
