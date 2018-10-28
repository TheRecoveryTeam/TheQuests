#ifndef SESSIONSCOLLECTION_H
#define SESSIONSCOLLECTION_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class SessionscollectionObject;
class QJsonArray;


class T_MODEL_EXPORT Sessionscollection : public TAbstractModel
{
public:
    Sessionscollection();
    Sessionscollection(const Sessionscollection &other);
    Sessionscollection(const SessionscollectionObject &object);
    ~Sessionscollection();

    QString id() const;
    QVariantMap userTokens() const;
    void setUserTokens(const QVariantMap &userTokens);
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    int lockRevision() const;
    Sessionscollection &operator=(const Sessionscollection &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool upsert(const QVariantMap &criteria);
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Sessionscollection create(const QVariantMap &userTokens);
    static Sessionscollection create(const QVariantMap &values);
    static Sessionscollection get(const QString &id);
    static Sessionscollection get(const QString &id, int lockRevision);
    static int count();
    static QList<Sessionscollection> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<SessionscollectionObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Sessionscollection &model);
    friend QDataStream &operator>>(QDataStream &ds, Sessionscollection &model);
};

Q_DECLARE_METATYPE(Sessionscollection)
Q_DECLARE_METATYPE(QList<Sessionscollection>)

#endif // SESSIONSCOLLECTION_H
