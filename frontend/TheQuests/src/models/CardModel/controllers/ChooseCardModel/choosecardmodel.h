#ifndef CHOOSECARDMODEL_H
#define CHOOSECARDMODEL_H

#include <vector>
#include "../abstractcardcontroller.h"



class ChooseCardModel : public AbstractCardController
{
public:
    ChooseCardModel(QObject* parent = nullptr);
    const QString& getType() const override;

private:
};

#endif // CHOOSECARDMODEL_H
