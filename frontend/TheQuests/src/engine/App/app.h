#ifndef APP_H
#define APP_H

#include <QQmlApplicationEngine>

class App
{
public:
    explicit App();
    bool init();

private:
    void registerTypes() const;
    void addConstantsToContext() const;

    QQmlApplicationEngine engine;
};

#endif // APP_H
