#include "choosecardmodel.h"
#include "src/config/questcardtypes.h"

ChooseCardModel::ChooseCardModel(QObject* parent):
    AbstractCardController(parent)
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
    linksList = value;
}
