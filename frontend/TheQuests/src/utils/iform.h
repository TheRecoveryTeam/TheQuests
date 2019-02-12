#ifndef IFORM_H
#define IFORM_H

#include <QObject>

class IForm: public QObject {
    Q_OBJECT
    Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged)
public:
    IForm(QObject* parent = nullptr): QObject(parent) {}
    virtual ~IForm() = default;
    virtual bool isValid() const = 0;
    Q_INVOKABLE virtual void validate() = 0;
    Q_INVOKABLE virtual void send() = 0;

signals:
    void isValidChanged(bool);
};

#endif // IFORM_H
