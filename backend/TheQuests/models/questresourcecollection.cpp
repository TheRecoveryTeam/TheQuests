#include <TreeFrogModel>
#include "questresourcecollection.h"
#include "questresourcecollectionobject.h"

Questresourcecollection::Questresourcecollection()
    : TAbstractModel(), d(new QuestresourcecollectionObject())
{
    d->lockRevision = 0;
}

Questresourcecollection::Questresourcecollection(const Questresourcecollection &other)
    : TAbstractModel(), d(new QuestresourcecollectionObject(*other.d))
{ }

Questresourcecollection::Questresourcecollection(const QuestresourcecollectionObject &object)
    : TAbstractModel(), d(new QuestresourcecollectionObject(object))
{ }

Questresourcecollection::~Questresourcecollection()
{
    // If the reference count becomes 0,
    // the shared data object 'QuestresourcecollectionObject' is deleted.
}

QString Questresourcecollection::id() const
{
    return d->_id;
}

QString Questresourcecollection::name() const
{
    return d->name;
}

void Questresourcecollection::setName(const QString &name)
{
    d->name = name;
}

QDateTime Questresourcecollection::createdAt() const
{
    return d->createdAt;
}

QDateTime Questresourcecollection::updatedAt() const
{
    return d->updatedAt;
}

int Questresourcecollection::lockRevision() const
{
    return d->lockRevision;
}

Questresourcecollection &Questresourcecollection::operator=(const Questresourcecollection &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

bool Questresourcecollection::upsert(const QVariantMap &criteria)
{
    auto *obj = dynamic_cast<TMongoObject*>(modelData());
    return (obj) ? obj->upsert(criteria) : false;
}

Questresourcecollection Questresourcecollection::create(const QString &name)
{
    QuestresourcecollectionObject obj;
    obj.name = name;
    if (!obj.create()) {
        return Questresourcecollection();
    }
    return Questresourcecollection(obj);
}

Questresourcecollection Questresourcecollection::create(const QVariantMap &values)
{
    Questresourcecollection model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Questresourcecollection Questresourcecollection::get(const QString &id)
{
    TMongoODMapper<QuestresourcecollectionObject> mapper;
    return Questresourcecollection(mapper.findByObjectId(id));
}

Questresourcecollection Questresourcecollection::get(const QString &id, int lockRevision)
{
    TMongoODMapper<QuestresourcecollectionObject> mapper;
    TCriteria cri;
    cri.add(QuestresourcecollectionObject::Id, id);
    cri.add(QuestresourcecollectionObject::LockRevision, lockRevision);
    return Questresourcecollection(mapper.findFirst(cri));
}

int Questresourcecollection::count()
{
    TMongoODMapper<QuestresourcecollectionObject> mapper;
    return mapper.findCount();
}

QList<Questresourcecollection> Questresourcecollection::getAll()
{
    return tfGetModelListByMongoCriteria<Questresourcecollection, QuestresourcecollectionObject>(TCriteria());
}

QJsonArray Questresourcecollection::getAllJson()
{
    QJsonArray array;
    TMongoODMapper<QuestresourcecollectionObject> mapper;

    if (mapper.find()) {
        while (mapper.next()) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Questresourcecollection(mapper.value()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Questresourcecollection::modelData()
{
    return d.data();
}

const TModelObject *Questresourcecollection::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Questresourcecollection &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Questresourcecollection &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Questresourcecollection)
