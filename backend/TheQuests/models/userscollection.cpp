#include <TreeFrogModel>
#include "userscollection.h"
#include "mongoobjects/userscollectionobject.h"

Userscollection::Userscollection()
    : TAbstractModel(), d(new UserscollectionObject())
{
    d->lockRevision = 0;
}

Userscollection::Userscollection(const Userscollection &other)
    : TAbstractModel(), d(new UserscollectionObject(*other.d))
{ }

Userscollection::Userscollection(const UserscollectionObject &object)
    : TAbstractModel(), d(new UserscollectionObject(object))
{ }

Userscollection::~Userscollection()
{
    // If the reference count becomes 0,
    // the shared data object 'UserscollectionObject' is deleted.
}

QString Userscollection::id() const
{
    return d->_id;
}

QString Userscollection::username() const
{
    return d->username;
}

void Userscollection::setUsername(const QString &username)
{
    d->username = username;
}

QString Userscollection::email() const
{
    return d->email;
}

void Userscollection::setEmail(const QString &email)
{
    d->email = email;
}

QString Userscollection::password() const
{
    return d->password;
}

void Userscollection::setPassword(const QString &password)
{
    d->password = password;
}

QDateTime Userscollection::createdAt() const
{
    return d->createdAt;
}

QDateTime Userscollection::updatedAt() const
{
    return d->updatedAt;
}

int Userscollection::lockRevision() const
{
    return d->lockRevision;
}

Userscollection &Userscollection::operator=(const Userscollection &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

bool Userscollection::upsert(const QVariantMap &criteria)
{
    auto *obj = dynamic_cast<TMongoObject*>(modelData());
    return (obj) ? obj->upsert(criteria) : false;
}

Userscollection Userscollection::create(const QString &username, const QString &email, const QString &password)
{
//    UserscollectionObject obj;
//    obj.username = username;
//    obj.email = email;
//    obj.password = password;
//    if (!obj.create()) {
//        return Userscollection();
//    }
//    return Userscollection(obj);
}

Userscollection Userscollection::create(const QVariantMap &values)
{
//    Userscollection model;
//    model.setProperties(values);
//    if (!model.d->create()) {
//        model.d->clear();
//    }
//    return model;
}

Userscollection Userscollection::get(const QString &id)
{
    TMongoODMapper<UserscollectionObject> mapper;
    return Userscollection(mapper.findByObjectId(id));
}

Userscollection Userscollection::get(const QString &id, int lockRevision)
{
    TMongoODMapper<UserscollectionObject> mapper;
    TCriteria cri;
    cri.add(UserscollectionObject::Id, id);
    cri.add(UserscollectionObject::LockRevision, lockRevision);
    return Userscollection(mapper.findFirst(cri));
}

int Userscollection::count()
{
    TMongoODMapper<UserscollectionObject> mapper;
    return mapper.findCount();
}

QList<Userscollection> Userscollection::getAll()
{
    return tfGetModelListByMongoCriteria<Userscollection, UserscollectionObject>(TCriteria());
}

QJsonArray Userscollection::getAllJson()
{
    QJsonArray array;
    TMongoODMapper<UserscollectionObject> mapper;

    if (mapper.find()) {
        while (mapper.next()) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Userscollection(mapper.value()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Userscollection::modelData()
{
//    return d.data();
}

const TModelObject *Userscollection::modelData() const
{
//    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Userscollection &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Userscollection &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Userscollection)
