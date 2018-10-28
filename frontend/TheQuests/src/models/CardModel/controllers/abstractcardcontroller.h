#ifndef ABSTRACTCARDCONTROLLER_H
#define ABSTRACTCARDCONTROLLER_H

#include <QObject>

class AbstractCardController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(const QString& type READ getType)
public:
    explicit AbstractCardController(QObject *parent = nullptr);
    virtual ~AbstractCardController() = default;

    virtual const QString& getType() const = 0;
};

#endif // ABSTRACTCARDCONTROLLER_H
