#ifndef APIURLS_H
#define APIURLS_H

#include <QString>

namespace config {
namespace apiUrls {

namespace card {
    const QString GET = "/api/card.get";
    const QString DO_ANSWER = "/api/card.do_answer";
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
