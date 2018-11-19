#ifndef APP_H
#define APP_H

#include <QObject>

class App : public QObject
{
    Q_OBJECT
public:
    explicit App(QObject *parent = nullptr);

private:
    void registerTypes() const;
};

#endif // APP_H
