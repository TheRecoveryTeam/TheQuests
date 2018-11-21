#ifndef QUESTRESOURCECOLLECTION_H
#define QUESTRESOURCECOLLECTION_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class QuestresourcecollectionObject;
class QJsonArray;


class T_MODEL_EXPORT Questresourcecollection : public TAbstractModel
{
public:
    Questresourcecollection();
    Questresourcecollection(const Questresourcecollection &other);
    Questresourcecollection(const QuestresourcecollectionObject &object);
    ~Questresourcecollection();

    QString id() const;
    QString name() const;
    void setName(const QString &name);
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    int lockRevision() const;
    Questresourcecollection &operator=(const Questresourcecollection &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool upsert(const QVariantMap &criteria);
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Questresourcecollection create(const QString &name);
    static Questresourcecollection create(const QVariantMap &values);
    static Questresourcecollection get(const QString &id);
    static Questresourcecollection get(const QString &id, int lockRevision);
    static int count();
    static QList<Questresourcecollection> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<QuestresourcecollectionObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Questresourcecollection &model);
    friend QDataStream &operator>>(QDataStream &ds, Questresourcecollection &model);
};

Q_DECLARE_METATYPE(Questresourcecollection)
Q_DECLARE_METATYPE(QList<Questresourcecollection>)

#endif // QUESTRESOURCECOLLECTION_H
