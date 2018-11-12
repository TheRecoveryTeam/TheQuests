#include <QDebug>
#include "choosecardmodel.h"
#include "src/config/questcardtypes.h"


ChooseCardModel::ChooseCardModel(QObject* parent):
    AbstractCardController(parent),
    linksList(nullptr)
{ }

ChooseCardModel::ChooseCardModel(CardLinkList* linksList, QObject* parent):
    AbstractCardController(parent),
    linksList(linksList)
{ }

const QString& ChooseCardModel::getType() const
{
    return config::QuestCardTypes::CHOOSE;
}

CardLinkList* ChooseCardModel::getLinksList() const
{
    return linksList;
}

void ChooseCardModel::setLinksList(CardLinkList* value)
{
    // Удаляем старые ссылки
    if (this->linksList) {
        delete linksList;
    }
    if (value) {
        value->setParent(this);
    }
    linksList = value;
    linksListChanged(linksList);
}
