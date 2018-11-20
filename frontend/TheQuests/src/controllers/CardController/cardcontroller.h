#ifndef CARDCONTROLLER_H
#define CARDCONTROLLER_H

#include "../AbstractController/abstractcontoller.h"

class QQmlEngine;
class QJSEngine;
class CardModel;
class HttpRequester;

class CardController: public AbstractContoller
{
    Q_OBJECT
public:
    ~CardController() = default;
    static CardController* instance(QQmlEngine* qmle = nullptr, QJSEngine* qjse = nullptr);

    Q_INVOKABLE void get(const QString& cardId) const;
    Q_INVOKABLE void doAnswer(const QString& cardId, const QString& answer) const;

private:
    static CardController* createInstance();
    explicit CardController(QObject* parent = nullptr);

    CardModel* cardModel;
};

#endif // CARDCONTROLLER_H
