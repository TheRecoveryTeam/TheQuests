#ifndef FINISHCARDCONTROLLER_H
#define FINISHCARDCONTROLLER_H

#include "../abstractcardcontroller.h"

class FinishCardController : public AbstractCardController
{
    Q_OBJECT
public:
    FinishCardController(QObject* parent = nullptr);
    virtual ~FinishCardController() override = default;

    const QString& getType() const override;
};

#endif // FINISHCARDCONTROLLER_H
