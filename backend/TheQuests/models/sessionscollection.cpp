#include <TreeFrogModel>
#include "sessionscollection.h"
#include "sessionscollectionobject.h"

Sessionscollection::Sessionscollection()
    : TAbstractModel(), d(new SessionscollectionObject())
{
    d->lockRevision = 0;
}

Sessionscollection::Sessionscollection(const Sessionscollection &other)
    : TAbstractModel(), d(new SessionscollectionObject(*other.d))
{ }

Sessionscollection::Sessionscollection(const SessionscollectionObject &object)
    : TAbstractModel(), d(new SessionscollectionObject(object))
{ }

Sessionscollection::~Sessionscollection()
{
    // If the reference count becomes 0,
    // the shared data object 'SessionscollectionObject' is deleted.
}

QString Sessionscollection::id() const
{
    return d->_id;
}

QVariantMap Sessionscollection::userTokens() const
{
    return d->userTokens;
}

void Sessionscollection::setUserTokens(const QVariantMap &userTokens)
{
    d->userTokens = userTokens;
}

QDateTime Sessionscollection::createdAt() const
{
    return d->createdAt;
}

QDateTime Sessionscollection::updatedAt() const
{
    return d->updatedAt;
}

int Sessionscollection::lockRevision() const
{
    return d->lockRevision;
}

Sessionscollection &Sessionscollection::operator=(const Sessionscollection &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

bool Sessionscollection::upsert(const QVariantMap &criteria)
{
    auto *obj = dynamic_cast<TMongoObject*>(modelData());
    return (obj) ? obj->upsert(criteria) : false;
}

Sessionscollection Sessionscollection::create(const QVariantMap &userTokens)
{
    SessionscollectionObject obj;
    obj.userTokens = userTokens;
    if (!obj.create()) {
        return Sessionscollection();
    }
    return Sessionscollection(obj);
}

Sessionscollection Sessionscollection::create(const QVariantMap &values)
{
    Sessionscollection model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Sessionscollection Sessionscollection::get(const QString &id)
{
    TMongoODMapper<SessionscollectionObject> mapper;
    return Sessionscollection(mapper.findByObjectId(id));
}

Sessionscollection Sessionscollection::get(const QString &id, int lockRevision)
{
    TMongoODMapper<SessionscollectionObject> mapper;
    TCriteria cri;
    cri.add(SessionscollectionObject::Id, id);
    cri.add(SessionscollectionObject::LockRevision, lockRevision);
    return Sessionscollection(mapper.findFirst(cri));
}

int Sessionscollection::count()
{
    TMongoODMapper<SessionscollectionObject> mapper;
    return mapper.findCount();
}

QList<Sessionscollection> Sessionscollection::getAll()
{
    return tfGetModelListByMongoCriteria<Sessionscollection, SessionscollectionObject>(TCriteria());
}

QJsonArray Sessionscollection::getAllJson()
{
    QJsonArray array;
    TMongoODMapper<SessionscollectionObject> mapper;

    if (mapper.find()) {
        while (mapper.next()) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Sessionscollection(mapper.value()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Sessionscollection::modelData()
{
    return d.data();
}

const TModelObject *Sessionscollection::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Sessionscollection &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Sessionscollection &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Sessionscollection)
