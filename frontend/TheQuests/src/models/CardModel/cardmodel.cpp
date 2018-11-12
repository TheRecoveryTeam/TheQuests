#include "cardmodel.h"
#include "src/utils/singleton.h"

CardModel::CardModel(QObject* parent):
    CardShortModel(parent),
    controller(nullptr)
{ }

CardModel *CardModel::createInstance()
{
    return new CardModel();
}

CardModel::~CardModel()
{
}

CardModel *CardModel::instance()
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
}

const QString& CardModel::getType() const
{
    return type;
}

void CardModel::setType(const QString &value)
{
    type = value;
}

AbstractCardController* CardModel::getController() const
{
    return controller;
}

void CardModel::setController(AbstractCardController* value)
{
    // Удаляем старый контроллер
    delete controller;
    if (value) {
        value->setParent(this);
    }
    controller = value;
}

void CardModel::setAll(const QString &id,
                       const QString &questId,
                       const QString &title,
                       const QString &imagePath,
                       const QString &description,
                       const QString &type,
                       AbstractCardController *controller)
{
    this->id = id;
    this->questId = questId;
    this->title = title;
    this->imagePath = imagePath;
    this->description = description;
    this->questId = questId;
    this->type = type;
    this->controller = controller;
}
