#ifndef USERLOGINREQUEST_H
#define USERLOGINREQUEST_H

#include <QString>
#include "src/data_structures/interfaces/iserializable.h"

class QJsonObject;

namespace data_structures {

class UserLoginRequest : public ISerializable
{
public:
    UserLoginRequest(const QString& email = "",
                     const QString& password = "");
    QJsonObject toJSON() const override;

    QString email;
    QString password;
};

}

#endif // USERLOGINREQUEST_H
