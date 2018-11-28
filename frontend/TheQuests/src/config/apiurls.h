#ifndef APIURLS_H
#define APIURLS_H

#include <QString>

namespace config {
namespace apiUrls {

namespace card {
    const QString GET = "/api/card.get";
    const QString DO_ANSWER = "/api/card.do_answer";
    const QString USER_CREATE = "/api/user.create";
    const QString USER_LOGIN = "/api/user.login";
    const QString USER_LOGOUT = "/api/user.logout";
    const QString USER_EDIT = "/api/user.edit";
}

}
}

#endif // APIURLS_H
