#include <TreeFrogModel>
#include "questcollection.h"
#include "questcollectionobject.h"

Questcollection::Questcollection()
    : TAbstractModel(), d(new QuestcollectionObject())
{
    d->lockRevision = 0;
}

Questcollection::Questcollection(const Questcollection &other)
    : TAbstractModel(), d(new QuestcollectionObject(*other.d))
{ }

Questcollection::Questcollection(const QuestcollectionObject &object)
    : TAbstractModel(), d(new QuestcollectionObject(object))
{ }

Questcollection::~Questcollection()
{
    // If the reference count becomes 0,
    // the shared data object 'QuestcollectionObject' is deleted.
}

QString Questcollection::id() const
{
    return d->_id;
}

QString Questcollection::title() const
{
    return d->title;
}

void Questcollection::setTitle(const QString &title)
{
    d->title = title;
}

QString Questcollection::description() const
{
    return d->description;
}

void Questcollection::setDescription(const QString &description)
{
    d->description = description;
}

QString Questcollection::imagePath() const
{
    return d->imagePath;
}

void Questcollection::setImagePath(const QString &imagePath)
{
    d->imagePath = imagePath;
}

QString Questcollection::firstCardId() const
{
    return d->firstCardId;
}

void Questcollection::setFirstCardId(const QString &firstCardId)
{
    d->firstCardId = firstCardId;
}

QString Questcollection::anotherId() const
{
    return d->anotherId;
}

void Questcollection::setAnotherId(const QString &anotherId)
{
    d->anotherId = anotherId;
}

QVariantMap Questcollection::resources() const
{
    return d->resources;
}

void Questcollection::setResources(const QVariantMap &resources)
{
    d->resources = resources;
}

QDateTime Questcollection::createdAt() const
{
    return d->createdAt;
}

QDateTime Questcollection::updatedAt() const
{
    return d->updatedAt;
}

int Questcollection::lockRevision() const
{
    return d->lockRevision;
}

Questcollection &Questcollection::operator=(const Questcollection &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

bool Questcollection::upsert(const QVariantMap &criteria)
{
    auto *obj = dynamic_cast<TMongoObject*>(modelData());
    return (obj) ? obj->upsert(criteria) : false;
}

Questcollection Questcollection::create(const QString &title, const QString &description, const QString &imagePath, const QString &firstCardId, const QString &anotherId, const QVariantMap &resources)
{
    QuestcollectionObject obj;
    obj.title = title;
    obj.description = description;
    obj.imagePath = imagePath;
    obj.firstCardId = firstCardId;
    obj.anotherId = anotherId;
    obj.resources = resources;
    if (!obj.create()) {
        return Questcollection();
    }
    return Questcollection(obj);
}

Questcollection Questcollection::create(const QVariantMap &values)
{
    Questcollection model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Questcollection Questcollection::get(const QString &id)
{
    TMongoODMapper<QuestcollectionObject> mapper;
    return Questcollection(mapper.findByObjectId(id));
}

Questcollection Questcollection::get(const QString &id, int lockRevision)
{
    TMongoODMapper<QuestcollectionObject> mapper;
    TCriteria cri;
    cri.add(QuestcollectionObject::Id, id);
    cri.add(QuestcollectionObject::LockRevision, lockRevision);
    return Questcollection(mapper.findFirst(cri));
}

int Questcollection::count()
{
    TMongoODMapper<QuestcollectionObject> mapper;
    return mapper.findCount();
}

QList<Questcollection> Questcollection::getAll()
{
    return tfGetModelListByMongoCriteria<Questcollection, QuestcollectionObject>(TCriteria());
}

QJsonArray Questcollection::getAllJson()
{
    QJsonArray array;
    TMongoODMapper<QuestcollectionObject> mapper;

    if (mapper.find()) {
        while (mapper.next()) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Questcollection(mapper.value()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Questcollection::modelData()
{
    return d.data();
}

const TModelObject *Questcollection::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Questcollection &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Questcollection &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Questcollection)
