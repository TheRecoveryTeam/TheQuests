#ifndef TSESSIONCOOKIESTORE_H
#define TSESSIONCOOKIESTORE_H

#include <TSessionStore>


class TSessionCookieStore : public TSessionStore
{
public:
    QString key() const { return "cookie"; }
    TSession find(const QByteArray &id) override;
    bool store(TSession &session) override;
    bool remove(const QByteArray &id) override;
    int gc(const QDateTime &expire) override;
};

#endif // TSESSIONCOOKIESTORE_H
