#include <QJsonDocument>
#include <QJsonObject>
#include "carddoanswerrequest.h"

data_structures::CardDoAnswerRequest::CardDoAnswerRequest(const QString& cardId,
                                                          const QString& answer):
    cardId(cardId),
    answer(answer)
{ }

QJsonObject data_structures::CardDoAnswerRequest::toJSON() const
{
    QJsonObject json;
    json["cardId"] = cardId;
    json["answer"] = answer;
    return json;
}


