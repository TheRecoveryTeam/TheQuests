#ifndef STORE_H
#define STORE_H

#include <QObject>
#include <map>
#include "src/models/CardModel/cardmodel.h"

class Store : public QObject
{
    Q_OBJECT
public:
    Store(QObject* parent = nullptr);
    Q_INVOKABLE QObject* get(const QString& key);
    void addModel(const QString& key, QObject* model);

signals:

public slots:

private:
    std::map<QString, QObject*> models;
};

#endif // STORE_H
