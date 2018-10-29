#ifndef REQUESTER_H
#define REQUESTER_H

#include <QObject>

class Requester : public QObject
{
    Q_OBJECT
public:
    explicit Requester(QObject *parent = nullptr);

signals:

public slots:
};

#endif // REQUESTER_H