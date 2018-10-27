#include "app.h"

App::App(QObject *parent):
    QObject(parent),
    store(nullptr)
{

}

Store* App::getStore() const
{
    return store;
}

void App::setStore(Store* value)
{
    store = value;
}
