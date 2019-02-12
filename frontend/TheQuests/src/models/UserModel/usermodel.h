#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>

class QQmlEngine;
class QJSEngine;

class UserModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(const QString& id READ getId NOTIFY idChanged)
    Q_PROPERTY(const QString& nickname READ getNickname NOTIFY nicknameChanged)
    Q_PROPERTY(const QString& email READ getEmail NOTIFY emailChanged)
    Q_PROPERTY(const QString& token READ getToken NOTIFY tokenChanged)
    Q_PROPERTY(bool isAuthenticated READ isAuthenticated NOTIFY tokenChanged)
    Q_PROPERTY(const QString& avatarPath READ getAvatarPath NOTIFY avatarPathChanged)

public:
    static UserModel* instance();

    ~UserModel();
    const QString& getId() const;
    void setId(const QString &value);

    const QString& getNickname() const;
    void setNickname(const QString &value);

    const QString& getEmail() const;
    void setEmail(const QString &value);

    const QString& getToken() const;
    void setToken(const QString &value);

    bool isAuthenticated() const;

    void setAll(const QString& id,
                const QString& nickname,
                const QString& email,
                const QString& token,
                const QString& avatarPath = "");

    const QString& getAvatarPath() const;
    void setAvatarPath(const QString& value);

signals:
    void idChanged(const QString&);
    void nicknameChanged(const QString&);
    void emailChanged(const QString&);
    void tokenChanged(const QString&);
    void avatarPathChanged(const QString&);

private:
    explicit UserModel(QObject *parent = nullptr);
    static UserModel* createInstance();

    QString id;
    QString nickname;
    QString email;
    QString token;
    QString avatarPath;
};

#endif // USERMODEL_H
