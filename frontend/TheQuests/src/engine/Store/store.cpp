#include "store.h"

Store::Store(QObject *parent) :
    QObject(parent)
{ }

QObject* Store::get(const QString& key)
{
    if (this->models.find(key) == this->models.end()) {
        return nullptr;
    }
    return this->models[key];
}

void Store::addModel(const QString& key, QObject* model)
{
    // TODO: check model existance
    if (model) {
        this->models[key] = model;
    }
}
