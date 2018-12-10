#include "finishcardcontroller.h"
#include "src/config/questcardtypes.h"

FinishCardController::FinishCardController(QObject* parent):
    AbstractCardController (parent)
{}

const QString&FinishCardController::getType() const
{
    return config::QuestCardTypes::FINISH;
}
