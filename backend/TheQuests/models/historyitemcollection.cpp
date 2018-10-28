#include <TreeFrogModel>
#include "historyitemcollection.h"
#include "historyitemcollectionobject.h"

Historyitemcollection::Historyitemcollection()
    : TAbstractModel(), d(new HistoryitemcollectionObject())
{
    d->lockRevision = 0;
}

Historyitemcollection::Historyitemcollection(const Historyitemcollection &other)
    : TAbstractModel(), d(new HistoryitemcollectionObject(*other.d))
{ }

Historyitemcollection::Historyitemcollection(const HistoryitemcollectionObject &object)
    : TAbstractModel(), d(new HistoryitemcollectionObject(object))
{ }

Historyitemcollection::~Historyitemcollection()
{
    // If the reference count becomes 0,
    // the shared data object 'HistoryitemcollectionObject' is deleted.
}

QString Historyitemcollection::id() const
{
    return d->_id;
}

QString Historyitemcollection::questId() const
{
    return d->questId;
}

void Historyitemcollection::setQuestId(const QString &questId)
{
    d->questId = questId;
}

QString Historyitemcollection::cardId() const
{
    return d->cardId;
}

void Historyitemcollection::setCardId(const QString &cardId)
{
    d->cardId = cardId;
}

QString Historyitemcollection::stage() const
{
    return d->stage;
}

void Historyitemcollection::setStage(const QString &stage)
{
    d->stage = stage;
}

QVariantMap Historyitemcollection::resources() const
{
    return d->resources;
}

void Historyitemcollection::setResources(const QVariantMap &resources)
{
    d->resources = resources;
}

QDateTime Historyitemcollection::createdAt() const
{
    return d->createdAt;
}

QDateTime Historyitemcollection::updatedAt() const
{
    return d->updatedAt;
}

int Historyitemcollection::lockRevision() const
{
    return d->lockRevision;
}

Historyitemcollection &Historyitemcollection::operator=(const Historyitemcollection &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

bool Historyitemcollection::upsert(const QVariantMap &criteria)
{
    auto *obj = dynamic_cast<TMongoObject*>(modelData());
    return (obj) ? obj->upsert(criteria) : false;
}

Historyitemcollection Historyitemcollection::create(const QString &questId, const QString &cardId, const QString &stage, const QVariantMap &resources)
{
    HistoryitemcollectionObject obj;
    obj.questId = questId;
    obj.cardId = cardId;
    obj.stage = stage;
    obj.resources = resources;
    if (!obj.create()) {
        return Historyitemcollection();
    }
    return Historyitemcollection(obj);
}

Historyitemcollection Historyitemcollection::create(const QVariantMap &values)
{
    Historyitemcollection model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Historyitemcollection Historyitemcollection::get(const QString &id)
{
    TMongoODMapper<HistoryitemcollectionObject> mapper;
    return Historyitemcollection(mapper.findByObjectId(id));
}

Historyitemcollection Historyitemcollection::get(const QString &id, int lockRevision)
{
    TMongoODMapper<HistoryitemcollectionObject> mapper;
    TCriteria cri;
    cri.add(HistoryitemcollectionObject::Id, id);
    cri.add(HistoryitemcollectionObject::LockRevision, lockRevision);
    return Historyitemcollection(mapper.findFirst(cri));
}

int Historyitemcollection::count()
{
    TMongoODMapper<HistoryitemcollectionObject> mapper;
    return mapper.findCount();
}

QList<Historyitemcollection> Historyitemcollection::getAll()
{
    return tfGetModelListByMongoCriteria<Historyitemcollection, HistoryitemcollectionObject>(TCriteria());
}

QJsonArray Historyitemcollection::getAllJson()
{
    QJsonArray array;
    TMongoODMapper<HistoryitemcollectionObject> mapper;

    if (mapper.find()) {
        while (mapper.next()) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Historyitemcollection(mapper.value()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Historyitemcollection::modelData()
{
    return d.data();
}

const TModelObject *Historyitemcollection::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Historyitemcollection &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Historyitemcollection &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Historyitemcollection)
