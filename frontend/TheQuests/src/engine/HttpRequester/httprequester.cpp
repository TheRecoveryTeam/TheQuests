#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include <QJsonDocument>
#include <QNetworkReply>
#include "src/utils/singleton.h"
#include "src/data_structures/interfaces/iserializable.h"
#include "src/data_structures/interfaces/iqueryable.h"
#include "src/config/network.h"
#include "httprequester.h"

const QString HttpRequester::httpTemplate = "%1%2?%3";

HttpRequester::HttpRequester(const QString& baseUrl, QObject* parent):
    QObject (parent),
    baseUrl(baseUrl),
    manager(new QNetworkAccessManager())
{ }

HttpRequester* HttpRequester::instance(QQmlEngine* qmle, QJSEngine* qjse)
{
    return Singleton<HttpRequester>::instance(HttpRequester::createInstance);
}

void HttpRequester::doPost(
        const QString& path,
        const ISerializable& body,
        const HttpRequester::handleFunc& onSuccess,
        const HttpRequester::handleFunc& onError
        )
{
    auto url = HttpRequester::httpTemplate
            .arg(baseUrl)
            .arg(path)
            .arg("");

    auto request = createRequest(url);
    auto byteBody = QJsonDocument(body.toJSON()).toJson(QJsonDocument::Compact);
    qDebug() << byteBody;
    auto reply = manager->post(request, byteBody);
    processRequest(reply, onSuccess, onError);
}

void HttpRequester::doGet(
        const QString& path,
        const IQueryable& queryParams,
        const HttpRequester::handleFunc& onSuccess,
        const HttpRequester::handleFunc& onError
        )
{
    auto url = HttpRequester::httpTemplate
            .arg(baseUrl)
            .arg(path)
            .arg(queryParams.toQueryString());

    auto request = createRequest(url);
    auto reply = manager->get(request);
    processRequest(reply, onSuccess, onError);
}

const QString& HttpRequester::getToken() const
{
    return token;
}

void HttpRequester::setToken(const QString& value)
{
    token = value;
}

QNetworkRequest HttpRequester::createRequest(const QString& url)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Accept", "*/*");
    if(!token.isEmpty()) {
        request.setRawHeader("Authorization", QString("token %1").arg(token).toUtf8());
    }

    return request;
}

void HttpRequester::processRequest(QNetworkReply* reply, const HttpRequester::handleFunc& onSuccess, const HttpRequester::handleFunc& onError)
{
    connect(reply, &QNetworkReply::finished, this, [this, onSuccess, onError, reply]() {
        QJsonObject obj = parseReply(reply);
        if (onFinishRequest(reply)) {
            if (onSuccess != nullptr) {
                onSuccess(obj);
            }
        }
        else {
            handleQtNetworkErrors(reply, obj);
            if (onError != nullptr) {
                onError(obj);
            }
        }
        reply->close();
        reply->deleteLater();
    });
}

bool HttpRequester::onFinishRequest(QNetworkReply *reply)
{
    auto replyError = reply->error();
    if (replyError == QNetworkReply::NoError ) {
        int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if ((code >=200) && (code < 300)) {
            return true;
        }
    }
    return false;
}

void HttpRequester::handleQtNetworkErrors(QNetworkReply *reply, QJsonObject &obj)
{
    qDebug() << reply->error();
    obj[config::network::ERROR_KEY] = reply->errorString();
}

QJsonObject HttpRequester::parseReply(QNetworkReply* reply)
{
    QJsonObject jsonObj;
    QJsonDocument jsonDoc;
    QJsonParseError parseError;
    auto replyText = reply->readAll();
    jsonDoc = QJsonDocument::fromJson(replyText, &parseError);

    if(parseError.error != QJsonParseError::NoError){
        qWarning() << "Json parse error: " << parseError.errorString();
        jsonObj[config::network::ERROR_KEY] = parseError.errorString();
    }
    else {
        if(jsonDoc.isObject()) {
            jsonObj = jsonDoc.object();
        }
        else if (jsonDoc.isArray()) {
            jsonObj[config::network::ITEMS_KEY] = QJsonArray(jsonDoc.array());
        }
    }
    return jsonObj;
}

const QString& HttpRequester::getBaseUrl() const
{
    return baseUrl;
}

void HttpRequester::setBaseUrl(const QString& value)
{
    baseUrl = value;
}

HttpRequester*HttpRequester::createInstance()
{
    // default value in BASE_URL
    return new HttpRequester(config::network::BASE_URL);
}
