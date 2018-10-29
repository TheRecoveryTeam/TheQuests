#ifndef NETWORK_H
#define NETWORK_H

#include <QString>

namespace config {
namespace network {
    enum class Method {
        GET,
        PODT,
    };

    const QString BASE_URL = "http://localhost:8800";
}
}

#endif // NETWORK_H
