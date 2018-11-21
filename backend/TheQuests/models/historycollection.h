#ifndef HISTORYCOLLECTION_H
#define HISTORYCOLLECTION_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class HistorycollectionObject;
class QJsonArray;


class T_MODEL_EXPORT Historycollection : public TAbstractModel
{
public:
    Historycollection();
    Historycollection(const Historycollection &other);
    Historycollection(const HistorycollectionObject &object);
    ~Historycollection();

    QString id() const;
    QString userId() const;
    void setUserId(const QString &userId);
    QStringList quests() const;
    void setQuests(const QStringList &quests);
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    int lockRevision() const;
    Historycollection &operator=(const Historycollection &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool upsert(const QVariantMap &criteria);
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Historycollection create(const QString &userId, const QStringList &quests);
    static Historycollection create(const QVariantMap &values);
    static Historycollection get(const QString &id);
    static Historycollection get(const QString &id, int lockRevision);
    static int count();
    static QList<Historycollection> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<HistorycollectionObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Historycollection &model);
    friend QDataStream &operator>>(QDataStream &ds, Historycollection &model);
};

Q_DECLARE_METATYPE(Historycollection)
Q_DECLARE_METATYPE(QList<Historycollection>)

#endif // HISTORYCOLLECTION_H
