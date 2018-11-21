#include <TreeFrogModel>
#include "cardcollection.h"
#include "cardcollectionobject.h"

Cardcollection::Cardcollection()
    : TAbstractModel(), d(new CardcollectionObject())
{ }

Cardcollection::Cardcollection(const Cardcollection &other)
    : TAbstractModel(), d(new CardcollectionObject(*other.d))
{ }

Cardcollection::Cardcollection(const CardcollectionObject &object)
    : TAbstractModel(), d(new CardcollectionObject(object))
{ }

Cardcollection::~Cardcollection()
{
    // If the reference count becomes 0,
    // the shared data object 'CardcollectionObject' is deleted.
}

QString Cardcollection::id() const
{
    return d->_id;
}

QString Cardcollection::questId() const
{
    return d->questId;
}

void Cardcollection::setQuestId(const QString &questId)
{
    d->questId = questId;
}

QString Cardcollection::title() const
{
    return d->title;
}

void Cardcollection::setTitle(const QString &title)
{
    d->title = title;
}

QString Cardcollection::imagePath() const
{
    return d->imagePath;
}

void Cardcollection::setImagePath(const QString &imagePath)
{
    d->imagePath = imagePath;
}

QString Cardcollection::description() const
{
    return d->description;
}

void Cardcollection::setDescription(const QString &description)
{
    d->description = description;
}

QVariantMap Cardcollection::links() const
{
    return d->links;
}

void Cardcollection::setLinks(const QVariantMap &links)
{
    d->links = links;
}

QString Cardcollection::type() const
{
    return d->type;
}

void Cardcollection::setType(const QString &type)
{
    d->type = type;
}

Cardcollection &Cardcollection::operator=(const Cardcollection &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

bool Cardcollection::upsert(const QVariantMap &criteria)
{
    auto *obj = dynamic_cast<TMongoObject*>(modelData());
    return (obj) ? obj->upsert(criteria) : false;
}

Cardcollection Cardcollection::create(const QString &questId, const QString &title, const QString &imagePath, const QString &description, const QVariantMap &links, const QString &type)
{
    CardcollectionObject obj;
    obj.questId = questId;
    obj.title = title;
    obj.imagePath = imagePath;
    obj.description = description;
    obj.links = links;
    obj.type = type;
    if (!obj.create()) {
        return Cardcollection();
    }
    return Cardcollection(obj);
}

Cardcollection Cardcollection::create(const QVariantMap &values)
{
    Cardcollection model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Cardcollection Cardcollection::get(const QString &id)
{
    TMongoODMapper<CardcollectionObject> mapper;
    return Cardcollection(mapper.findByObjectId(id));
}

int Cardcollection::count()
{
    TMongoODMapper<CardcollectionObject> mapper;
    return mapper.findCount();
}

QList<Cardcollection> Cardcollection::getAll()
{
    return tfGetModelListByMongoCriteria<Cardcollection, CardcollectionObject>(TCriteria());
}

QJsonArray Cardcollection::getAllJson()
{
    QJsonArray array;
    TMongoODMapper<CardcollectionObject> mapper;

    if (mapper.find()) {
        while (mapper.next()) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(Cardcollection(mapper.value()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *Cardcollection::modelData()
{
    return d.data();
}

const TModelObject *Cardcollection::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Cardcollection &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Cardcollection &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Cardcollection)
