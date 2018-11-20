#include <QDebug>
#include "cardmodel.h"
#include "src/utils/singleton.h"
#include "src/models/structures/carddetail.h"

CardModel::CardModel(QObject* parent):
    CardShortModel(parent),
    controller(nullptr)
{ }

CardModel* CardModel::createInstance()
{
    return new CardModel();
}

CardModel* CardModel::instance(QQmlEngine* qqmle, QJSEngine* qjse)
{
    return Singleton<CardModel>::instance(CardModel::createInstance);
}

const QString& CardModel::getQuestId() const
{
    return questId;
}

void CardModel::setQuestId(const QString &value)
{
    questId = value;
    emit questIdChanged(questId);
}

const QString& CardModel::getType() const
{
    return type;
}

void CardModel::setType(const QString &value)
{
    type = value;
    emit typeChanged(type);
}

AbstractCardController* CardModel::getController() const
{
    return controller;
}

void CardModel::setController(AbstractCardController* value)
{
    // Удаляем старый контроллер
    if (controller) {
        controller->deleteLater();
    }
    if (value) {
        value->setParent(this);
    }
    controller = value;
    qDebug() << "set controller" << controller;
    emit controllerChanged(controller);
}

void CardModel::setAll(const QString &id,
                       const QString &questId,
                       const QString &title,
                       const QString &imagePath,
                       const QString &description,
                       const QString &type,
                       AbstractCardController *controller)
{
    setId(id);
    setQuestId(questId);
    setTitle(title);
    setImagePath(imagePath);
    setDescription(description);
    setType(type);
    setController(controller);
}

void CardModel::setCardDetal(const structures::CardDetail& cardDetail)
{
    setId(cardDetail.id);
    setQuestId(cardDetail.questId);
    setTitle(cardDetail.title);
    setImagePath(cardDetail.imagePath);
    setDescription(cardDetail.description);
    setType(cardDetail.type);
}
