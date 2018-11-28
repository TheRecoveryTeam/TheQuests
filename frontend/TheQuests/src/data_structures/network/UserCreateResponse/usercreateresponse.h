#ifndef USERCREATERESPONSE_H
#define USERCREATERESPONSE_H

#include <QString>

namespace data_structures {

class UserCreateResponse
{
public:
    UserCreateResponse(const QString& id = "", const QString& token = "");
    QString id;
    QString token;
};

}

#endif // USERCREATERESPONSE_H
