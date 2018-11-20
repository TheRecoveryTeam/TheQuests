#include "abstractcontoller.h"

AbstractContoller::AbstractContoller(
        QObject *parent,
        HttpRequester* httpRequester
        ):
    QObject(parent),
    httpRequester(httpRequester)
{ }
