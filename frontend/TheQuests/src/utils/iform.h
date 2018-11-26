#ifndef IFORM_H
#define IFORM_H

#include <QObject>

class IForm: public QObject {
    Q_OBJECT
public:
    IForm(QObject* parent = nullptr): QObject(parent) {}
    virtual ~IForm() = default;
    virtual bool isValid() = 0;
    Q_INVOKABLE virtual void send() = 0;
};

#endif // IFORM_H
