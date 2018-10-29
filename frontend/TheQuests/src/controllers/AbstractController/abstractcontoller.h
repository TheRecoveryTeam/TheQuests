#ifndef ABSTRACTCONTOLLER_H
#define ABSTRACTCONTOLLER_H

#include <QObject>

class HttpRequester;

class AbstractContoller : public QObject
{
    Q_OBJECT
public:
    explicit AbstractContoller(QObject *parent = nullptr);
    virtual ~AbstractContoller() = 0;

protected:
    HttpRequester* httpRequester;
};

#endif // ABSTRACTCONTOLLER_H
