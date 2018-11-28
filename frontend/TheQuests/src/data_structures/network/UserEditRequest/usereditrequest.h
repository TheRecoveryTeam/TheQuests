#ifndef USEREDITREQUEST_H
#define USEREDITREQUEST_H

#include <QString>
#include "src/data_structures/interfaces/iserializable.h"

class QJsonObject;

namespace data_structures {

class UserEditRequest : public ISerializable
{
public:
    UserEditRequest(const QString& nickname = "", const QString& email = "");
    QJsonObject toJSON() const override;

    QString nickname;
    QString email;
};

}

#endif // USEREDITREQUEST_H
