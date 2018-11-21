#ifndef QUESTCOLLECTION_H
#define QUESTCOLLECTION_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class QuestcollectionObject;
class QJsonArray;


class T_MODEL_EXPORT Questcollection : public TAbstractModel
{
public:
    Questcollection();
    Questcollection(const Questcollection &other);
    Questcollection(const QuestcollectionObject &object);
    ~Questcollection();

    QString id() const;
    QString title() const;
    void setTitle(const QString &title);
    QString description() const;
    void setDescription(const QString &description);
    QString imagePath() const;
    void setImagePath(const QString &imagePath);
    QString firstCardId() const;
    void setFirstCardId(const QString &firstCardId);
    QString anotherId() const;
    void setAnotherId(const QString &anotherId);
    QVariantMap resources() const;
    void setResources(const QVariantMap &resources);
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    int lockRevision() const;
    Questcollection &operator=(const Questcollection &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool upsert(const QVariantMap &criteria);
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Questcollection create(const QString &title, const QString &description, const QString &imagePath, const QString &firstCardId, const QString &anotherId, const QVariantMap &resources);
    static Questcollection create(const QVariantMap &values);
    static Questcollection get(const QString &id);
    static Questcollection get(const QString &id, int lockRevision);
    static int count();
    static QList<Questcollection> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<QuestcollectionObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Questcollection &model);
    friend QDataStream &operator>>(QDataStream &ds, Questcollection &model);
};

Q_DECLARE_METATYPE(Questcollection)
Q_DECLARE_METATYPE(QList<Questcollection>)

#endif // QUESTCOLLECTION_H
