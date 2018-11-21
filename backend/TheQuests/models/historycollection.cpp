#include <TreeFrogModel>
#include "historycollection.h"
#include "historycollectionobject.h"

Historycollection::Historycollection()
    : TAbstractModel(), d(new HistorycollectionObject())
{
    d->lockRevision = 0;
}

Historycollection::Historycollection(const Historycollection &other)
    : TAbstractModel(), d(new HistorycollectionObject(*other.d))
{ }

Historycollection::Historycollection(const HistorycollectionObject &object)
    : TAbstractModel(), d(new HistorycollectionObject(object))
{ }

Historycollection::~Historycollection()
{
    // If the reference count becomes 0,
    // the shared data object 'HistorycollectionObject' is deleted.
}

QString Historycollection::id() const
{
    return d->_id;
}

QString Historycollection::userId() const
{
    return d->userId;
}

void Historycollection::setUserId(const QString &userId)
{
    d->userId = userId;
}

QStringList Historycollection::quests() const
{
    return d->quests;
}

void Historycollection::setQuests(const QStringList &quests)
{
    d->quests = quests;
}

QDateTime Historycollection::createdAt() const
{
    return d->createdAt;
}

QDateTime Historycollection::updatedAt() const
{
    return d->updatedAt;
}

int Historycollection::lockRevision() const
{
    return d->lockRevision;
}

Historycollection &Historycollection::operator=(const Historycollection &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

bool Historycollection::upsert(const QVariantMap &criteria)
{
    auto *obj = dynamic_cast<TMongoObject*>(modelData());
    return (obj) ? obj->upsert(criteria) : false;
}

Historycollection Historycollection::create(const QString &userId, const QStringList &quests)
{
    HistorycollectionObject obj;
    obj.userId = userId;
    obj.quests = quests;
    if (!obj.create()) {
        return Historycollection();
    }
    return Historycollection(obj);
}

Historycollection Historycollection::create(const QVariantMap &values)
{
    Historycollection model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Historycollection Historycollection::get(const QString &id)
{
    TMongoODMapper<HistorycollectionObject> mapper;
    return Historycollection(mapper.findByObjectId(id));
}

Historycollection Historycollection::get(const QString &id, int lockRevision)
{
    TMongoODMapper<HistorycollectionObject> mapper;
    TCriteria cri;
    cri.add(HistorycollectionObject::Id, id);
    cri.add(HistorycollectionObject::LockRevision, lockRevision);
    return Historycollection(mapper.findFirst(cri));
}

int Historycollection::count()
{
    TMongoODMapper<HistorycollectionObject> mapper;
    return mapper.findCount();
}

QList<Historycollection> Historycollection::getAll()
{
    return tfGetModelListByMongoCriteria<Historycollection, HistorycollectionObject>(TCriteria());
}

QJsonArray Historycollection::getAllJson()
{
    QJsonArray array;
    TMongoODMapper<HistorycollectionObject> mapper;

    if (mapper.find()) {
        while (mapper.next()) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Historycollection(mapper.value()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Historycollection::modelData()
{
    return d.data();
}

const TModelObject *Historycollection::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Historycollection &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Historycollection &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Historycollection)
