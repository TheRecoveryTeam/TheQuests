#include <QUrlQuery>
#include "src/config/network.h"


QString config::network::oauth::getOauthUrl(const QString& oauthBase, const QString& clientId,
               const QString& redirectPath, const QString& apiV) {
    QUrlQuery query;
    query.addQueryItem("client_id", clientId);
    query.addQueryItem("display", "mobile");
    query.addQueryItem("redirect_uri", redirectPath);
    query.addQueryItem("resoponse_type", "code");
    query.addQueryItem("v", apiV);

    return QString("%1?%2")
            .arg(oauthBase)
            .arg(query.toString(QUrl::FullyEncoded));
}
