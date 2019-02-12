#ifndef USERFINDNICKNAMEREQUEST_H
#define USERFINDNICKNAMEREQUEST_H

#include <QString>
#include "src/data_structures/interfaces/iqueryable.h"

namespace data_structures {

class UserFindNicknameRequest: public IQueryable
{
public:
    explicit UserFindNicknameRequest(const QString& nickname = "");
    QString toQueryString() const override;

    QString nickname;
};

}


#endif // USERFINDEMAILREQUEST_H
