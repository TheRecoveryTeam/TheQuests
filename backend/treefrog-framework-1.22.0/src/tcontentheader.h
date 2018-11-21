#ifndef TCONTENTHEADER_H
#define TCONTENTHEADER_H

#include <TInternetMessageHeader>


class T_CORE_EXPORT TContentHeader : public TInternetMessageHeader
{
public:
    TContentHeader();
    TContentHeader(const TContentHeader &other);
    TContentHeader(const QByteArray &str);
    virtual ~TContentHeader() { }
    
    TContentHeader &operator=(const TContentHeader &other);
};

Q_DECLARE_METATYPE(TContentHeader)

#endif // TCONTENTHEADER_H
