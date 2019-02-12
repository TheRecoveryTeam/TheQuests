#ifndef USERFINDEMAILREQUEST_H
#define USERFINDEMAILREQUEST_H

#include <QString>
#include "src/data_structures/interfaces/iqueryable.h"

namespace data_structures {

class UserFindEmailRequest: public IQueryable
{
public:
    explicit UserFindEmailRequest(const QString& email = "");
    QString toQueryString() const override;

    QString email;
};

}


#endif // USERFINDEMAILREQUEST_H
