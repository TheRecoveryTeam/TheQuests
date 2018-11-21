#ifndef USERSCOLLECTION_H
#define USERSCOLLECTION_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class UserscollectionObject;
class QJsonArray;


class T_MODEL_EXPORT Userscollection : public TAbstractModel
{
public:
    Userscollection();
    Userscollection(const Userscollection &other);
    Userscollection(const UserscollectionObject &object);
    ~Userscollection();

    QString id() const;
    QString username() const;
    void setUsername(const QString &username);
    QString email() const;
    void setEmail(const QString &email);
    QString password() const;
    void setPassword(const QString &password);
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    int lockRevision() const;
    Userscollection &operator=(const Userscollection &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool upsert(const QVariantMap &criteria);
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Userscollection create(const QString &username, const QString &email, const QString &password);
    static Userscollection create(const QVariantMap &values);
    static Userscollection get(const QString &id);
    static Userscollection get(const QString &id, int lockRevision);
    static int count();
    static QList<Userscollection> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<UserscollectionObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Userscollection &model);
    friend QDataStream &operator>>(QDataStream &ds, Userscollection &model);
};

Q_DECLARE_METATYPE(Userscollection)
Q_DECLARE_METATYPE(QList<Userscollection>)

#endif // USERSCOLLECTION_H
