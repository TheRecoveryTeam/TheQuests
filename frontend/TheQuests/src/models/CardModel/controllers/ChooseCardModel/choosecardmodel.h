#ifndef CHOOSECARDMODEL_H
#define CHOOSECARDMODEL_H

#include <vector>
#include "../abstractcardcontroller.h"
#include "./cardlinklist.h"

class ChooseCardModel : public AbstractCardController
{
    Q_OBJECT
    Q_PROPERTY(CardLinkList* linksList READ getLinksList NOTIFY linksListChanged)
public:
    ChooseCardModel(QObject* parent = nullptr);
    ChooseCardModel(CardLinkList* linksList, QObject* parent);
    virtual ~ChooseCardModel() override = default;

    const QString& getType() const override;

    CardLinkList* getLinksList() const;
    void setLinksList(CardLinkList* value);

signals:
    void linksListChanged(CardLinkList* newLinksList);

private:
    CardLinkList* linksList;
};

#endif // CHOOSECARDMODEL_H
