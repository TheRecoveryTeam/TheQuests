#ifndef ABSTRACTCONTOLLER_H
#define ABSTRACTCONTOLLER_H

#include <QObject>

class HttpRequester;

class AbstractContoller : public QObject
{
    Q_OBJECT
public:
    explicit AbstractContoller(QObject *parent = nullptr);
    virtual ~AbstractContoller();

protected:
    HttpRequester* httpRequester;
};

#endif // ABSTRACTCONTOLLER_H
