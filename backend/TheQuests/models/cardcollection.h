#ifndef CARDCOLLECTION_H
#define CARDCOLLECTION_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class CardcollectionObject;
class QJsonArray;


class T_MODEL_EXPORT Cardcollection : public TAbstractModel
{
public:
    Cardcollection();
    Cardcollection(const Cardcollection &other);
    Cardcollection(const CardcollectionObject &object);
    ~Cardcollection();

    QString id() const;
    QString questId() const;
    void setQuestId(const QString &questId);
    QString title() const;
    void setTitle(const QString &title);
    QString imagePath() const;
    void setImagePath(const QString &imagePath);
    QString description() const;
    void setDescription(const QString &description);
    QVariantMap links() const;
    void setLinks(const QVariantMap &links);
    QString type() const;
    void setType(const QString &type);
    Cardcollection &operator=(const Cardcollection &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool upsert(const QVariantMap &criteria);
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Cardcollection create(const QString &questId, const QString &title, const QString &imagePath, const QString &description, const QVariantMap &links, const QString &type);
    static Cardcollection create(const QVariantMap &values);
    static Cardcollection get(const QString &id);
    static int count();
    static QList<Cardcollection> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<CardcollectionObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Cardcollection &model);
    friend QDataStream &operator>>(QDataStream &ds, Cardcollection &model);
};

Q_DECLARE_METATYPE(Cardcollection)
Q_DECLARE_METATYPE(QList<Cardcollection>)

#endif // CARDCOLLECTION_H
