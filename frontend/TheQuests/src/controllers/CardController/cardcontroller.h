#ifndef CARDCONTROLLER_H
#define CARDCONTROLLER_H

#include "../AbstractController/abstractcontoller.h"

class CardModel;

class CardController: public AbstractContoller
{
public:
    CardController(QObject* parent = nullptr);
    ~CardController() = default;

    void get(const QString& cardId);

private:
    CardModel* cardModel;
};

#endif // CARDCONTROLLER_H
