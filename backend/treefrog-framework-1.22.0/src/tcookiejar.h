#ifndef TCOOKIEJAR_H
#define TCOOKIEJAR_H

#include <QList>
#include <QString>
#include <QNetworkCookie>
#include <TGlobal>

typedef QNetworkCookie TCookie;

#ifdef Q_CC_MSVC
extern uint qHash(const TCookie &key);
#endif


class T_CORE_EXPORT TCookieJar : protected QList<TCookie>
{
public:
    TCookieJar() { }
    TCookieJar(const TCookieJar &jar);
    TCookieJar &operator=(const TCookieJar &jar);

    void addCookie(const TCookie &cookie);
    QList<TCookie> allCookies() const;
};


inline TCookieJar::TCookieJar(const TCookieJar &jar)
    : QList<TCookie>(*static_cast<const QList<TCookie> *>(&jar))
{ }

inline TCookieJar &TCookieJar::operator=(const TCookieJar &jar)
{
    QList<TCookie>::operator=(*static_cast<const QList<TCookie> *>(&jar));
    return *this;
}

inline QList<TCookie> TCookieJar::allCookies() const
{
    return *static_cast<const QList<TCookie> *>(this);
}

#endif // TCOOKIEJAR_H
