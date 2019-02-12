#include "abstractcardcontroller.h"
#include "src/config/questcardtypes.h"

AbstractCardController::AbstractCardController(QObject *parent):
    QObject(parent)
{ }

const QString& AbstractCardController::getType() const
{
    return config::QuestCardTypes::NOCARD;
}
