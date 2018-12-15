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


    namespace oauth {
        QString getOauthUrl(const QString& oauthBase, const QString& clientId,
                       const QString& redirectPath, const QString& apiV);

        const QString VK_BASE = "https://oauth.vk.com/authorize";
        const QString VK_CLIENT_ID = "6779621";
        const QString VK_REDIRECT_PATH = "/api/vk_oauth";
        const QString VK_API_V = "5.92";
    }

}
}

#endif // NETWORK_H
