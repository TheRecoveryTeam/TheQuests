#ifndef QUESTCOLLECTION_H
#define QUESTCOLLECTION_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class QuestCollectionObject;
class QJsonArray;


class T_MODEL_EXPORT QuestCollection : public TAbstractModel
{
public:
    QuestCollection();
    QuestCollection(const QuestCollection &other);
    QuestCollection(const QuestCollectionObject &object);
    ~QuestCollection();

    QString id() const;
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    int lockRevision() const;
    QuestCollection &operator=(const QuestCollection &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool upsert(const QVariantMap &criteria);
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static QuestCollection create(const QString &);
    static QuestCollection create(const QVariantMap &values);
    static QuestCollection get(const QString &id);
    static QuestCollection get(const QString &id, int lockRevision);
    static int count();
    static QList<QuestCollection> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<QuestCollectionObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const QuestCollection &model);
    friend QDataStream &operator>>(QDataStream &ds, QuestCollection &model);
};

Q_DECLARE_METATYPE(QuestCollection)
Q_DECLARE_METATYPE(QList<QuestCollection>)

#endif // QUESTCOLLECTION_H
