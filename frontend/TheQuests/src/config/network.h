#ifndef NETWORK_H
#define NETWORK_H

#include <QString>

namespace config {
namespace network {
    enum class Method {
        GET,
        POST,
    };

    const QString BASE_URL = "http://127.0.0.1:8008";
    const QString ERROR_KEY = "__error__";
    const QString ITEMS_KEY = "__items__";


    namespace oauth {
        QString getOauthUrl(const QString& oauthBase, const QString& clientId,
                       const QString& redirectPath, const QString& apiV);

        const QString VK_BASE = "https://oauth.vk.com/authorize";
        const QString VK_CLIENT_ID = "6779621";
        const QString VK_REDIRECT_PATH = "http://127.0.0.1:9123/api/user/vk_oauth2";
        const QString VK_API_V = "5.92";
    }

}
}

#endif // NETWORK_H
