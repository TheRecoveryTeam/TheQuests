#ifndef CARDCOLLECTION_H
#define CARDCOLLECTION_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class CardCollectionObject;
class QJsonArray;


class T_MODEL_EXPORT CardCollection : public TAbstractModel
{
public:
    CardCollection();
    CardCollection(const CardCollection &other);
    CardCollection(const CardCollectionObject &object);
    ~CardCollection();

    QString id() const;
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    int lockRevision() const;
    CardCollection &operator=(const CardCollection &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool upsert(const QVariantMap &criteria);
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static CardCollection create(const QString &);
    static CardCollection create(const QVariantMap &values);
    static CardCollection get(const QString &id);
    static CardCollection get(const QString &id, int lockRevision);
    static int count();
    static QList<CardCollection> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<CardCollectionObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const CardCollection &model);
    friend QDataStream &operator>>(QDataStream &ds, CardCollection &model);
};

Q_DECLARE_METATYPE(CardCollection)
Q_DECLARE_METATYPE(QList<CardCollection>)

#endif // CARDCOLLECTION_H
