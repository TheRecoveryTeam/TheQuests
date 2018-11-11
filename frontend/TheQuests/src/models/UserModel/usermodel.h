#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>

class UserModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(const QString& id READ getId NOTIFY idChanged)
    Q_PROPERTY(const QString& nickName READ getNickName NOTIFY nickNameChanged)
    Q_PROPERTY(const QString& eMail READ getEMail NOTIFY eMailChanged)
    Q_PROPERTY(const QString& token READ getToken NOTIFY tokenChanged)
private:
    explicit UserModel(QObject *parent = nullptr);
    static UserModel* createInstance();

signals:
    void idChanged(const QString&);
    void nickNameChanged(const QString&);
    void eMailChanged(const QString&);
    void tokenChanged(const QString&);

public:
    static UserModel* instance();

    ~UserModel();
    const QString& getId() const;
    void setId(const QString &value);

    const QString& getNickName() const;
    void setNickName(const QString &value);

    const QString& getEMail() const;
    void setEMail(const QString &value);

    const QString& getToken() const;
    void setToken(const QString &value);

    void setAll(const QString& id,
                const QString& nickName,
                const QString& eMail,
                const QString& token);

private:
    QString id;
    QString nickName;
    QString eMail;
    QString token;
};

#endif // USERMODEL_H
