#ifndef HTTPREQUESTER_H
#define HTTPREQUESTER_H

#include <QObject>
#include <functional>

class QNetworkAccessManager;
class QUrlQuery;
class QNetworkRequest;
class QString;
class QNetworkReply;

namespace config {
namespace network {
enum class Method;
}
}

class HttpRequester : public QObject
{
    Q_OBJECT
public:
    typedef std::function<void(const QJsonObject &)> handleFunc;

    HttpRequester() = delete;
    HttpRequester(const QString& baseUrl, QObject *parent = nullptr);
    ~HttpRequester() = default;

    void doPost(const QString& path,
                const QVariantMap& body,
                const handleFunc& onSuccess,
                const handleFunc& onError);

    void doGet(const QString& path,
               const QVariantMap& queryParams,
               const handleFunc& onSuccess,
               const handleFunc& onError);

    const QString& getToken() const;
    void setToken(const QString& value);

private:
    QUrlQuery createQueryString(const QVariantMap& qyeryParams);
    QByteArray createRequestBody(const QVariantMap& body);
    QNetworkRequest createRequest(const config::network::Method& method);
    QJsonObject parseReply(QNetworkReply *reply);

    QString baseUrl;
    QString token;
    QNetworkAccessManager* manager;
};

#endif // HTTPREQUESTER_H
