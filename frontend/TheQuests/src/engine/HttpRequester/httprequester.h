#ifndef HTTPREQUESTER_H
#define HTTPREQUESTER_H

#include <QObject>
#include <functional>
#include <QSharedPointer>

class QNetworkAccessManager;
class QUrlQuery;
class QNetworkRequest;
class QString;
class QNetworkReply;
class QJsonObject;
class QUrlQuery;

namespace config {
namespace network {
enum class Method;
}
}

class QQmlEngine;
class QJSEngine;
class ISerializable;
class IQueryable;

class HttpRequester : public QObject
{
    Q_OBJECT
public:
    typedef std::function<void(const QJsonObject&)> handleFunc;

    ~HttpRequester() = default;

    static HttpRequester* instance(QQmlEngine* qmle = nullptr, QJSEngine* qjse = nullptr);

    void doPost(const QString& path,
                const ISerializable& body,
                const handleFunc& onSuccess,
                const handleFunc& onError);

    void doPost(const QString& path,
                const handleFunc& onSuccess,
                const handleFunc& onError);

    void doGet(const QString& path,
               const IQueryable& queryParams,
               const handleFunc& onSuccess,
               const handleFunc& onError);


    void doGet(const QString& path,
               const handleFunc& onSuccess,
               const handleFunc& onError);
    // reset token if value == ""
    void setToken(const QString& value = "");
    const QString& getToken() const;

    const QString& getBaseUrl() const;
    void setBaseUrl(const QString& value);

private:
    static const QString httpTemplate;
    static const QString httpEmptyTemplate;
    static HttpRequester* createInstance();

    explicit HttpRequester(const QString& baseUrl = "", QObject* parent = nullptr);

    QNetworkRequest createRequest(const QString& queryString = "");
    void processRequest(QNetworkReply* reply, const handleFunc& onSuccess, const handleFunc& onError);
    bool onFinishRequest(QNetworkReply *reply);
    void handleQtNetworkErrors(QNetworkReply *reply, QJsonObject &obj);
    QJsonObject parseReply(QNetworkReply* reply);

    QString baseUrl;
    QString token;
    QSharedPointer<QNetworkAccessManager> manager;
};

#endif // HTTPREQUESTER_H
