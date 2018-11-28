#ifndef USERCREATEREQUEST_H
#define USERCREATEREQUEST_H

#include <QString>
#include "src/data_structures/interfaces/iserializable.h"

class JQsonObject;

namespace data_structures {

class UserCreateRequest : public ISerializable
{
public:
    UserCreateRequest(const QString& email = "",
                      const QString& nickname = "",
                      const QString& password = "");
    QJsonObject toJSON() const override;

    QString email;
    QString nickname;
    QString password;
};

}

#endif // USERCREATEREQUEST_H
