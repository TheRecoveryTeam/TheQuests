#include "choosecardmodel.h"

ChooseCardModel::ChooseCardModel(QObject* parent):
    AbstractCardController (parent)
{ }

const QString& ChooseCardModel::getType() const
{
    return "choose";
}
