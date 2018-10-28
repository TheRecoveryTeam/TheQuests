#ifndef HISTORYITEMCOLLECTION_H
#define HISTORYITEMCOLLECTION_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class HistoryitemcollectionObject;
class QJsonArray;


class T_MODEL_EXPORT Historyitemcollection : public TAbstractModel
{
public:
    Historyitemcollection();
    Historyitemcollection(const Historyitemcollection &other);
    Historyitemcollection(const HistoryitemcollectionObject &object);
    ~Historyitemcollection();

    QString id() const;
    QString questId() const;
    void setQuestId(const QString &questId);
    QString cardId() const;
    void setCardId(const QString &cardId);
    QString stage() const;
    void setStage(const QString &stage);
    QVariantMap resources() const;
    void setResources(const QVariantMap &resources);
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    int lockRevision() const;
    Historyitemcollection &operator=(const Historyitemcollection &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool upsert(const QVariantMap &criteria);
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Historyitemcollection create(const QString &questId, const QString &cardId, const QString &stage, const QVariantMap &resources);
    static Historyitemcollection create(const QVariantMap &values);
    static Historyitemcollection get(const QString &id);
    static Historyitemcollection get(const QString &id, int lockRevision);
    static int count();
    static QList<Historyitemcollection> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<HistoryitemcollectionObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Historyitemcollection &model);
    friend QDataStream &operator>>(QDataStream &ds, Historyitemcollection &model);
};

Q_DECLARE_METATYPE(Historyitemcollection)
Q_DECLARE_METATYPE(QList<Historyitemcollection>)

#endif // HISTORYITEMCOLLECTION_H
