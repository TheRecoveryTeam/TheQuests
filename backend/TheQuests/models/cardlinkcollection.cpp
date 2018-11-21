#include <TreeFrogModel>
#include "cardlinkcollection.h"
#include "cardlinkcollectionobject.h"

Cardlinkcollection::Cardlinkcollection()
    : TAbstractModel(), d(new CardlinkcollectionObject())
{
    d->lockRevision = 0;
}

Cardlinkcollection::Cardlinkcollection(const Cardlinkcollection &other)
    : TAbstractModel(), d(new CardlinkcollectionObject(*other.d))
{ }

Cardlinkcollection::Cardlinkcollection(const CardlinkcollectionObject &object)
    : TAbstractModel(), d(new CardlinkcollectionObject(object))
{ }

Cardlinkcollection::~Cardlinkcollection()
{
    // If the reference count becomes 0,
    // the shared data object 'CardlinkcollectionObject' is deleted.
}

QString Cardlinkcollection::id() const
{
    return d->_id;
}

QString Cardlinkcollection::toId() const
{
    return d->toId;
}

void Cardlinkcollection::setToId(const QString &toId)
{
    d->toId = toId;
}

QVariantMap Cardlinkcollection::weight() const
{
    return d->weight;
}

void Cardlinkcollection::setWeight(const QVariantMap &weight)
{
    d->weight = weight;
}

QDateTime Cardlinkcollection::createdAt() const
{
    return d->createdAt;
}

QDateTime Cardlinkcollection::updatedAt() const
{
    return d->updatedAt;
}

int Cardlinkcollection::lockRevision() const
{
    return d->lockRevision;
}

Cardlinkcollection &Cardlinkcollection::operator=(const Cardlinkcollection &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

bool Cardlinkcollection::upsert(const QVariantMap &criteria)
{
    auto *obj = dynamic_cast<TMongoObject*>(modelData());
    return (obj) ? obj->upsert(criteria) : false;
}

Cardlinkcollection Cardlinkcollection::create(const QString &toId, const QVariantMap &weight)
{
    CardlinkcollectionObject obj;
    obj.toId = toId;
    obj.weight = weight;
    if (!obj.create()) {
        return Cardlinkcollection();
    }
    return Cardlinkcollection(obj);
}

Cardlinkcollection Cardlinkcollection::create(const QVariantMap &values)
{
    Cardlinkcollection model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Cardlinkcollection Cardlinkcollection::get(const QString &id)
{
    TMongoODMapper<CardlinkcollectionObject> mapper;
    return Cardlinkcollection(mapper.findByObjectId(id));
}

Cardlinkcollection Cardlinkcollection::get(const QString &id, int lockRevision)
{
    TMongoODMapper<CardlinkcollectionObject> mapper;
    TCriteria cri;
    cri.add(CardlinkcollectionObject::Id, id);
    cri.add(CardlinkcollectionObject::LockRevision, lockRevision);
    return Cardlinkcollection(mapper.findFirst(cri));
}

int Cardlinkcollection::count()
{
    TMongoODMapper<CardlinkcollectionObject> mapper;
    return mapper.findCount();
}

QList<Cardlinkcollection> Cardlinkcollection::getAll()
{
    return tfGetModelListByMongoCriteria<Cardlinkcollection, CardlinkcollectionObject>(TCriteria());
}

QJsonArray Cardlinkcollection::getAllJson()
{
    QJsonArray array;
    TMongoODMapper<CardlinkcollectionObject> mapper;

    if (mapper.find()) {
        while (mapper.next()) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Cardlinkcollection(mapper.value()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Cardlinkcollection::modelData()
{
    return d.data();
}

const TModelObject *Cardlinkcollection::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Cardlinkcollection &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Cardlinkcollection &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Cardlinkcollection)
