#ifndef APIURLS_H
#define APIURLS_H

#include <QString>

namespace config {
namespace apiUrls {

namespace card {
    const QString GET = "/api/card.get";
    const QString DO_ANSWER = "/api/card.do_answer";
}

namespace user {
    const QString CREATE = "/api/user.create";
    const QString LOGIN = "/api/user.login";
    const QString LOGOUT = "/api/user.logout";
    const QString EDIT = "/api/user.edit";
    const QString FIND_EMAIL = "/api/user.find_email";
    const QString FIND_NICKNAME = "/api/user.find_nickname";
    const QString CHEAK_AUTH = "/api/user.check_auth";
}

namespace quest {
    const QString GET = "/api/quest.get";
    const QString GET_RESOURCES = "/api/quest.resources";
    const QString GET_QUEST_LIST = "/api/quest.list";
    const QString CREATE = "api/quest.create";
}

}
}

#endif // APIURLS_H
