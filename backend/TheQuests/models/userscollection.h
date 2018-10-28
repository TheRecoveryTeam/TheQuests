#ifndef USERSCOLLECTION_H
#define USERSCOLLECTION_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class UsersCollectionObject;
class QJsonArray;


class T_MODEL_EXPORT UsersCollection : public TAbstractModel
{
public:
    UsersCollection();
    UsersCollection(const UsersCollection &other);
    UsersCollection(const UsersCollectionObject &object);
    ~UsersCollection();

    QString id() const;
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    int lockRevision() const;
    UsersCollection &operator=(const UsersCollection &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool upsert(const QVariantMap &criteria);
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static UsersCollection create(const QString &);
    static UsersCollection create(const QVariantMap &values);
    static UsersCollection get(const QString &id);
    static UsersCollection get(const QString &id, int lockRevision);
    static int count();
    static QList<UsersCollection> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<UsersCollectionObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const UsersCollection &model);
    friend QDataStream &operator>>(QDataStream &ds, UsersCollection &model);
};

Q_DECLARE_METATYPE(UsersCollection)
Q_DECLARE_METATYPE(QList<UsersCollection>)

#endif // USERSCOLLECTION_H
