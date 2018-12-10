#ifndef USERCHECKAUTHREQUEST_H
#define USERCHECKAUTHREQUEST_H

#include <QString>
#include "src/data_structures/interfaces/iserializable.h"

class QJsonObject;

namespace data_structures {

class UserCheckAuthRequest : public ISerializable
{
public:
    UserCheckAuthRequest(const QString& token = "");

    QJsonObject toJSON() const override;

    QString token;
};

}

#endif // USERCHECKAUTHREQUEST_H
