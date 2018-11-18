#ifndef CARDDOANSWERREQUEST_H
#define CARDDOANSWERREQUEST_H

#include <QString>
#include "src/data_structures/interfaces/iserializable.h"

class QJsonDocument;

namespace data_structures {

class CardDoAnswerRequest : public ISerializable
{
public:
    CardDoAnswerRequest(const QString& cardId = "", const QString& answer = "");
    QJsonDocument toJSON() const override;

    QString cardId;
    QString answer;
};

}

#endif // CARDDOANSWERREQUEST_H
