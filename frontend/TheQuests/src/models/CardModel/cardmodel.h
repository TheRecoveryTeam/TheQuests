#ifndef CARDMODEL_H
#define CARDMODEL_H

#include <QObject>
#include "src/models/CardShortModel/cardshortmodel.h"

class CardModel : public CardShortModel
{
    Q_OBJECT
    Q_PROPERTY(const QString& questId READ getQuestId NOTIFY questIdChanged)
    Q_PROPERTY(const QString& type READ getType NOTIFY typeChanged)

public:

    explicit CardModel(QObject* parent = nullptr);

    CardModel(
            const QString& id,
            const QString& questId,
            const QString& title,
            const QString& imagePath,
            const QString& description,
            const QString& type,
            QObject* parent = nullptr);

    const QString& getQuestId() const;
    void setQuestId(const QString &value);

    const QString& getType() const;
    void setType(const QString &value);

signals:

    void idChanged(const QString&);
    void questIdChanged(const QString&);
    void titleChanged(const QString&);
    void imagePathChanged(const QString&);
    void descriptionChanged(const QString&);
    void typeChanged(const QString&);

private:

    QString questId;
    QString type;
};

#endif // CARDMODEL_H
