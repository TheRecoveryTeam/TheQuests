#ifndef NETWORK_H
#define NETWORK_H

#include <QString>

namespace config {
namespace network {
    enum class Method {
        GET,
        POST,
    };

    const QString BASE_URL = "http://cherkov.ru";
    const QString ERROR_KEY = "__error__";
    const QString ITEMS_KEY = "__items__";
}
}

#endif // NETWORK_H
