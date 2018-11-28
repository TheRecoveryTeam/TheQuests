#ifndef USERLOGINRESPONSE_H
#define USERLOGINRESPONSE_H

#include <QString>

namespace data_structures {

class UserLoginResponse
{
public:
    UserLoginResponse(const QString& id = "",
                      const QString& nickname = "",
                      const QString& email = "",
                      const QString& token = "");
    QString id;
    QString nickname;
    QString email;
    QString token;
};

}
#endif // USERLOGINRESPONSE_H
