#ifndef HTTPREQUESTER_H
#define HTTPREQUESTER_H

#include <QObject>
#include <QString>
#include <QFuture>
#include <QNetworkAccessManager>
#include <QVariantMap>

class HttpRequester : public QObject
{
    Q_OBJECT
public:
    HttpRequester() = delete;
    HttpRequester(QObject *parent = nullptr);
    ~HttpRequester() = default;

    QFuture doPost(const QString& path, const QVariantMap& data);

signals:

public slots:

private:
    QString baseUrl;
    QString token;
    QNetworkAccessManager* manager;
};

#endif // HTTPREQUESTER_H
