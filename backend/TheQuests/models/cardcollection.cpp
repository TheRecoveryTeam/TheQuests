#include <TreeFrogModel>
#include "cardcollection.h"
#include "cardcollectionobject.h"

CardCollection::CardCollection()
    : TAbstractModel(), d(new CardCollectionObject())
{
    d->lockRevision = 0;
}

CardCollection::CardCollection(const CardCollection &other)
    : TAbstractModel(), d(new CardCollectionObject(*other.d))
{ }

CardCollection::CardCollection(const CardCollectionObject &object)
    : TAbstractModel(), d(new CardCollectionObject(object))
{ }

CardCollection::~CardCollection()
{
    // If the reference count becomes 0,
    // the shared data object 'CardCollectionObject' is deleted.
}

QString CardCollection::id() const
{
    return d->_id;
}

QDateTime CardCollection::createdAt() const
{
    return d->createdAt;
}

QDateTime CardCollection::updatedAt() const
{
    return d->updatedAt;
}

int CardCollection::lockRevision() const
{
    return d->lockRevision;
}

CardCollection &CardCollection::operator=(const CardCollection &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

bool CardCollection::upsert(const QVariantMap &criteria)
{
    auto *obj = dynamic_cast<TMongoObject*>(modelData());
    return (obj) ? obj->upsert(criteria) : false;
}

CardCollection CardCollection::create(const QString &)
{
    CardCollectionObject obj;
    if (!obj.create()) {
        return CardCollection();
    }
    return CardCollection(obj);
}

CardCollection CardCollection::create(const QVariantMap &values)
{
    CardCollection model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

CardCollection CardCollection::get(const QString &id)
{
    TMongoODMapper<CardCollectionObject> mapper;
    return CardCollection(mapper.findByObjectId(id));
}

CardCollection CardCollection::get(const QString &id, int lockRevision)
{
    TMongoODMapper<CardCollectionObject> mapper;
    TCriteria cri;
    cri.add(CardCollectionObject::Id, id);
    cri.add(CardCollectionObject::LockRevision, lockRevision);
    return CardCollection(mapper.findFirst(cri));
}

int CardCollection::count()
{
    TMongoODMapper<CardCollectionObject> mapper;
    return mapper.findCount();
}

QList<CardCollection> CardCollection::getAll()
{
    return tfGetModelListByMongoCriteria<CardCollection, CardCollectionObject>(TCriteria());
}

QJsonArray CardCollection::getAllJson()
{
    QJsonArray array;
    TMongoODMapper<CardCollectionObject> mapper;

    if (mapper.find()) {
        while (mapper.next()) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(CardCollection(mapper.value()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *CardCollection::modelData()
{
    return d.data();
}

const TModelObject *CardCollection::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const CardCollection &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, CardCollection &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(CardCollection)
