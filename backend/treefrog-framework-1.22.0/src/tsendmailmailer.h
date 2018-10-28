#ifndef TSENDMAILMAILER_H
#define TSENDMAILMAILER_H

#include <QObject>
#include <QStringList>
#include <QByteArray>
#include <QProcess>
#include <TMailMessage>


class T_CORE_EXPORT TSendmailMailer : public QObject
{
    Q_OBJECT
public:
    TSendmailMailer(const QString &command, QObject *parent = 0);
    ~TSendmailMailer();

    QString key() const { return "sendmail"; }
    bool send(const TMailMessage &message);
    void sendLater(const TMailMessage &message);

protected slots:
    void sendAndDeleteLater();

protected:
    bool send();

private:
    QString sendmailCmd;
    TMailMessage mailMessage;

    T_DISABLE_COPY(TSendmailMailer)
    T_DISABLE_MOVE(TSendmailMailer)
};

#endif // TSENDMAILMAILER_H
