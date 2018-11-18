#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

class QJsonDocument;

class ISerizlizable {
public:
    virtual ~ISerizlizable() = default;
    virtual QJsonDocument toJSON() const = 0;
};

#endif // ISERIALIZABLE_H
