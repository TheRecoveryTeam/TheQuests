#ifndef APP_H
#define APP_H

#include <QObject>
#include "src/engine/Store/store.h"

class App : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Store* store READ getStore NOTIFY storeChanged)
public:
    explicit App(QObject *parent = nullptr);

    Store* getStore() const;
    void setStore(Store* value);

signals:
    void storeChanged(const Store* store);

public slots:

private:
    Store* store;
};

#endif // APP_H
