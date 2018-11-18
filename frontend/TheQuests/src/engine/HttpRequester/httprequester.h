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

class ISerializable;
class IQueryable;

class HttpRequester : public QObject
{
    Q_OBJECT
public:
    typedef std::function<void(const QJsonObject&)> handleFunc;

    HttpRequester() = delete;
    HttpRequester(const QString& baseUrl, QObject* parent = nullptr);
    ~HttpRequester() = default;

    void doPost(const QString& path,
                const ISerializable& body,
                const handleFunc& onSuccess,
                const handleFunc& onError);

    void doGet(const QString& path,
               const IQueryable& queryParams,
               const handleFunc& onSuccess,
               const handleFunc& onError);

    const QString& getToken() const;
    void setToken(const QString& value);

private:
    static const QString httpTemplate;

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
