#ifndef CARDMODEL_H
#define CARDMODEL_H

#include <QObject>
#include "../CardShortModel/cardshortmodel.h"
#include "./controllers/abstractcardcontroller.h"
#include "./controllers/ChooseCardModel/choosecardmodel.h"

class QQmlEngine;
class QJSEngine;

namespace structures {
struct CardDetail;
}

class CardModel : public CardShortModel
{
    Q_OBJECT
    Q_PROPERTY(const QString& questId READ getQuestId NOTIFY questIdChanged)
    Q_PROPERTY(const QString& type READ getType NOTIFY typeChanged)
    Q_PROPERTY(AbstractCardController* controller READ getController NOTIFY controllerChanged)

public:
    ~CardModel() = default;

    static CardModel* instance();

    const QString& getQuestId() const;
    void setQuestId(const QString &value);

    const QString& getType() const;
    void setType(const QString &value);

    AbstractCardController* getController() const;
    void setController(AbstractCardController* value);

    void setAll (const QString& id,
                 const QString& questId,
                 const QString& title,
                 const QString& imagePath,
                 const QString& description,
                 const QString& type,
                 AbstractCardController* controller = nullptr);

    void setCardDetal (const structures::CardDetail& cardDetail);

signals:
    void questIdChanged(const QString&);
    void typeChanged(const QString&);
    void controllerChanged(AbstractCardController*);

private:
    static CardModel* createInstance();
    explicit CardModel(QObject* parent = nullptr);

    QString questId;
    QString type;
    AbstractCardController* controller;
};

#endif // CARDMODEL_H
