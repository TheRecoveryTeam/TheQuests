#ifndef TOKENCOLLECTION_H
#define TOKENCOLLECTION_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class TokencollectionObject;
class QJsonArray;


class T_MODEL_EXPORT Tokencollection : public TAbstractModel
{
public:
    Tokencollection();
    Tokencollection(const Tokencollection &other);
    Tokencollection(const TokencollectionObject &object);
    ~Tokencollection();

    QString id() const;
    QString key() const;
    void setKey(const QString &key);
    QString expires() const;
    void setExpires(const QString &expires);
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    int lockRevision() const;
    Tokencollection &operator=(const Tokencollection &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool upsert(const QVariantMap &criteria);
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Tokencollection create(const QString &key, const QString &expires);
    static Tokencollection create(const QVariantMap &values);
    static Tokencollection get(const QString &id);
    static Tokencollection get(const QString &id, int lockRevision);
    static int count();
    static QList<Tokencollection> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<TokencollectionObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Tokencollection &model);
    friend QDataStream &operator>>(QDataStream &ds, Tokencollection &model);
};

Q_DECLARE_METATYPE(Tokencollection)
Q_DECLARE_METATYPE(QList<Tokencollection>)

#endif // TOKENCOLLECTION_H
