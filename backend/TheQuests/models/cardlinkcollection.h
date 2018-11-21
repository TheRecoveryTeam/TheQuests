#ifndef CARDLINKCOLLECTION_H
#define CARDLINKCOLLECTION_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class CardlinkcollectionObject;
class QJsonArray;


class T_MODEL_EXPORT Cardlinkcollection : public TAbstractModel
{
public:
    Cardlinkcollection();
    Cardlinkcollection(const Cardlinkcollection &other);
    Cardlinkcollection(const CardlinkcollectionObject &object);
    ~Cardlinkcollection();

    QString id() const;
    QString toId() const;
    void setToId(const QString &toId);
    QVariantMap weight() const;
    void setWeight(const QVariantMap &weight);
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    int lockRevision() const;
    Cardlinkcollection &operator=(const Cardlinkcollection &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool upsert(const QVariantMap &criteria);
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Cardlinkcollection create(const QString &toId, const QVariantMap &weight);
    static Cardlinkcollection create(const QVariantMap &values);
    static Cardlinkcollection get(const QString &id);
    static Cardlinkcollection get(const QString &id, int lockRevision);
    static int count();
    static QList<Cardlinkcollection> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<CardlinkcollectionObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Cardlinkcollection &model);
    friend QDataStream &operator>>(QDataStream &ds, Cardlinkcollection &model);
};

Q_DECLARE_METATYPE(Cardlinkcollection)
Q_DECLARE_METATYPE(QList<Cardlinkcollection>)

#endif // CARDLINKCOLLECTION_H
