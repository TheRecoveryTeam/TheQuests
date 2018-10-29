#include "httprequester.h"

const QString& HttpRequester::getToken() const
{
    return token;
}

void HttpRequester::setToken(const QString& value)
{
    token = value;
}
