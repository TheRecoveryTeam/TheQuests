#ifndef CARDGETREQUEST_H
#define CARDGETREQUEST_H

#include <QString>
#include "src/data_structures/interfaces/iqueryable.h"

namespace data_structures {

class CardGetRequest: public IQueryable
{
public:
    explicit CardGetRequest(const QString& cardId = "");
    QString toQueryString() const override;

    QString cardId;
};

}

#endif // CARDGETREQUEST_H
